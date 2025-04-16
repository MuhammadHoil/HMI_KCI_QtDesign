#include "cctvcabin.h"
#include "ui_cctvcabin.h"

CctvCabin::CctvCabin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CctvCabin)
{
    ui->setupUi(this);
}

CctvCabin::~CctvCabin()
{
    delete ui;
}
