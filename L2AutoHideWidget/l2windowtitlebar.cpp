#include "l2windowtitlebar.h"
#include <QMainWindow>
#include <QMouseEvent>
#include <QToolButton>
#include <QHBoxLayout>
#include <QApplication>

L2WindowTitleBar::L2WindowTitleBar(QWidget *parent)
    : QWidget (parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addStretch(1);
    QToolButton *closeButton = new QToolButton(this);
    connect(closeButton, &QToolButton::clicked, [](){
        qApp->quit();
    });
    closeButton->setIcon(QIcon(":/close.svg"));
    layout->addWidget(closeButton);
}

L2WindowTitleBar::~L2WindowTitleBar()
{

}

void L2WindowTitleBar::SetMainWindow(QMainWindow *mainwindow)
{
    mMainWindow = mainwindow;
}

void L2WindowTitleBar::mousePressEvent(QMouseEvent *event)
{
    mClickPos = event->globalPos() - mMainWindow->pos();
}

void L2WindowTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::RightButton) {
        return;
    }
    mMainWindow->move(event->globalPos() - mClickPos);
}
