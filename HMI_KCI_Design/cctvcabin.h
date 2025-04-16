#ifndef CCTVCABIN_H
#define CCTVCABIN_H

#include <QMainWindow>

namespace Ui {
class CctvCabin;
}

class CctvCabin : public QMainWindow
{
    Q_OBJECT

public:
    explicit CctvCabin(QWidget *parent = nullptr);
    ~CctvCabin();

private:
    Ui::CctvCabin *ui;
};

#endif // CCTVCABIN_H
