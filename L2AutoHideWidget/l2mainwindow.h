#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class L2MainWindow;
}

class QTimer;

class L2MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum Direction {
        Up = 0,
        Left,
        Right
    };
public:
    explicit L2MainWindow(QWidget *parent = nullptr);
    ~L2MainWindow();

protected:
    void moveEvent(QMoveEvent *event) override;

private slots:
    void on_actionClose_triggered();
    void onTimeout();

private:
    void hideWidget();
    void showWidget();

private:
    Ui::L2MainWindow *ui;
    int mScreenWidth;
    Direction mDirection;
    bool mHideFlag = false;
    bool mIsMoving = false;
    QTimer *mTimer = nullptr;
};

#endif // MAINWINDOW_H
