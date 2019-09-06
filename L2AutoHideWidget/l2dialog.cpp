#include "l2dialog.h"
#include "ui_l2dialog.h"

L2Dialog::L2Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::L2Dialog)
{
    ui->setupUi(this);
}

L2Dialog::~L2Dialog()
{
    delete ui;
}
