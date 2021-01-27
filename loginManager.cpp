#include "loginManager.h"

#include <qboxlayout.h>
#include <qgraphicseffect.h>
#include <qlabel.h>
#include <qline.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qscrollarea.h>
#include <qsizepolicy.h>
#include <quiloader.h>
#include <qwidget.h>

#include <QBoxLayout>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>

#include "common.h"
#include "lib/qtmaterialtheme.h"
#include "qtmaterialavatar.h"
#include "qtmaterialflatbutton.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialscrollbar.h"
#include "qtmaterialtextfield.h"
#include "userInfo.h"

loginManager::loginManager(QWidget* parent)
    : QWidget(parent), ui(new Ui::loginManager)
{
    ui->setupUi(this);
    ui->vlLoginPage->setAlignment(Qt::AlignHCenter);

    this->mtfCreateUsername = new QtMaterialTextField(ui->frameCreateWidget);
    this->mtfCreatePassword = new QtMaterialTextField(ui->frameCreateWidget);
    this->mrbCreateButton = new QtMaterialRaisedButton(ui->frameCreateWidget);
    ui->vlCreate->addWidget(this->mtfCreateUsername);
    ui->vlCreate->addWidget(this->mtfCreatePassword);
    ui->vlCreate->addWidget(this->mrbCreateButton);

    this->mrbCreateButton->setText("Create");
    this->mtfCreateUsername->setLabel("Username");
    this->mtfCreatePassword->setLabel("Password (optional)");

    // Tweak styles
    this->mrbCreateButton->setHaloVisible(false);
    this->mrbCreateButton->setBackgroundColor(QColor(SAFETYORANGE));
    this->mtfCreateUsername->setInkColor(QColor(DARKSKY));
    this->mtfCreatePassword->setInkColor(QColor(DARKSKY));
    common::cardStyle(this, ui->frameCreateWidget);
    common::cardStyle(this, ui->frameSelectWidget);
    QtMaterialScrollBar* scrollBar = new QtMaterialScrollBar(ui->saSelectUser);
    scrollBar->setSliderColor(QColor(DARKSKY));
    scrollBar->setHideOnMouseOut(false);
    ui->saSelectUser->setVerticalScrollBar(scrollBar);

    // Hide the account creation widget
    ui->frameCreateWidget->hide();

    // Load all user json files
    this->loadUsers();

    connect(ui->pbSwitchView, SIGNAL(clicked()), this, SLOT(switchView()));
}

loginManager::~loginManager() {}

void loginManager::loadUsers()
{
    QDir users(GNUSICIAN_USERS_DIR);
    QStringList files = users.entryList();
    files.removeAll(".");
    files.removeAll("..");

    foreach(QString file, files)
    {
        userInfo* user = this->getUser(GNUSICIAN_USERS_DIR+file);
        this->userList.append(user);
        QPushButton* button = new QPushButton(ui->scrollAreaWidgetContents);
        button->setText("   "+user->name);
        button->setFlat(true);
        button->setMinimumHeight(40);
        button->setIcon(QIcon(":/avatars/" + user->avatar));
        button->setIconSize(QSize(32,32));
        button->setStyleSheet("Text-align:left; font-size: 24px;");
        this->userButtonList.append(button);
        ui->vlScrollArea->addWidget(button);
    }
}

void loginManager::switchView()
{
    if (ui->frameCreateWidget->isVisible())
    {
        ui->frameCreateWidget->hide();
        ui->frameSelectWidget->show();
        ui->pbSwitchView->setText("Don't have an account? Create one!");
    }
    else if (ui->frameSelectWidget->isVisible())
    {
        ui->frameSelectWidget->hide();
        ui->frameCreateWidget->show();
        ui->pbSwitchView->setText("Have an account? Log in!");
    }
}

userInfo* loginManager::getUser(QString path)
{
    QFile* file = new QFile(path);
    file->open(QIODevice::ReadOnly);
    QString content = file->readAll();
    file->close();

    QJsonDocument doc = QJsonDocument::fromJson(content.toUtf8());
    QJsonObject jobject = doc.object();

    this->user = new userInfo();
    this->user->username = jobject["username"].toString();
    this->user->password = jobject["password"].toString();
    this->user->avatar = jobject["avatar"].toString();
    this->user->name = jobject["name"].toString();
    this->user->level = jobject["level"].toInt();
    this->user->hoursPlayed = jobject["hoursPlayed"].toDouble();
    this->user->libraryLocation = jobject["libraryLocation"].toString();

    return user;
}