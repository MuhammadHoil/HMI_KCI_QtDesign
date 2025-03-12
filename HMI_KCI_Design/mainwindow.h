#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QOpenGLWidget>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtWidgets/WidgetVideo.h>
#include <VLCQtCore/Common.h>
#include <QThread>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class QTimer;
class WindowManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(WindowManager *mgr, QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void hide();

private slots:
    void updateTime();
    void stopStream();
    void openStream(const QString &cameraType);

    void on_sidecam_tc1_button_clicked();

private:
    Ui::MainWindow *ui;
    WindowManager *m_wndManager;
    QTimer *m_timer;

    void initSignalConnection();
    void playSound();

    QString m_dstAddress;
    QString trainId;
    QString m_finalStation;

    //VLC Components
    VlcInstance *m_vlcInstance;
    VlcMediaPlayer *m_player1;
    VlcMediaPlayer *m_player2;
    VlcWidgetVideo *m_vid1;
    VlcWidgetVideo *m_vid2;
    VlcMedia *m_media1;
    VlcMedia *m_media2;

    const quint16 HMI_DATA_PORT = 1234;
    QString m_activeCamPage;
    bool m_cameraZoomIn;
};

#endif // MAINWINDOW_H
