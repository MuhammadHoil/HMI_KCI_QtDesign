#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


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

private:
    Ui::MainWindow *ui;
    WindowManager *m_wndManager;
    QTimer *m_timer;

    void initSignalConnection();
    void playSound();

    QString m_dstAddress;
    QString trainId;
    QString m_finalStation;

    const quint16 HMI_DATA_PORT = 1234;
};

#endif // MAINWINDOW_H
