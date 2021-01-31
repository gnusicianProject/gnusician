#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QVBoxLayout>

#include "LoginManager.h"
#include "qtmaterialappbar.h"
#include "qtmaterialdrawer.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialsnackbar.h"
#include "qtmaterialtextfield.h"
#include "UserInfo.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void initUi();
    void connectSignals();

public slots:
    void loginDone(UserInfo*);

private:
    Ui::MainWindow* ui;

    UserInfo* user;

    LoginManager* loginMan;
    QtMaterialAppBar* appbar;
    QtMaterialDrawer* drawer;
    QtMaterialSnackbar* snackbar;
};
#endif  // MAINWINDOW_H
