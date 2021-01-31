#include "mainwindow.h"

#include <QBoxLayout>
#include <QDebug>
#include <QSpacerItem>

#include "./ui_mainwindow.h"
#include "LoginManager.h"
#include "NavigationDrawer.h"
#include "UserInfo.h"
#include "common.h"
#include "qtmaterialappbar.h"
#include "qtmaterialdrawer.h"
#include "qtmaterialiconbutton.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialsnackbar.h"
#include "qtmaterialtextfield.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initUi();
    this->connectSignals();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::initUi()
{
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
    this->setWindowTitle("Gnusician");
    // Create the app bar
    this->appbar = new QtMaterialAppBar(this);
    QtMaterialIconButton *appbarButton =
        new QtMaterialIconButton(QtMaterialTheme::icon("navigation", "menu"));
    appbarButton->setIconSize(QSize(24, 24));
    this->appbar->appBarLayout()->addWidget(appbarButton);
    this->appbar->appBarLayout()->addStretch(1);
    this->appbar->setFixedHeight(56);
    this->appbar->setBackgroundColor(QColor(QUEENBLUE));
    appbarButton->setColor(Qt::white);
    appbarButton->setFixedSize(QSize(42, 42));

    // Create the app drawer
    this->drawer = new QtMaterialDrawer(this);
    this->drawerLayout = new QVBoxLayout(this->drawer);
    drawerLayout->setMargin(0);
    this->drawer->setClickOutsideToClose(false);
    this->drawer->setDrawerWidth(300);
    this->drawer->setOverlayMode(true);
    this->drawer->setDrawerLayout(drawerLayout);
    connect(appbarButton, SIGNAL(clicked()), this->drawer, SLOT(openDrawer()));

    // Create the snackbar
    this->snackbar = new QtMaterialSnackbar(this);
    this->snackbar->setClickToDismissMode(true);

    // Order widgets in layouts
    ui->mainLayout->addWidget(this->appbar, 0, 0);
    ui->mainLayout->addWidget(ui->stackedWidget, 1, 0);

    // Create the login page
    this->loginMan = new LoginManager(ui->loginPage);
    ui->vlLoginPage->addWidget(this->loginMan);
    ui->vlLoginPage->setAlignment(Qt::AlignCenter);

    this->drawerWidget = new NavigationDrawer(this->drawer);
    drawerLayout->addWidget(this->drawerWidget);
}

void MainWindow::connectSignals()
{
    connect(this->loginMan, SIGNAL(loginDone(UserInfo *)), this,
            SLOT(loginDone(UserInfo *)));
    connect(this->loginMan, SIGNAL(loginDone(UserInfo *)), this->drawerWidget,
            SLOT(signIn(UserInfo *)));
    connect(this->loginMan, SIGNAL(snackMessage(QString)), this->snackbar,
            SLOT(addMessage(QString)));
    connect(this->drawerWidget, SIGNAL(signOutClicked()), this,
            SLOT(signOut()));
    connect(this->drawerWidget, SIGNAL(signOutClicked()), this->drawerWidget,
            SLOT(signOutSlot()));
    connect(this->drawerWidget, SIGNAL(settingsClicked()), this,
            SLOT(settingsClicked()));
    connect(this->drawerWidget, SIGNAL(homeClicked()), this,
            SLOT(homeClicked()));
}

void MainWindow::loginDone(UserInfo *user)
{
    this->user = user;
    ui->stackedWidget->setCurrentWidget(ui->libraryPage);
    ui->lLibraryTitle->setText("Libray Page: Welcome " + user->name);
}

void MainWindow::signOut()
{
    this->loginMan->deleteLater();
    this->drawerWidget->deleteLater();
    this->user = nullptr;

    this->loginMan = new LoginManager(ui->loginPage);
    ui->vlLoginPage->addWidget(this->loginMan);
    ui->stackedWidget->setCurrentWidget(ui->loginPage);

    this->drawerWidget = new NavigationDrawer(this->drawer);
    this->drawerLayout->addWidget(this->drawerWidget);
    this->connectSignals();

    this->drawer->closeDrawer();
}

void MainWindow::settingsClicked()
{
    ui->stackedWidget->setCurrentWidget(ui->settingsPage);
    this->drawer->closeDrawer();
}

void MainWindow::homeClicked()
{
    if (this->user == nullptr)
        ui->stackedWidget->setCurrentWidget(ui->loginPage);
    else
        ui->stackedWidget->setCurrentWidget(ui->libraryPage);
    this->drawer->closeDrawer();
}