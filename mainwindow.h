#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QVBoxLayout>

#include "loginmanager.h"
#include "navigationdrawer.h"
#include "qtmaterialappbar.h"
#include "qtmaterialdrawer.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialsnackbar.h"
#include "qtmaterialtextfield.h"
#include "settingsmanager.h"

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
    void signOut();
    void settingsClicked();
    void homeClicked();

private:
    Ui::MainWindow* ui;

    UserInfo* user = nullptr;

    LoginManager* loginMan;
    SettingsManager* settingsMan;
    NavigationDrawer* drawerWidget;
    QtMaterialAppBar* appbar;
    QtMaterialDrawer* drawer;
    QVBoxLayout* drawerLayout;
    QtMaterialSnackbar* snackbar;

    QLabel* lAppBarTitle;
};
#endif  // MAINWINDOW_H
