#include "mainwindow.h"

#include <qcolor.h>
#include <qlabel.h>
#include <qlayoutitem.h>
#include <qnamespace.h>
#include <qsizepolicy.h>

#include <QBoxLayout>
#include <QSpacerItem>

#include "./ui_mainwindow.h"
#include "loginManager.h"
#include "qtmaterialappbar.h"
#include "qtmaterialiconbutton.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialtextfield.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initUi();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::initUi()
{
    this->appbar = new QtMaterialAppBar(this);

    // Create the login page layout (vertical layout)
    this->vlLogin = new QVBoxLayout(ui->loginPage);
    this->vlLogin->setAlignment(Qt::AlignCenter);
    ui->loginPage->setLayout(this->vlLogin);

    /*
        this->raisedButton = new QtMaterialRaisedButton(ui->loginPage);
        this->vlLogin->addWidget(this->raisedButton);
        this->usernameField = new QtMaterialTextField(ui->loginPage);
        this->vlLogin->addWidget(this->usernameField);
        ui->stackedWidget->setCurrentIndex(0);
        */

    // Create the app bar
    QtMaterialIconButton *button =
        new QtMaterialIconButton(QtMaterialTheme::icon("navigation", "menu"));
    button->setIconSize(QSize(24, 24));
    this->appbar->appBarLayout()->addWidget(button);
    this->appbar->appBarLayout()->addStretch(1);
    this->appbar->setMaximumHeight(40);
    this->appbar->setBackgroundColor(QColor("#00796B"));
    button->setColor(Qt::white);
    button->setFixedWidth(42);

    // Create the login page title
    this->loginPageTitle = new QLabel(ui->loginPage);
    this->loginPageTitle->setText("Gnusician");
    QFont titleFont = this->loginPageTitle->font();
    titleFont.setBold(true);
    titleFont.setPointSize(72);
    this->loginPageTitle->setFont(titleFont);
    this->loginPageTitle->setAlignment(Qt::AlignCenter);

    this->loginMan = new loginManager(ui->loginPage);

    QSpacerItem *loginSpacer =
        new QSpacerItem(0, 1000, QSizePolicy::Minimum, QSizePolicy::Expanding);

    // Order widgets in layouts
    ui->mainLayout->addWidget(this->appbar, 0, 0);
    ui->mainLayout->addWidget(ui->stackedWidget, 1, 0);

    this->vlLogin->addWidget(this->loginPageTitle, 0);
    this->vlLogin->addItem(loginSpacer);
    this->vlLogin->addWidget(this->loginMan, 1);
}
