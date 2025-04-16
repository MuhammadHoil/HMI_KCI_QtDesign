#ifndef CONNECTIONSTATUS_H
#define CONNECTIONSTATUS_H

#include <QMainWindow>

namespace Ui {
class ConnectionStatus;
}

class WindowManager;
class QTimer;

class ConnectionStatus : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConnectionStatus(WindowManager *mgr, QWidget *parent = nullptr);
    ~ConnectionStatus();

public slots:
    void hide();

private slots:
    void updateTime();

private:
    Ui::ConnectionStatus *ui;
    WindowManager *m_wndManager;
    QTimer *m_timer;

    void initSignalConnection();
};

#endif // CONNECTIONSTATUS_H
