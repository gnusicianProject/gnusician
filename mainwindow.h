#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>

#include "qtmaterialappbar.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialtextfield.h"

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

    QVBoxLayout* vlLogin;
    QLabel* loginPageTitle;
    QtMaterialAppBar* appbar;
    QtMaterialRaisedButton* raisedButton;
    QtMaterialTextField* usernameField;
};
#endif // MAINWINDOW_H
