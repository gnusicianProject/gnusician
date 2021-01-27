#include <qapplication.h>
#include <qcoreapplication.h>
#include <qdir.h>
#include <qfileinfo.h>
#include "mainwindow.h"

#include <QApplication>
#include <algorithm>
#include <QResource>
#include <QDir>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Set ~/.gnusician as working directory
    QDir dirObj;
    if(!QFileInfo::exists(QDir::homePath()+"/.gnusician"))
        dirObj.mkdir(QDir::homePath()+"/.gnusician");
    QDir::setCurrent(QDir::homePath()+"/.gnusician");
    if(!QFileInfo::exists("users"))
        dirObj.mkdir("users");

    return a.exec();
}
