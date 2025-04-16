#include "announcermenu.h"
#include "ui_announcermenu.h"
#include "windowmanager.h"
#include <QDateTime>
#include <QDebug>
#include <QProcess>
#include <QFileInfo>
#include <QTimer>

AnnouncerMenu::AnnouncerMenu(WindowManager *mgr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AnnouncerMenu),
    m_wndManager(mgr)
{
    ui->setupUi(this);
    ui->lblDate->setTextFormat(Qt::RichText);
    ui->lblTime->setTextFormat(Qt::RichText);

    m_timer = new QTimer(this);

    initSignalConnection();

    m_timer -> start(1000);
}

AnnouncerMenu::~AnnouncerMenu()
{
    delete ui;

}

void AnnouncerMenu::hide()
{
    QMainWindow::hide();
}

void AnnouncerMenu::initSignalConnection()
{
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTime()));

    connect(ui -> announcer_button, SIGNAL(clicked()), m_wndManager, SLOT(onBtnAnnouncerClick()));
    connect(ui -> cctv_passenger_button, SIGNAL(clicked()), m_wndManager, SLOT(onBtnCctvClick()));
    connect(ui -> pecu_stat_button, SIGNAL(clicked()), m_wndManager, SLOT(onBtnPecuClick()));
    connect(ui -> device_stat_button, SIGNAL(clicked()), m_wndManager, SLOT(onBtnConnectionStatusClick()));
    connect(ui -> display_button, SIGNAL(clicked()), m_wndManager, SLOT(onBtnDisplayMenuClick()));
    connect(ui -> system_button, SIGNAL(clicked()), m_wndManager, SLOT(onBtnSystemClick()));
}

void AnnouncerMenu::updateTime()
{
    QDateTime curTime = QDateTime::currentDateTime();
    QString strDate = curTime.toString("dd-MM-yyyy");
    QString strTime = curTime.toString("hh:mm:ss");

    ui -> lblDate -> setText("<p style='font-size:12pt; text-align: center'>" + strDate + "</p>");
    ui -> lblTime -> setText("<p style='font-size:12pt; text-align: center'>" "| " + strTime + " WIB" + "</p>");
}
