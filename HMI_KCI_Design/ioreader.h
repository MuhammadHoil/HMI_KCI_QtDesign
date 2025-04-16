#ifndef IOREADER_H
#define IOREADER_H

#include <QObject>
#include <QModbusDataUnit>

QT_BEGIN_NAMESPACE
class QModbusClient;
class QTimer;
QT_END_NAMESPACE

class IOReader : public QObject
{
    Q_OBJECT
public:
    explicit IOReader(QObject *parent = nullptr);
    ~IOReader();

    void start();
    bool isCabinOn();
private:
    bool connectToDevice();
    QModbusDataUnit readRequest() const;
    void parseDataUnit();
    void resetCloseCtr();

signals:
    void turnOnCabin();
    void turnOffCabin();
    void leftDoorsOpening();
    void rightDoorsOpening();
    void leftDoorsClosing();
    void rightDoorsClosing();
    void anyDoorClosing();
    //void playAudioMp3(QString fileName);

private slots:
    void sendRequest();
    void readReady();
    void stateChanged(int state);

private:
    QModbusClient *m_modbusClient;
    QModbusDataUnit m_dataUnit;

    QString m_deviceIP;
    int m_deviceModbusAddress;
    int m_readTimeout;
    int m_delay;    // Delay between poll in milli second
    quint16 m_numOfDataUnit;

    QTimer *m_timer;
    bool m_isConnected;
    bool m_isCabinOn;
    bool m_isResetTimerActive;

    int m_leftDoorVal;
    int m_rightDoorVal;
    int m_closeCtr;

    void playSound(QString fileName);
};

#endif // IOREADER_H
