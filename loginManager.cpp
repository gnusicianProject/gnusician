#include "loginManager.h"

#include <qboxlayout.h>
#include <qgraphicseffect.h>
#include <qimage.h>
#include <qlabel.h>
#include <qline.h>
#include <qnamespace.h>
#include <qpixmap.h>
#include <qpushbutton.h>
#include <qregexp.h>
#include <qscrollarea.h>
#include <qsizepolicy.h>
#include <quiloader.h>
#include <qwidget.h>

#include <QBoxLayout>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPixmap>

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
    common::cardStyle(this, ui->frameAvatarWidget);
    QtMaterialScrollBar* scrollBar = new QtMaterialScrollBar(ui->saSelectUser);
    scrollBar->setSliderColor(QColor(DARKSKY));
    scrollBar->setHideOnMouseOut(false);
    ui->saSelectUser->setVerticalScrollBar(scrollBar);

    // Hide the account creation widget
    ui->frameCreateWidget->hide();
    ui->frameAvatarWidget->hide();

    // Load all user json files
    this->loadUsers();
    this->loadAvatars();

    connect(ui->pbSwitchView, SIGNAL(clicked()), this, SLOT(switchView()));
    connect(this->mrbCreateButton, SIGNAL(clicked()), this,
            SLOT(createAccount()));
}

loginManager::~loginManager() {}


void loginManager::loadAvatars()
{
    QPushButton* avatarButton = new QPushButton(ui->frameAvatarWidget);
    avatarButton->setCheckable(true);
    avatarButton->setIcon(QIcon(":/avatars/avatarMouse.svg"));
    avatarButton->setIconSize(QSize(50,50));
    avatarButton->setFixedSize(50,50);
    avatarButton->setFlat(true);
    ui->glAvatar->addWidget(avatarButton,1,0);
}

void loginManager::loadUsers()
{
    QDir users(GNUSICIAN_USERS_DIR);
    QStringList files = users.entryList();
    files.removeAll(".");
    files.removeAll("..");

    foreach (QString file, files)
    {
        userInfo* user = this->getUser(GNUSICIAN_USERS_DIR + file);
        this->userList.append(user);
        QPushButton* button = new QPushButton(ui->scrollAreaWidgetContents);
        button->setText("   " + user->name);
        button->setFlat(true);
        button->setMinimumHeight(40);
        button->setIcon(QIcon(":/avatars/" + user->avatar));
        button->setIconSize(QSize(32, 32));
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

void loginManager::createAccount()
{
    // Cache username and password from text fields
    QString username = this->mtfCreateUsername->text();
    QString password = this->mtfCreatePassword->text();

    // Check if username/password are valid and if user exists
    if (not this->validateUsername(username))
    {
        emit snackMessage(
            "Username cannot contain spaces or special characters");
        return;
    }
    if (not this->validatePassword(password))
    {
        emit snackMessage("Password not valid");
        return;
    }
    if (not this->checkForExistingUser(username))
    {
        emit snackMessage("Username already taken");
        return;
    }

    // Create new user
    this->user = new userInfo();
    this->user->username = username;
    this->user->password = password;

    ui->frameCreateWidget->setEnabled(false);
    ui->frameAvatarWidget->show();
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

bool loginManager::validateUsername(QString uname)
{
    if (uname.contains(QRegExp("^[a-zA-Z0-9_]*$"))) return true;
    return false;
}

bool loginManager::validatePassword(QString pass) { return true; }

bool loginManager::checkForExistingUser(QString uname)
{
    foreach (userInfo* user, this->userList)
        if (user->username == uname) return false;
    return true;
}