#ifndef ANNOUNCERMENU_H
#define ANNOUNCERMENU_H

#include <QMainWindow>

namespace Ui {
class AnnouncerMenu;
}

class WindowManager;
class QTimer;

class AnnouncerMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit AnnouncerMenu(WindowManager *mgr, QWidget *parent = nullptr);
    ~AnnouncerMenu();

public slots:
    void hide();

private slots:
    void updateTime();

private:
    Ui::AnnouncerMenu *ui;
    WindowManager *m_wndManager;
    QTimer *m_timer;

    void initSignalConnection();
};

#endif // ANNOUNCERMENU_H
