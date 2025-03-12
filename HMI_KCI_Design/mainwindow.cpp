#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windowmanager.h"
#include <QDateTime>
#include <QTimer>
#include <QDebug>
#include <QProcess>
#include <QFileInfo>
#include <QtConcurrent/qtconcurrentrun.h>

MainWindow::MainWindow(WindowManager *mgr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_wndManager(mgr),
    m_activeCamPage(""),
    m_cameraZoomIn(false),
    m_media1(nullptr),
    m_media2(nullptr)
{
    ui->setupUi(this);
    ui->lblDate->setTextFormat(Qt::RichText);
    ui->lblTime->setTextFormat(Qt::RichText);

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    m_timer->start(1000);

    // Inisialisasi VLC
    m_vlcInstance = new VlcInstance(VlcCommon::args(), this);

    m_player1 = new VlcMediaPlayer(m_vlcInstance);
    m_player2 = new VlcMediaPlayer(m_vlcInstance);

    // Buat VlcWidgetVideo langsung, tanpa QOpenGLWidget
    m_vid1 = new VlcWidgetVideo(this);
    m_vid2 = new VlcWidgetVideo(this);

    // Hubungkan Video Widget ke Media Player
    m_player1->setVideoWidget(m_vid1);
    m_vid1->setMediaPlayer(m_player1);

    m_player2->setVideoWidget(m_vid2);
    m_vid2->setMediaPlayer(m_player2);

    // Atur ukuran tampilan
    m_vid1->setMinimumSize(450, 249);
    m_vid2->setMinimumSize(450, 249);

    // Tambahkan widget video ke layout UI
    //ui->camera_grid->setSpacing(5);
    //ui->camera_grid->setContentsMargins(10, 10, 10, 10);
    ui->camera_grid->addWidget(m_vid1, 0, 0);
    ui->camera_grid->addWidget(m_vid2, 0, 1);

    initSignalConnection();

    on_sidecam_tc1_button_clicked();

}

MainWindow::~MainWindow()
{
    stopStream();

    if(m_media1) { delete m_media1; }
    if(m_media2) { delete m_media2; }

    delete m_player1;
    delete m_player2;
    delete m_vid1;
    delete m_vid2;
    delete m_vlcInstance;
    delete ui;
}

void MainWindow::hide()
{
    QMainWindow::hide();
}

void MainWindow::initSignalConnection()
{
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTime()));

    connect(ui -> announcer_button, SIGNAL(clicked()), m_wndManager, SLOT(onBtnAnnouncerClick()));
    connect(ui -> cctv_passenger_button, SIGNAL(clicked()), m_wndManager, SLOT(onBtnCctvClick()));
    connect(ui -> pecu_stat_button, SIGNAL(clicked()), m_wndManager, SLOT(onBtnPecuClick()));
    connect(ui -> device_stat_button, SIGNAL(clicked()), m_wndManager, SLOT(onBtnConnectionStatusClick()));
    connect(ui -> display_button, SIGNAL(clicked()), m_wndManager, SLOT(onBtnDisplayMenuClick()));
    connect(ui -> system_button, SIGNAL(clicked()), m_wndManager, SLOT(onBtnSystemClick()));
}

void MainWindow::updateTime()
{
    QDateTime curTime = QDateTime::currentDateTime();
    QString strDate = curTime.toString("dd-MM-yyyy");
    QString strTime = curTime.toString("hh:mm:ss");

    ui -> lblDate -> setText("<p style='font-size:12pt; text-align: center'>" + strDate + "</p>");
    ui -> lblTime -> setText("<p style='font-size:12pt; text-align: center'>" "| " + strTime + " WIB" + "</p>");
}

void MainWindow::stopStream()
{
    m_player1 -> stop();
    m_player2 -> stop();
}

void MainWindow::openStream(const QString &cameraType)
{
    if (cameraType == "tc1")
    {
        stopStream();

        if (m_media1) { delete m_media1; m_media1 = nullptr; }
        if (m_media2) { delete m_media2; m_media2 = nullptr; }

        m_media1 = new VlcMedia("rtsp://admin:admin@10.128.9.14:554/stander/livestream/0/1", m_vlcInstance);
        m_media2 = new VlcMedia("rtsp://admin:admin@10.128.1.15:554/stander/livestream/0/1", m_vlcInstance);

        m_player1->open(m_media1);
        m_player2->open(m_media2);

        m_vid1->update();
        m_vid2->update();
    }
}


void MainWindow::on_sidecam_tc1_button_clicked()
{
    if(m_activeCamPage != "tc1")
    {
        m_activeCamPage = "tc1";
        qDebug() << "Switching to camera Side Cam TC1";

        stopStream();
        openStream("tc1");
    }
}
