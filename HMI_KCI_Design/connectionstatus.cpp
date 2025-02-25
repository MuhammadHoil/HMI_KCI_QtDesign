#include "connectionstatus.h"
#include "ui_connectionstatus.h"

ConnectionStatus::ConnectionStatus(WindowManager *mgr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectionStatus),
    m_wndManager(mgr)
{
    ui->setupUi(this);
}

ConnectionStatus::~ConnectionStatus()
{
    delete ui;
}

void ConnectionStatus::hide()
{
    QMainWindow::hide();
}
