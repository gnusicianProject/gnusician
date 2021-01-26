#include "mainwindow.h"

#include <QApplication>
#include <algorithm>
#include <QResource>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
