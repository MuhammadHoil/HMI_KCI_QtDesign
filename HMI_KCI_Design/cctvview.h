#ifndef CCTVVIEW_H
#define CCTVVIEW_H

#include <QMainWindow>

namespace Ui {
class CctvView;
}

class CctvView : public QMainWindow
{
    Q_OBJECT

public:
    explicit CctvView(QWidget *parent = nullptr);
    ~CctvView();

private:
    Ui::CctvView *ui;
};

#endif // CCTVVIEW_H
