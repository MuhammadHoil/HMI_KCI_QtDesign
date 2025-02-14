#include "pecustatus.h"
#include "ui_pecustatus.h"

PecuStatus::PecuStatus(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PecuStatus)
{
    ui->setupUi(this);
}

PecuStatus::~PecuStatus()
{
    delete ui;
}
