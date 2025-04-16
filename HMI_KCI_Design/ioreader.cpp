#include "ioreader.h"
#include <QModbusTcpClient>
#include <QSettings>
#include <QTimer>
#include <QUrl>
#include <QDebug>
#include <QProcess>

IOReader::IOReader(QObject *parent) : QObject (parent),
m_isConnected(false), m_isCabinOn(false),m_isResetTimerActive(false), m_leftDoorVal(-1),m_rightDoorVal(-1),m_closeCtr(0)
{
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, "Respati", "pids");

    m_modbusClient = new QModbusTcpClient(this);
    m_deviceIP = "10.128.1.24:502";
    m_readTimeout = 1000;
    m_delay = 200;
    m_numOfDataUnit = 6;

    connect(m_modbusClient, &QModbusClient::stateChanged, this, &IOReader::stateChanged);
}

IOReader::~IOReader()
{
    delete m_modbusClient;
}

void IOReader::start()
{
    if (connectToDevice()) {
        m_timer = new QTimer(this);
        connect(m_timer, SIGNAL(timeout()), this, SLOT(sendRequest()));
        m_timer->start(m_delay);
    }
}

bool IOReader::isCabinOn()
{
    return m_isCabinOn;
}

bool IOReader::connectToDevice()
{
    bool result = true;

    if (m_modbusClient->state() != QModbusClient::ConnectedState) {
        QUrl url = QUrl::fromUserInput(m_deviceIP);
        m_modbusClient->setConnectionParameter(QModbusDevice::NetworkAddressParameter, url.host());
        m_modbusClient->setConnectionParameter(QModbusDevice::NetworkPortParameter, url.port());
        m_modbusClient->setTimeout(m_readTimeout);
        m_modbusClient->setNumberOfRetries(3);

        if (!m_modbusClient->connectDevice()) {
            qDebug() << "Connect to modbus device failed: " << m_modbusClient->errorString() << endl;
            return false;
        }
    }

    return result;
}

void IOReader::sendRequest()
{
    // qDebug() << "Sending modbus request..." << endl;
    auto *reply = m_modbusClient->sendReadRequest(readRequest(), m_deviceModbusAddress);
    if (reply) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &IOReader::readReady);
        } else {
            delete reply;   // broadcast replies return immediately
        }
    } else {
        qDebug() << "Modbus Read Error: " << m_modbusClient->errorString() << endl;
    }
}

void IOReader::readReady()
{
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError) {
        m_dataUnit = reply->result();
        for (int i = 0; i < int(m_dataUnit.valueCount()); i++) {
            //qDebug() << "Address: " << m_dataUnit.startAddress() + i
            //         << "Value: " << m_dataUnit.value(i) << endl;

            //if (m_dataUnit.value(3) || m_dataUnit.value(2)){
            //    playSound("dooropen.mp3");
            //}else if(m_dataUnit.value(4) || m_dataUnit.value(5)){
            //    playSound("doorclose.mp3");
            //}
        }
        parseDataUnit();
    } else if (reply->error() == QModbusDevice::ProtocolError) {
        qDebug() << "Read response error: " << reply->errorString()
                 << "Modbus exception: " << reply->rawResult().exceptionCode() << endl;
    } else {
        qDebug() << "Read response error: " << reply->errorString()
                 << "Error code: " << reply->error() << endl;
    }

    reply->deleteLater();
}

void IOReader::stateChanged(int state)
{
    if (state == QModbusDevice::ConnectedState) {
        m_isConnected = true;
        qDebug() << "Inside stateChanged() slot" << endl;
    }
    else if (state == QModbusDevice::UnconnectedState ||
             state == QModbusDevice::ClosingState) {
        connectToDevice();
        qDebug() << "Reconnecting to IO device" << endl;
    }
}

QModbusDataUnit IOReader::readRequest() const
{
    const auto table =
            static_cast<QModbusDataUnit::RegisterType> (QModbusDataUnit::Coils);

    int startAddress = 0;
    return QModbusDataUnit(table, startAddress, m_numOfDataUnit);
}

void IOReader::parseDataUnit()
{
    if (!m_dataUnit.value(0)) {
        if (m_isCabinOn) {
            //emit turnOffCabin();
            m_isCabinOn = false;
        }
        return;
    }

    if (m_dataUnit.value(0)) {
        if (!m_isCabinOn) {
            //emit turnOnCabin();
            m_isCabinOn = true;
            playSound("welcome.mp3");
        }
    }

    if (m_leftDoorVal == -1) {
        m_leftDoorVal = m_dataUnit.value(3);
        m_rightDoorVal = m_dataUnit.value(2);
        return;
    }

    if (m_dataUnit.value(2) != m_rightDoorVal) {
        if (m_dataUnit.value(2) == 1) {
            //emit rightDoorsOpening();
            qDebug() << "Right Door Open";
            playSound("dooropen.mp3");
        }
    }

    if (m_dataUnit.value(3) != m_leftDoorVal) {
        if (m_dataUnit.value(3) == 1) {
            //emit leftDoorsOpening();
            qDebug() << "Left Door Open";
            playSound("dooropen.mp3");
        }
    }

    if (m_dataUnit.value(4) && m_closeCtr < 1) {
        //emit rightDoorsClosing();
        //emit anyDoorClosing();
        ++m_closeCtr;
        qDebug() << "Right Door Closing";
        playSound("doorclose.mp3");
    }

    if (m_dataUnit.value(5) && m_closeCtr < 1) {
        //emit leftDoorsClosing();
        //emit anyDoorClosing();
        ++m_closeCtr;
        qDebug() << "Left Door Closing";
        playSound("doorclose.mp3");
    }

    if (m_closeCtr > 0 && !m_isResetTimerActive) {
        QTimer::singleShot(5000, [this]() {
            resetCloseCtr();
        });
        m_isResetTimerActive = true;
    }
}

/*
void IOReader::playAudioMp3(QString fileName)
{
    QString dstAddress = "192.168.255.255";
    QProcess::startDetached(
        "cvlc",
        {"../sound/" + fileName,
         "--sout=#duplicate{dst=rtp{dst=" + dstAddress + ",port-audio=32000}}",
         "--no-sout-all",
         "--sout-keep",
         "vlc://quit"});
}
*/

void IOReader::playSound(QString fileName)
{
    QString dstAddress = "255.255.255.255";
    QProcess::startDetached(
        "cvlc",
        {"../sound/" + fileName,
         "--sout=#duplicate{dst=rtp{dst=" + dstAddress + ",port-audio=11001}}",
         "--no-sout-all",
         "--sout-keep",
         "vlc://quit"});
}


void IOReader::resetCloseCtr()
{
    m_closeCtr = 0;
    m_isResetTimerActive = false;
}

