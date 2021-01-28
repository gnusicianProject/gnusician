#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QResource>
#include <algorithm>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Set ~/.gnusician as working directory
    QDir dirObj;
    if (!QFileInfo::exists(QDir::homePath() + "/.gnusician"))
        dirObj.mkdir(QDir::homePath() + "/.gnusician");
    QDir::setCurrent(QDir::homePath() + "/.gnusician");
    if (!QFileInfo::exists("users")) dirObj.mkdir("users");

    return a.exec();
}
