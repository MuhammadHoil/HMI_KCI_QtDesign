#include "connectionstatus.h"
#include "ui_connectionstatus.h"

ConnectionStatus::ConnectionStatus(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectionStatus)
{
    ui->setupUi(this);
}

ConnectionStatus::~ConnectionStatus()
{
    delete ui;
}
