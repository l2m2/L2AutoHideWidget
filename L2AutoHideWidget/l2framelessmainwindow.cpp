#include "l2framelessmainwindow.h"
#include "ui_l2framelessmainwindow.h"
#include <QDebug>
#include <QScreen>
#include <QPropertyAnimation>
#include <QMoveEvent>

L2FramelessMainWindow::L2FramelessMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::L2FramelessMainWindow)
{
    ui->setupUi(this);
    ui->windowTitleBar->SetMainWindow(this);

    setWindowFlags(Qt::FramelessWindowHint);

    // 获取屏幕宽度
    mScreenWidth = QApplication::primaryScreen()->geometry().width();
}

L2FramelessMainWindow::~L2FramelessMainWindow()
{
    delete ui;
}

void L2FramelessMainWindow::leaveEvent(QEvent *event)
{
    bool shouldHide = false;
    if (mDirection == Direction::Up)  {
        shouldHide = (this->y() <= 0);
    } else if (mDirection == Direction::Left) {
        shouldHide = (this->x() <= 0);
    } else if (mDirection == Direction::Right) {
        shouldHide = (this->x() >= (mScreenWidth - this->width()));
    }
    if (shouldHide) {
        hideWidget();
        mHideFlag = true;
    } else {
        mHideFlag = false;
    }
    QWidget::leaveEvent(event);
}

void L2FramelessMainWindow::enterEvent(QEvent *event)
{
    if (mHideFlag) {
        showWidget();
    }
    QWidget::enterEvent(event);
}

void L2FramelessMainWindow::moveEvent(QMoveEvent *event)
{
    if (qApp->mouseButtons() == Qt::LeftButton) {
        if (this->y() < 0) {
            mDirection = Direction::Up;
            move(this->x(), 0);
        }
        if (this->x() < 0) {
            mDirection = Direction::Left;
            move(0, this->y());
        }
        if (this->x() > (mScreenWidth - this->width()))  {
            mDirection = Direction::Right;
            move(mScreenWidth - this->width(), this->y());
        }
    }
    QWidget::moveEvent(event);
}

void L2FramelessMainWindow::hideWidget()
{
    QPoint startPos = this->pos();
    QPoint endPos;
    if (mDirection == Direction::Up) {
        endPos = QPoint(this->x(), -this->height() + 1);
    } else if (mDirection == Direction::Left) {
        endPos = QPoint(-this->width() + 1, this->y());
    } else if (mDirection == Direction::Right) {
        endPos = QPoint(mScreenWidth - 1, this->y());
    }
    if (startPos == endPos) {
        return;
    }
    if (mAnim == nullptr) {
        mAnim = new QPropertyAnimation(this, "pos", this);
    }
    mAnim->setDuration(200);
    mAnim->setStartValue(startPos);
    mAnim->setEndValue(endPos);
    mAnim->start();
}

void L2FramelessMainWindow::showWidget()
{
    QPoint startPos = this->pos();
    QPoint endPos;
    if (mDirection == Direction::Up) {
        endPos = QPoint(this->x(), 0);
    } else if (mDirection == Direction::Left) {
        endPos = QPoint(0, this->y());
    } else if (mDirection == Direction::Right) {
        endPos = QPoint(mScreenWidth - this->width(), this->y());
    }
    if (startPos == endPos) {
        return;
    }
    if (mAnim == nullptr) {
        mAnim = new QPropertyAnimation(this, "pos", this);
    }
    mAnim->setDuration(200);
    mAnim->setStartValue(startPos);
    mAnim->setEndValue(endPos);
    mAnim->start();
}
