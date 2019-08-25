#ifndef FRAMELESSMAINWINDOW_H
#define FRAMELESSMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class FramelessMainWindow;
}

class FramelessMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FramelessMainWindow(QWidget *parent = nullptr);
    ~FramelessMainWindow();

private:
    Ui::FramelessMainWindow *ui;
};

#endif // FRAMELESSMAINWINDOW_H
