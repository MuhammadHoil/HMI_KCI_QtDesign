#include "connectionstatus.h"
#include "ui_connectionstatus.h"
#include "windowmanager.h"
#include <QDateTime>
#include <QTimer>
#include <QDebug>
#include <QFileInfo>
#include <QProcess>

ConnectionStatus::ConnectionStatus(WindowManager *mgr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectionStatus),
    m_wndManager(mgr)
{
    ui->setupUi(this);

    m_timer = new QTimer(this);

    initSignalConnection();

    m_timer -> start(1000);
}

ConnectionStatus::~ConnectionStatus()
{
    delete ui;
}

void ConnectionStatus::hide()
{
    QMainWindow::hide();
}

void ConnectionStatus::initSignalConnection()
{
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTime()));

    connect(ui -> announcer_button, SIGNAL(clicked()), m_wndManager, SLOT(onBtnAnnouncerClick()));
    connect(ui -> cctv_passenger_button, SIGNAL(clicked()), m_wndManager, SLOT(onBtnCctvClick()));
    connect(ui -> pecu_stat_button, SIGNAL(clicked()), m_wndManager, SLOT(onBtnPecuClick()));
    connect(ui -> device_stat_button, SIGNAL(clicked()), m_wndManager, SLOT(onBtnConnectionStatusClick()));
    connect(ui -> display_button, SIGNAL(clicked()), m_wndManager, SLOT(onBtnDisplayMenuClick()));
    connect(ui -> system_button, SIGNAL(clicked()), m_wndManager, SLOT(onBtnSystemClick()));
}

void ConnectionStatus::updateTime()
{
    QDateTime curTime = QDateTime::currentDateTime();
    QString strDate = curTime.toString("dd-MM-yyyy");
    QString strTime = curTime.toString("hh:mm:ss");

    ui -> lblDate -> setText("<p style='font-size:12pt; text-align: center'>" + strDate + "</p>");
    ui -> lblTime -> setText("<p style='font-size:12pt; text-align: center'>" "| " + strTime + " WIB" + "</p>");
}
