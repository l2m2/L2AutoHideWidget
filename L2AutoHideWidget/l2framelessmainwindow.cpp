#include "framelessmainwindow.h"
#include "ui_framelessmainwindow.h"

FramelessMainWindow::FramelessMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FramelessMainWindow)
{
    ui->setupUi(this);
}

FramelessMainWindow::~FramelessMainWindow()
{
    delete ui;
}
