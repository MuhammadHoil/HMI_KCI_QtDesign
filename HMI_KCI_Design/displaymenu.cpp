#include "displaymenu.h"
#include "ui_displaymenu.h"

DisplayMenu::DisplayMenu(WindowManager *mgr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DisplayMenu),
    m_wndManager(mgr)
{
    ui->setupUi(this);
}

DisplayMenu::~DisplayMenu()
{
    delete ui;
}

void DisplayMenu::hide()
{
    QMainWindow::hide();
}
