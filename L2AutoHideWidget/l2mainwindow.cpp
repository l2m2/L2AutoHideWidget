#include "l2mainwindow.h"
#include "ui_l2mainwindow.h"
#include <QDebug>
#include <QScreen>
#include <QPropertyAnimation>
#include <QMoveEvent>

L2MainWindow::L2MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::L2MainWindow)
{
    ui->setupUi(this);

    // 禁止最大化按钮
    setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);

    // 获取屏幕宽度
    mScreenWidth = QApplication::primaryScreen()->geometry().width();
}

L2MainWindow::~L2MainWindow()
{
    delete ui;
}

void L2MainWindow::leaveEvent(QEvent *event)
{
    if (!this->frameGeometry().contains(QCursor::pos())) {
        bool shouldHide = false;
        if (mDirection == Direction::Up)  {
            shouldHide = (this->y() <= 0);
        } else if (mDirection == Direction::Left) {
            shouldHide = (this->x() <= 0);
        } else if (mDirection == Direction::Right) {
            shouldHide = (this->x() >= (mScreenWidth - this->frameGeometry().width()));
        }
        if (shouldHide) {
            hideWidget();
            mHideFlag = true;
        } else {
            mHideFlag = false;
        }
    }
    QWidget::leaveEvent(event);
}

void L2MainWindow::enterEvent(QEvent *event)
{
    if (mHideFlag) {
        showWidget();
    }
    QWidget::enterEvent(event);
}

void L2MainWindow::moveEvent(QMoveEvent *event)
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
        if (this->x() > (mScreenWidth - this->frameGeometry().width()))  {
            mDirection = Direction::Right;
            move(mScreenWidth-this->width(), this->y());
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
    anim->setDuration(200);
    anim->setStartValue(startPos);
    anim->setEndValue(endPos);
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
    QPropertyAnimation *anim = new QPropertyAnimation(this, "pos", this);
    anim->setDuration(200);
    anim->setStartValue(startPos);
    anim->setEndValue(endPos);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void L2MainWindow::on_actionClose_triggered()
{
    qApp->quit();
}
