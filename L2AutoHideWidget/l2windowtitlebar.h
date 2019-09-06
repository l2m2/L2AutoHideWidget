#ifndef L2MOVEABLEMENUBAR_H
#define L2MOVEABLEMENUBAR_H

#include <QWidget>
#include <QPoint>

class QMainWindow;

class L2WindowTitleBar : public QWidget
{
public:
    L2WindowTitleBar(QWidget *parent = nullptr);
    ~L2WindowTitleBar();

    void SetMainWindow(QMainWindow *mainwindow);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QMainWindow *mMainWindow = nullptr;
    QPoint mClickPos;
};

#endif // L2MOVEABLEMENUBAR_H
