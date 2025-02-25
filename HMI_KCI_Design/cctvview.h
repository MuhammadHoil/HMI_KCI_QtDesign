#ifndef CCTVVIEW_H
#define CCTVVIEW_H

#include <QMainWindow>

namespace Ui {
class CctvView;
}

class QTimer;
class WindowManager;

class CctvView : public QMainWindow
{
    Q_OBJECT

public:
    explicit CctvView(WindowManager *mgr, QWidget *parent = nullptr);
    ~CctvView();

public slots:
    void hide();

private slots:
    void updateTime();

private:
    Ui::CctvView *ui;
    WindowManager *m_wndManager;
    QTimer *m_timer;

    void initSignalConnection();
};

#endif // CCTVVIEW_H
