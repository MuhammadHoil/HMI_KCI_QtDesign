#ifndef DISPLAYMENU_H
#define DISPLAYMENU_H

#include <QMainWindow>

namespace Ui {
class DisplayMenu;
}

class WindowManager;
class QTimer;

class DisplayMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit DisplayMenu(WindowManager *mgr, QWidget *parent = nullptr);
    ~DisplayMenu();

public slots:
    void hide();

private slots:
    void updateTime();

private:
    Ui::DisplayMenu *ui;
    WindowManager *m_wndManager;
    QTimer *m_timer;
};

#endif // DISPLAYMENU_H
