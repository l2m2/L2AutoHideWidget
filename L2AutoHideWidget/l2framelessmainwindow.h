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
    void leaveEvent(QEvent *event) override;
    void enterEvent(QEvent *event) override;
    void moveEvent(QMoveEvent *event) override;
    void showEvent(QShowEvent *event) override;

private slots:
    void on_pushButton_clicked();

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
