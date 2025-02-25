#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>

class AnnouncerMenu;
class CctvView;
class ConnectionStatus;
class DisplayMenu;
class MainWindow;
class PecuStatus;

class WindowManager : public QObject
{
    Q_OBJECT
public:
    explicit WindowManager(QObject *parent = nullptr);
    ~WindowManager();

    void showMainWindow();

public slots:
    void onBtnAnnouncerClick();
    void onBtnCctvClick();
    void onBtnConnectionStatusClick();
    void onBtnDisplayMenuClick();
    void onBtnSystemClick();
    void onBtnPecuClick();

private:
    AnnouncerMenu *m_wndAnnouncer;
    CctvView *m_wndCctv;
    ConnectionStatus *m_wndConnection;
    DisplayMenu *m_wndDisplay;
    MainWindow *m_wndHMI;
    PecuStatus *m_wndPecu;
};

#endif // WINDOWMANAGER_H
