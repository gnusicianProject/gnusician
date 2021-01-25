#include "loginManager.h"

#include <qboxlayout.h>
#include <qlabel.h>
#include <qline.h>
#include <qscrollarea.h>
#include <qsizepolicy.h>
#include <qwidget.h>

#include "qtmaterialflatbutton.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialtextfield.h"

loginManager::loginManager(QWidget* parent) : QWidget(parent)
{
    // Create loginManager widget and layout
    this->mainLayout = new QVBoxLayout(this);
    this->setLayout(this->mainLayout);

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
    this->selectAccoutWidget->setLayout(this->vlSelectAccout);
    this->lSelectAccout = new QLabel(this->selectAccoutWidget);
    this->saSelect = new QScrollArea(this->selectAccoutWidget);
    this->vlSelectScrollArea = new QVBoxLayout(this->selectAccoutWidget);

    this->selectAccoutWidget->setLayout(this->vlSelectAccout);
    this->saSelect->setLayout(this->vlSelectScrollArea);

    this->mainLayout->addWidget(this->selectAccoutWidget);
    this->vlSelectAccout->addWidget(this->lSelectAccout);
    this->vlSelectAccout->addWidget(this->saSelect);

    this->selectAccoutWidget->setObjectName("selectAccountWidget");
    this->lSelectAccout->setText("Users");
    this->lSelectAccout->setFont(font);
    this->selectAccoutWidget->setStyleSheet(
        "QWidget#selectAccountWidget{ border: 1px solid rgb(210,210,210); "
        "border-radius: 10px;} ");

    QtMaterialFlatButton* butt = new QtMaterialFlatButton(this->selectAccoutWidget);
    this->vlSelectScrollArea->addWidget(butt);
    butt->setText("user 1");
    butt->setHaloVisible(false);
    butt->setIcon(QIcon(":/"));
}

loginManager::~loginManager() {}