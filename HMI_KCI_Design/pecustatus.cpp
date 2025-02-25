#include "pecustatus.h"
#include "ui_pecustatus.h"

PecuStatus::PecuStatus(WindowManager *mgr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PecuStatus),
    m_wndManager(mgr)
{
    ui->setupUi(this);
}

PecuStatus::~PecuStatus()
{
    delete ui;
}

void PecuStatus::hide()
{
    QMainWindow::hide();
}
