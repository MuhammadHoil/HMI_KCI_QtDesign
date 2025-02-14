#ifndef PECUSTATUS_H
#define PECUSTATUS_H

#include <QMainWindow>

namespace Ui {
class PecuStatus;
}

class PecuStatus : public QMainWindow
{
    Q_OBJECT

public:
    explicit PecuStatus(QWidget *parent = nullptr);
    ~PecuStatus();

private:
    Ui::PecuStatus *ui;
};

#endif // PECUSTATUS_H
