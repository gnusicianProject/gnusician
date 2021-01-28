#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QVBoxLayout>

#include "loginManager.h"
#include "qtmaterialappbar.h"
#include "qtmaterialdrawer.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialsnackbar.h"
#include "qtmaterialtextfield.h"
#include "userInfo.h"

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
    void loginDone(userInfo*);

private:
    Ui::MainWindow* ui;

    userInfo* user;

    loginManager* loginMan;
    QtMaterialAppBar* appbar;
    QtMaterialDrawer* drawer;
    QtMaterialSnackbar* snackbar;
};
#endif  // MAINWINDOW_H
