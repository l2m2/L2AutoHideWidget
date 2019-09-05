#include "l2mainwindow.h"
#include "ui_l2mainwindow.h"
#include <QDebug>
#include <QMoveEvent>
#include <QPropertyAnimation>
#include <QScreen>
#include <QTimer>

L2MainWindow::L2MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::L2MainWindow)
{
    ui->setupUi(this);

    // 禁止最大化按钮
    setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);

    // 获取屏幕宽度
    mScreenWidth = QApplication::primaryScreen()->geometry().width();

    // 由于leaveEvent与enterEnter对系统边框部分失效
    // 因此增加定时器监测鼠标所在点是否在窗口区域内
    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    mTimer->start(100);
}

L2MainWindow::~L2MainWindow()
{
    delete ui;
}

void L2MainWindow::moveEvent(QMoveEvent *event)
{
    if (qApp->mouseButtons() == Qt::LeftButton) {
        mIsMoving = true;
        if (this->y() < 0) {
            mDirection = Direction::Up;
            move(this->x(), 0);
            mIsMoving = false;
        } else if (this->x() < 0) {
            mDirection = Direction::Left;
            move(0, this->y());
            mIsMoving = false;
        } else if (this->x() > (mScreenWidth - this->frameGeometry().width()))  {
            mDirection = Direction::Right;
            move(mScreenWidth-this->width(), this->y());
            mIsMoving = false;
        }
    }
    QWidget::moveEvent(event);
}

void L2MainWindow::hideWidget()
{
    QPoint startPos = this->pos();
    QPoint endPos;
    if (mDirection == Direction::Up) {
        endPos = QPoint(this->x(), -this->frameGeometry().height() + 2);
    } else if (mDirection == Direction::Left) {
        endPos = QPoint(-this->frameGeometry().width() + 2, this->y());
    } else if (mDirection == Direction::Right) {
        endPos = QPoint(mScreenWidth - 2, this->y());
    }

    if (startPos == endPos) {
        return;
    }

    QPropertyAnimation *anim = new QPropertyAnimation(this, "pos", this);
    connect(anim, &QAbstractAnimation::finished, [this](){
        // Note: This function calls setParent() when changing the flags for a window,
        // causing the widget to be hidden.
        // You must call show() to make the widget visible again..
        setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
        show();
    });
    anim->setDuration(100);
    anim->setStartValue(startPos);
    anim->setEndValue(endPos);
    anim->setEasingCurve(QEasingCurve::InQuad);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void L2MainWindow::showWidget()
{
    QPoint startPos = this->pos();
    QPoint endPos;
    if (mDirection == Direction::Up) {
        endPos = QPoint(this->x(), 0);
    } else if (mDirection == Direction::Left) {
        endPos = QPoint(0, this->y());
    } else if (mDirection == Direction::Right) {
        endPos = QPoint(mScreenWidth - this->frameGeometry().width(), this->y());
    }

    if (startPos == endPos) {
        return;
    }

    // Note: This function calls setParent() when changing the flags for a window,
    // causing the widget to be hidden.
    // You must call show() to make the widget visible again..
    setWindowFlags(this->windowFlags() & ~Qt::WindowStaysOnTopHint);
    show();

    QPropertyAnimation *anim = new QPropertyAnimation(this, "pos", this);
    anim->setDuration(100);
    anim->setStartValue(startPos);
    anim->setEndValue(endPos);
    anim->setEasingCurve(QEasingCurve::OutQuad);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void L2MainWindow::on_actionClose_triggered()
{
    qApp->quit();
}

void L2MainWindow::onTimeout()
{
    if (mIsMoving) {
        return;
    }
    if (this->frameGeometry().contains(QCursor::pos())) {
        // 如果鼠标点在窗口区域内
        // 且已经隐藏，则显示窗口
        if (mHideFlag) {
            mHideFlag = false;
            showWidget();
        }
    } else {
        // 如果鼠标点不在窗口区域内
        // 判断是否贴边需要自动隐藏
        bool shouldHide = false;
        if (mDirection == Direction::Up)  {
            shouldHide = (this->y() <= 0);
        } else if (mDirection == Direction::Left) {
            shouldHide = (this->x() <= 0);
        } else if (mDirection == Direction::Right) {
            shouldHide = (this->x() >= (mScreenWidth - this->frameGeometry().width()));
        }
        if (shouldHide) {
            mHideFlag = true;
            hideWidget();
        } else {
            mHideFlag = false;
        }
    }
}
