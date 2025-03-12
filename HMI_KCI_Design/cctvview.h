#ifndef CCTVVIEW_H
#define CCTVVIEW_H

#include <QMainWindow>
#include <QOpenGLWidget>
#include <QTimer>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtWidgets/WidgetVideo.h>
#include <VLCQtCore/Common.h>
#include <QMap>
#include <QPushButton>

class WindowManager;

namespace Ui {
class CctvView;
}

class CctvView : public QMainWindow
{
    Q_OBJECT

public:
    explicit CctvView(WindowManager *mgr, QWidget *parent = nullptr);
    ~CctvView();

protected:
    void hideEvent(QHideEvent *event) override;
    void showEvent(QShowEvent *event) override;

private slots:
    void updateTime();
    void stopStream();
    void openStream(const QString &cameraType);
    void changeActiveButton(const QString &buttonName);

    void on_cctv_tc1_button_clicked();
    void on_cctv_m1_button_clicked();

private:
    Ui::CctvView *ui;
    WindowManager *m_wndManager;
    QTimer *m_timer;

    // VLC Components
    VlcInstance *m_vlcInstance;
    VlcMediaPlayer *m_player1;
    VlcMediaPlayer *m_player2;
    VlcWidgetVideo *m_vid1;
    VlcWidgetVideo *m_vid2;
    VlcMedia *m_media1;
    VlcMedia *m_media2;

    QString m_activeCamPage;
    bool m_cameraZoomIn;
    QMap<QString, QPushButton*> m_buttonMap;

    void initSignalConnection();
};

#endif // CCTVVIEW_H
