#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPropertyAnimation;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum Direction {
        Up = 0,
        Left,
        Right
    };
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);
    void moveEvent(QMoveEvent *event);

private slots:
    void on_actionClose_triggered();

private:
    void hideWidget();
    void showWidget();

private:
    Ui::MainWindow *ui;
    int mScreenWidth;
    int mSpacingToEdge = 2;
    Direction mDirection;
    bool mHideFlag = false;
    QPropertyAnimation *mAnim = nullptr;
};

#endif // MAINWINDOW_H
