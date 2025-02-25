#ifndef PECUSTATUS_H
#define PECUSTATUS_H

#include <QMainWindow>

namespace Ui {
class PecuStatus;
}

class WindowManager;
class QTimer;

class PecuStatus : public QMainWindow
{
    Q_OBJECT

public:
    explicit PecuStatus(WindowManager *mgr, QWidget *parent = nullptr);
    ~PecuStatus();

public slots:
    void hide();

private slots:
    void updateTime();

private:
    Ui::PecuStatus *ui;
    WindowManager *m_wndManager;
    QTimer *m_timer;
};

#endif // PECUSTATUS_H
