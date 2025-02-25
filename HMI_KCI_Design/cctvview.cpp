#include "cctvview.h"
#include "ui_cctvview.h"

CctvView::CctvView(WindowManager *mgr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CctvView),
    m_wndManager(mgr)
{
    ui->setupUi(this);
}

CctvView::~CctvView()
{
    delete ui;
}

void CctvView::hide()
{
    QMainWindow::hide();
}
