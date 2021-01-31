#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QResource>
#include <QFontDatabase>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Load fonts from resource
    QFontDatabase::addApplicationFont(":/fonts/Ubuntu-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Ubuntu-Bold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Ubuntu-Medium.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Ubuntu-Light.ttf");
    QApplication::setFont(QFont(":/fonts/Ubuntu-Regular.ttf"));

    // Create MainWindow
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
