#ifndef FRAMELESSMAINWINDOW_H
#define FRAMELESSMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class L2FramelessMainWindow;
}

class L2FramelessMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum Direction {
        Up = 0,
        Left,
        Right
    };
public:
    explicit L2FramelessMainWindow(QWidget *parent = nullptr);
    ~L2FramelessMainWindow();

protected:
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);
    void moveEvent(QMoveEvent *event);

private:
    void hideWidget();
    void showWidget();

private:
    Ui::L2FramelessMainWindow *ui;
    int mScreenWidth;
    Direction mDirection;
    bool mHideFlag = false;
};

#endif // FRAMELESSMAINWINDOW_H
