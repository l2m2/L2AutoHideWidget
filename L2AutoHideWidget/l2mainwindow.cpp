#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QScreen>
#include <QPropertyAnimation>
#include <QMoveEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 禁止最大化按钮
    setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);

    // 获取屏幕宽度
    mScreenWidth = QApplication::primaryScreen()->geometry().width();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::leaveEvent(QEvent *event)
{
    if (!this->frameGeometry().contains(QCursor::pos())) {
        bool shouldHide = false;
        if (mDirection == Direction::Up)  {
            shouldHide = (this->y() <= mSpacingToEdge);
        } else if (mDirection == Direction::Left) {
            shouldHide = (this->x() <= mSpacingToEdge);
        } else if (mDirection == Direction::Right) {
            shouldHide = (this->x() >= (mScreenWidth - this->frameGeometry().width() - mSpacingToEdge));
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

void MainWindow::enterEvent(QEvent *event)
{
    if (mHideFlag) {
        showWidget();
        mHideFlag = false;
    }
    QWidget::enterEvent(event);
}

void MainWindow::moveEvent(QMoveEvent *event)
{
    if (qApp->mouseButtons() == Qt::LeftButton) {
        if (this->y() < mSpacingToEdge) {
            mDirection = Direction::Up;
            move(this->x(), mSpacingToEdge);
        }
        if (this->x() < mSpacingToEdge) {
            mDirection = Direction::Left;
            move(mSpacingToEdge, y());
        }
        if (this->x() > (mScreenWidth - this->frameGeometry().width() - mSpacingToEdge))  {
            mDirection = Direction::Right;
            move(mScreenWidth-this->width(), y());
        }
    }
    QWidget::moveEvent(event);
}

void MainWindow::hideWidget()
{
    if (mAnim == nullptr) {
        mAnim = new QPropertyAnimation(this, "pos", this);
    }
    mAnim->setDuration(200);
    mAnim->setStartValue(this->pos());
    QPoint endPos;
    if (mDirection == Direction::Up) {
        endPos = QPoint(this->x(), -this->frameGeometry().height() + mSpacingToEdge);
    } else if (mDirection == Direction::Left) {
        endPos = QPoint(-this->frameGeometry().width() + mSpacingToEdge, this->y());
    } else if (mDirection == Direction::Right) {
        endPos = QPoint(mScreenWidth - mSpacingToEdge, this->y());
    }
    mAnim->setEndValue(endPos);

    mAnim->start();
}

void MainWindow::showWidget()
{
    if (mAnim == nullptr) {
        mAnim = new QPropertyAnimation(this, "pos", this);
    }
    mAnim->setDuration(200);
    mAnim->setStartValue(this->pos());

    QPoint endPos;
    if (mDirection == Direction::Up) {
        endPos = QPoint(this->x(), mSpacingToEdge);
    } else if (mDirection == Direction::Left) {
        endPos = QPoint(mSpacingToEdge, this->y());
    } else if (mDirection == Direction::Right) {
        endPos = QPoint(mScreenWidth - this->frameGeometry().width() - mSpacingToEdge, this->y());
    }
    mAnim->setEndValue(endPos);
    mAnim->start();
}

void MainWindow::on_actionClose_triggered()
{
    qApp->quit();
}
