#include "announcermenu.h"
#include "ui_announcermenu.h"

AnnouncerMenu::AnnouncerMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AnnouncerMenu)
{
    ui->setupUi(this);
}

AnnouncerMenu::~AnnouncerMenu()
{
    delete ui;
}
