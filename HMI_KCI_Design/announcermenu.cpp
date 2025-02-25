#include "announcermenu.h"
#include "ui_announcermenu.h"
#include "windowmanager.h"

AnnouncerMenu::AnnouncerMenu(WindowManager *mgr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AnnouncerMenu),
    m_wndManager(mgr)
{
    ui->setupUi(this);
}

AnnouncerMenu::~AnnouncerMenu()
{
    delete ui;
}

void AnnouncerMenu::hide()
{
    QMainWindow::hide();
}
