#include "displaymenu.h"
#include "ui_displaymenu.h"

DisplayMenu::DisplayMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DisplayMenu)
{
    ui->setupUi(this);
}

DisplayMenu::~DisplayMenu()
{
    delete ui;
}
