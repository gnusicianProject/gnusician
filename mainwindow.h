#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>

#include "qtmaterialappbar.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialtextfield.h"
#include "qtmaterialdrawer.h"

#include "loginManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initUi();

private:
    Ui::MainWindow *ui;

    loginManager* loginMan;
    QtMaterialAppBar* appbar;
    QtMaterialDrawer* drawer;
};
#endif // MAINWINDOW_H
