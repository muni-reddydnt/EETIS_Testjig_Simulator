#include "mainwindow.h"
#include <QApplication>

MainWindow *mainAppWin;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainAppWin = new MainWindow();
    //MainWindow w;
    //w.show();
    mainAppWin->showFullScreen();

    return a.exec();
}
