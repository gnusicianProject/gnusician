#include "loginManager.h"

#include <QDebug>

#include <qboxlayout.h>
#include <qlabel.h>
#include <qline.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qscrollarea.h>
#include <qsizepolicy.h>
#include <quiloader.h>
#include <qwidget.h>

#include <QFile>
#include <QBoxLayout>

#include "lib/qtmaterialtheme.h"
#include "qtmaterialflatbutton.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialtextfield.h"
#include "qtmaterialavatar.h"
#include "qtmaterialscrollbar.h"
#include "common.h"

loginManager::loginManager(QWidget* parent) : QWidget(parent)
{
    // Load the UI from the ui file with QUiLoader
    this->uiLoader = new QUiLoader(this);
    QFile* file = new QFile(":/forms/loginPage.ui");
    file->open(QFile::ReadOnly);
    this->loginPageWidget = uiLoader->load(file, this);
    file->close();

    QVBoxLayout* vlCreate = this->loginPageWidget->findChild<QVBoxLayout*>("vlCreate");
    this->frameCreateWidget = this->loginPageWidget->findChild<QWidget*>("frameCreateWidget");
    this->frameSelectWidget = this->loginPageWidget->findChild<QWidget*>("frameSelectWidget");
    this->pbSwitchView = this->loginPageWidget->findChild<QPushButton*>("pbSwitchView");

    this->mainLayout = new QVBoxLayout(this);
    this->mainLayout->setAlignment(Qt::AlignCenter);
    this->setLayout(this->mainLayout);
    this->mainLayout->addWidget(this->loginPageWidget);

    this->mtfCreateUsername = new QtMaterialTextField(frameCreateWidget);
    this->mtfCreatePassword = new QtMaterialTextField(frameCreateWidget);
    this->mrbCreateButton = new QtMaterialRaisedButton(frameCreateWidget);
    vlCreate->addWidget(this->mtfCreateUsername);
    vlCreate->addWidget(this->mtfCreatePassword);
    vlCreate->addWidget(this->mrbCreateButton);

    this->mrbCreateButton->setText("Create");
    this->mtfCreateUsername->setLabel("Username");
    this->mtfCreatePassword->setLabel("Password (optional)");

    this->mrbCreateButton->setHaloVisible(false);
    this->mrbCreateButton->setBackgroundColor(QColor(SAFETYORANGE));
    this->mtfCreateUsername->setInkColor(QColor(DARKSKY));
    this->mtfCreatePassword->setInkColor(QColor(DARKSKY));

    connect(this->pbSwitchView, SIGNAL(clicked()), this, SLOT(switchView()));

    this->frameCreateWidget->hide();

/*
    // Create loginManager widget and layout

    this->createAccoutWidget = new QWidget(this);
    this->createAccoutWidget->setObjectName("createAccountWidget");
    this->mainLayout->addWidget(this->createAccoutWidget);
    this->vlCreateAccout = new QVBoxLayout(this->createAccoutWidget);
    this->createAccoutWidget->setLayout(this->vlCreateAccout);

    // Create widgets instances
    this->lCreateAccout = new QLabel(this);
    this->mtfCreateUsername = new QtMaterialTextField(this->createAccoutWidget);
    this->mtfCreatePassword = new QtMaterialTextField(this->createAccoutWidget);
    this->mrbCreateButton =
        new QtMaterialRaisedButton(this->createAccoutWidget);

    // Place widgets in layout
    this->createAccoutWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    this->vlCreateAccout->addWidget(this->lCreateAccout);
    this->vlCreateAccout->addWidget(this->mtfCreateUsername);
    this->vlCreateAccout->addWidget(this->mtfCreatePassword);
    this->vlCreateAccout->addWidget(this->mrbCreateButton);

    // Set text on widgets
    this->lCreateAccout->setText("New User");
    this->mrbCreateButton->setText("Create");
    this->mtfCreateUsername->setLabel("Username");
    this->mtfCreatePassword->setLabel("Password (optional)");

    // Configure style, size, fonts, etc.
    this->setMaximumWidth(500);
    this->createAccoutWidget->setStyleSheet(
        "QWidget#createAccountWidget{ border: 1px solid rgb(210,210,210); "
        "border-radius: 10px;} ");
    QFont font = this->lCreateAccout->font();
    font.setBold(true);
    font.setPointSize(24);
    this->lCreateAccout->setFont(font);
    this->lCreateAccout->setMaximumHeight(50);

    this->mrbCreateButton->setHaloVisible(false);
    this->mrbCreateButton->setBackgroundColor(QColor("#00796B"));

    // Create user selection section
    this->selectAccoutWidget = new QWidget(this);
    this->vlSelectAccout = new QVBoxLayout(this->selectAccoutWidget);
    this->lSelectAccout = new QLabel(this->selectAccoutWidget);
    this->saSelect = new QScrollArea(this->selectAccoutWidget);

    this->selectAccoutWidget->setLayout(this->vlSelectAccout);
    QWidget* widget = new QWidget(this->saSelect);
    this->vlSelectScrollArea = new QVBoxLayout(widget);
    widget->setLayout(this->vlSelectScrollArea);
    this->saSelect->setWidget(widget);
    widget->show();

    this->mainLayout->addWidget(this->selectAccoutWidget);
    this->vlSelectAccout->addWidget(this->lSelectAccout);
    this->vlSelectAccout->addWidget(this->saSelect);

    this->selectAccoutWidget->setObjectName("selectAccountWidget");
    this->lSelectAccout->setText("Users");
    this->lSelectAccout->setFont(font);
    this->selectAccoutWidget->setStyleSheet(
        "QWidget#selectAccountWidget{ border: 1px solid rgb(210,210,210); "
        "border-radius: 10px;} ");

    //butt->setIcon(QIcon(":/avatars/test.png"));
    //butt->setIconSize(QSize(24,24));

    // try adding icon to regular push button
    QPushButton* pb = new QPushButton(widget);
    this->vlSelectScrollArea->addWidget(pb);
    pb->setIcon(QIcon(":/avatars/avatarPigeon.svg"));
    pb->setStyleSheet("text-align:left");
    pb->setText("Arijan");
    pb->setFlat(true);
    pb->setMinimumHeight(36);
    pb->setIconSize(QSize(32,32));
    pb->setFont(font);
    QPushButton* pb2 = new QPushButton(widget);
    this->vlSelectScrollArea->addWidget(pb2);
    pb2->setIcon(QIcon(":/avatars/avatarCat.svg"));
    pb2->setStyleSheet("text-align:left");
    pb2->setText("John");
    pb2->setFlat(true);
    pb2->setMinimumHeight(36);
    pb2->setIconSize(QSize(64,32));
    pb2->setFont(font);
    widget->setMinimumHeight(200);
    widget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
    widget->setMinimumWidth(400);
    this->saSelect->setMinimumHeight(200);
    this->saSelect->setMinimumWidth(400);
    this->saSelect->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
    this->saSelect->setStyleSheet("QScrollArea{border:none; background-color: white}");
    this->saSelect->setVerticalScrollBar(new QtMaterialScrollBar(this->saSelect));
    this->saSelect->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);


    this->pbSwitchView = new QPushButton(this);
    this->mainLayout->addWidget(this->pbSwitchView);
    this->pbSwitchView->setText("Don't have an account? Create one!");
    this->pbSwitchView->setFlat(true);
    connect(this->pbSwitchView, SIGNAL(clicked()), this, SLOT(switchView()));

    this->createAccoutWidget->hide();
    */
}

loginManager::~loginManager() {}

void loginManager::switchView()
{
    if(this->frameCreateWidget->isVisible())
    {
        this->frameCreateWidget->hide();
        this->frameSelectWidget->show();
        this->pbSwitchView->setText("Don't have an account? Create one!");
    }
    else if(this->frameSelectWidget->isVisible())
    {
        this->frameSelectWidget->hide();
        this->frameCreateWidget->show();
        this->pbSwitchView->setText("Have an account? Log in!");
    }
}