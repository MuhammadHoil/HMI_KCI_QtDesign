#ifndef CONNECTIONSTATUS_H
#define CONNECTIONSTATUS_H

#include <QMainWindow>

namespace Ui {
class ConnectionStatus;
}

class ConnectionStatus : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConnectionStatus(QWidget *parent = nullptr);
    ~ConnectionStatus();

private:
    Ui::ConnectionStatus *ui;
};

#endif // CONNECTIONSTATUS_H
