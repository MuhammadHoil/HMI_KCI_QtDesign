#include "cctvview.h"
#include "ui_cctvview.h"
#include "windowmanager.h"
#include <QDateTime>
#include <QVBoxLayout>
#include <QDebug>
#include <QHideEvent>
#include <QSettings>

CctvView::CctvView(WindowManager *mgr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CctvView),
    m_wndManager(mgr),
    m_cameraZoomIn(false),
    m_activeCamPage(""),
    m_media1(nullptr),
    m_media2(nullptr)
{
    ui->setupUi(this);

    QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, "../config/");
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, "Respati", "pids-hmi");

    QString test = settings.value("CCTV/test").toString();
    qDebug() << test;

    //button cctv group
    m_buttonMap["tc1"] = ui -> cctv_tc1_button;
    m_buttonMap["tc2"] = ui -> cctv_tc2_button;

    m_buttonMap["m1-1"] = ui -> cctv_m1_button;
    m_buttonMap["m1-2"] = ui -> cctv_m1_2_button;
    m_buttonMap["m1-3"] = ui -> cctv_m1_3_button;

    m_buttonMap["m2-1"] = ui -> cctv_m2_button;
    m_buttonMap["m2-2"] = ui -> cctv_m2_2_button;
    m_buttonMap["m2-3"] = ui -> cctv_m2_3_button;

    m_buttonMap["t1-1"] = ui -> cctv_t1_button;
    m_buttonMap["t1-2"] = ui -> cctv_t1_1_button;

    m_buttonMap["t2"] = ui -> cctv_t2_button;

    m_buttonMap["t3"] = ui -> cctv_t3_button;

    m_buttonMap["cabinTc1"] = ui -> cctv_cabin_tc1_button;
    m_buttonMap["cabinTc2"] = ui -> cctv_cabin_tc2_button;

    // Initialize VLC instance
    m_vlcInstance = new VlcInstance(VlcCommon::args(), this);

    // Initialize VLC media players
    m_player1 = new VlcMediaPlayer(m_vlcInstance);
    m_player2 = new VlcMediaPlayer(m_vlcInstance);

    // Create VLC Video Widgets
    m_vid1 = new VlcWidgetVideo(this);
    m_vid2 = new VlcWidgetVideo(this);

    // Set media players for video widgets
    m_player1->setVideoWidget(m_vid1);
    m_vid1->setMediaPlayer(m_player1);

    m_player2->setVideoWidget(m_vid2);
    m_vid2->setMediaPlayer(m_player2);

    m_vid1->setMinimumSize(430, 370);
    m_vid2->setMinimumSize(430, 370);
    // Layout settings
   // ui->camera_grid->setSpacing(5);
    //ui->camera_grid->setContentsMargins(10, 10, 10, 10);

    // Add OpenGL containers to grid layout
    ui->camera_grid->addWidget(m_vid1, 0, 0);
    ui->camera_grid->addWidget(m_vid2, 0, 1);

    // Start the timer for updating the time display
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &CctvView::updateTime);
    m_timer->start(1000);

    initSignalConnection();

    showEvent(nullptr);
}

CctvView::~CctvView()
{
    stopStream();

    if (m_media1) { delete m_media1; }
    if (m_media2) { delete m_media2; }

    delete m_player1;
    delete m_player2;
    delete m_vid1;
    delete m_vid2;
    delete m_vlcInstance;
    delete ui;
}

void CctvView::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);

    if (m_activeCamPage.isEmpty()) {
        on_cctv_tc1_button_clicked();
    }
}

void CctvView::hideEvent(QHideEvent *event)
{
    stopStream();
    QMainWindow::hideEvent(event);
}

void CctvView::initSignalConnection()
{
    connect(ui->announcer_button, &QPushButton::clicked, m_wndManager, &WindowManager::onBtnAnnouncerClick);
    connect(ui->cctv_passenger_button, &QPushButton::clicked, m_wndManager, &WindowManager::onBtnCctvClick);
    connect(ui->pecu_stat_button, &QPushButton::clicked, m_wndManager, &WindowManager::onBtnPecuClick);
    connect(ui->device_stat_button, &QPushButton::clicked, m_wndManager, &WindowManager::onBtnConnectionStatusClick);
    connect(ui->display_button, &QPushButton::clicked, m_wndManager, &WindowManager::onBtnDisplayMenuClick);
    connect(ui->system_button, &QPushButton::clicked, m_wndManager, &WindowManager::onBtnSystemClick);
}

void CctvView::updateTime()
{
    QDateTime curTime = QDateTime::currentDateTime();
    QString strDate = curTime.toString("dd-MM-yyyy");
    QString strTime = curTime.toString("hh:mm:ss");

    ui->lblDate->setText("<p style='font-size:12pt; text-align: center'>" + strDate + "</p>");
    ui->lblTime->setText("<p style='font-size:12pt; text-align: center'>" "| " + strTime + " WIB" + "</p>");
}

void CctvView::stopStream()
{
    m_player1->stop();
    m_player2->stop();
}

void CctvView::changeActiveButton(const QString &buttonName)
{
    for (auto it = m_buttonMap.begin(); it != m_buttonMap.end(); ++it) {
        if (it.key() == buttonName) {
            // Warna biru untuk tombol aktif
            it.value()->setStyleSheet("background-color: rgb(28, 31, 91); color: white; "
                                      "border: 1px solid white; border-radius: 8px;");
        } else {
            // Warna coklat untuk tombol non-aktif
            it.value()->setStyleSheet("background-color: rgb(91, 55, 28); color: white; "
                                      "border: 1px solid white; border-radius: 8px;");
        }
    }
}

void CctvView::openStream(const QString &cameraType)
{
    if (cameraType == "tc1")
    {
        stopStream();

        if (m_media1) { delete m_media1; m_media1 = nullptr; }
        if (m_media2) { delete m_media2; m_media2 = nullptr; }

        m_media1 = new VlcMedia("rtsp://admin:admiN132@10.128.1.101:554/cam/realmonitor?channel=1&subtype=1", m_vlcInstance);
        m_media2 = new VlcMedia("rtsp://admin:admiN132@10.128.1.102:554/cam/realmonitor?channel=1&subtype=1", m_vlcInstance);

        m_player1->open(m_media1);
        m_player2->open(m_media2);

        m_vid1->update();
        m_vid2->update();
    }
    else if ( cameraType == "m1-1")
    {
        stopStream();

        if (m_media1) { delete m_media1; m_media1 = nullptr; }
        if (m_media2) { delete m_media2; m_media2 = nullptr; }

        m_media1 = new VlcMedia("rtsp://admin:admiN132@10.128.2.101:554/cam/realmonitor?channel=1&subtype=1", m_vlcInstance);
        m_media2 = new VlcMedia("rtsp://admin:admiN132@10.128.2.102:554/cam/realmonitor?channel=1&subtype=1", m_vlcInstance);

        m_player1->open(m_media1);
        m_player2->open(m_media2);

        m_vid1->update();
        m_vid2->update();
    }
}

void CctvView::on_cctv_tc1_button_clicked()
{
    if (m_activeCamPage != "tc1") {
        m_activeCamPage = "tc1";
        qDebug() << "Switching to camera Passanger TC1";

        changeActiveButton("tc1");

        stopStream();
        openStream("tc1");
    }
}


void CctvView::on_cctv_m1_button_clicked()
{
    if (m_activeCamPage != "m1-1") {
        m_activeCamPage = "m1-1";
        qDebug() << "Switching to camera Passanger M1-1";

        changeActiveButton("m1-1");

        stopStream();
        openStream("m1-1");
    }
}
