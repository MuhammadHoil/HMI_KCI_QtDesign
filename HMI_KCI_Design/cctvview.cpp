#include "cctvview.h"
#include "ui_cctvview.h"

CctvView::CctvView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CctvView)
{
    ui->setupUi(this);
}

CctvView::~CctvView()
{
    delete ui;
}
