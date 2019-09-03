#include <QApplication>
#include "l2mainwindow.h"
#include "l2framelessmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if 0
    L2FramelessMainWindow w;
#else
    L2MainWindow w;
#endif
    w.resize(400, 600);
    w.show();

    return a.exec();
}
