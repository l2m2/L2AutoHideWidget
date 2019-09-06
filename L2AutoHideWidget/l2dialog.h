#ifndef L2DIALOG_H
#define L2DIALOG_H

#include <QDialog>

namespace Ui {
class L2Dialog;
}

class L2Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit L2Dialog(QWidget *parent = 0);
    ~L2Dialog();

private:
    Ui::L2Dialog *ui;
};

#endif // L2DIALOG_H
