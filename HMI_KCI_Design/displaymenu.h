#ifndef DISPLAYMENU_H
#define DISPLAYMENU_H

#include <QMainWindow>

namespace Ui {
class DisplayMenu;
}

class DisplayMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit DisplayMenu(QWidget *parent = nullptr);
    ~DisplayMenu();

private:
    Ui::DisplayMenu *ui;
};

#endif // DISPLAYMENU_H
