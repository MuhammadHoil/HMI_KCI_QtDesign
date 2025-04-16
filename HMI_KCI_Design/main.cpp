#include "windowmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WindowManager mgr;
    mgr.showMainWindow();

    return a.exec();
}
