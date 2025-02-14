#ifndef ANNOUNCERMENU_H
#define ANNOUNCERMENU_H

#include <QMainWindow>

namespace Ui {
class AnnouncerMenu;
}

class AnnouncerMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit AnnouncerMenu(QWidget *parent = nullptr);
    ~AnnouncerMenu();

private:
    Ui::AnnouncerMenu *ui;
};

#endif // ANNOUNCERMENU_H
