#include "loginmanager.h"

#include <QBoxLayout>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPixmap>
#include <QToolButton>

#include "common.h"
#include "lib/qtmaterialtheme.h"
#include "qtmaterialavatar.h"
#include "qtmaterialflatbutton.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialscrollbar.h"
#include "qtmaterialtextfield.h"

LoginManager::LoginManager(QWidget* parent)
    : QWidget(parent), ui(new Ui::LoginManager)
{
    ui->setupUi(this);
    ui->vlLoginPage->setAlignment(Qt::AlignHCenter);

    // Set button texts
    ui->mrbCreateButton->setText("Create");
    ui->mrbAvatarButton->setText("Done");
    ui->mtfCreateUsername->setLabel("Username");
    ui->mtfCreatePassword->setLabel("Password (optional)");
    ui->mtfCreateName->setLabel("Name");

    // Tweak styles
    ui->mrbCreateButton->setHaloVisible(false);
    ui->mrbCreateButton->setBackgroundColor(QColor(SAFETYORANGE));
    ui->mrbAvatarButton->setHaloVisible(false);
    ui->mrbAvatarButton->setBackgroundColor(QColor(SAFETYORANGE));
    ui->mtfCreateUsername->setInkColor(QColor(DARKSKY));
    ui->mtfCreatePassword->setInkColor(QColor(DARKSKY));
    ui->mtfCreateName->setInkColor(QColor(DARKSKY));
    common::cardStyle(this, ui->frameCreateWidget);
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
    connect(ui->mrbCreateButton, SIGNAL(clicked()), this,
            SLOT(validateAccount()));
    connect(ui->mrbAvatarButton, SIGNAL(clicked()), this,
            SLOT(createAccount()));
    connect(ui->mtfCreateUsername, SIGNAL(returnPressed()),
            ui->mrbCreateButton, SIGNAL(clicked()));
    connect(ui->mtfCreatePassword, SIGNAL(returnPressed()),
            ui->mrbCreateButton, SIGNAL(clicked()));
    connect(ui->mtfCreateName, SIGNAL(returnPressed()), ui->mrbAvatarButton,
            SIGNAL(clicked()));
}

LoginManager::~LoginManager()
{
    delete ui;
    foreach (UserInfo* user, this->userList.values())
        delete user;
}

void LoginManager::loadAvatars()
{
    this->buttonGroup = new QButtonGroup(ui->wAvatarGrid);
    this->createAvatarButton(":/avatars/avatarMouse.svg");
    this->createAvatarButton(":/avatars/avatarCat.svg");
    this->createAvatarButton(":/avatars/avatarDog.svg");
    this->createAvatarButton(":/avatars/avatarBison.svg");
    this->createAvatarButton(":/avatars/avatarPigeon.svg");
    this->createAvatarButton(":/avatars/avatarSheep.svg");
    this->createAvatarButton(":/avatars/avatarDeer.svg");
    this->createAvatarButton(":/avatars/avatarDinosaur.svg");
}

void LoginManager::loadUsers()
{
    QDir users(GNUSICIAN_USERS_DIR);
    QStringList files = users.entryList();
    files.removeAll(".");
    files.removeAll("..");

    foreach (QString file, files)
    {
        UserInfo* user = this->getUser(GNUSICIAN_USERS_DIR + file);
        QPushButton* button = new QPushButton(ui->scrollAreaWidgetContents);
        this->userList[button] = user;
        button->setText("    " + user->name);
        button->setMinimumHeight(128);
        button->setIcon(QIcon(user->avatar));
        button->setIconSize(QSize(80, 80));
        common::cardStyle(ui->scrollAreaWidgetContents, button);
        ui->vlScrollArea->addWidget(button);
        connect(button, &QPushButton::clicked, this,
                [this, button]() { emit loginDone(this->userList[button]); });
    }

    if (this->userList.empty()) ui->pbSwitchView->animateClick();
}

void LoginManager::switchView()
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

void LoginManager::validateAccount()
{
    // Cache username and password from text fields
    QString username = ui->mtfCreateUsername->text();
    QString password = ui->mtfCreatePassword->text();

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
    this->user = new UserInfo();
    this->user->username = username;
    this->user->password = password;

    ui->mtfCreateName->setText(username);
    ui->pbSwitchView->hide();
    ui->frameCreateWidget->setEnabled(false);
    ui->frameAvatarWidget->show();
}

void LoginManager::createAccount()
{
    this->user->name = ui->mtfCreateName->text();
    this->user->avatar = this->buttonGroup->checkedButton()->text();
    this->user->hoursPlayed = 0;
    this->user->level = 0;
    this->user->libraryLocation = QDir::homePath();
    this->createUserJson(this->user);
    emit loginDone(this->user);
}

UserInfo* LoginManager::getUser(QString path)
{
    QFile* file = new QFile(path);
    file->open(QIODevice::ReadOnly);
    QString content = file->readAll();
    file->close();

    QJsonDocument doc = QJsonDocument::fromJson(content.toUtf8());
    QJsonObject jobject = doc.object();

    this->user = new UserInfo();
    this->user->username = jobject["username"].toString();
    this->user->password = jobject["password"].toString();
    this->user->avatar = jobject["avatar"].toString();
    this->user->name = jobject["name"].toString();
    this->user->level = jobject["level"].toInt();
    this->user->hoursPlayed = jobject["hoursPlayed"].toDouble();
    this->user->libraryLocation = jobject["libraryLocation"].toString();

    return user;
}

bool LoginManager::validateUsername(QString uname)
{
    if (not uname.isEmpty())
        if (uname.contains(QRegExp("^[a-zA-Z0-9_]*$"))) return true;
    return false;
}

bool LoginManager::validatePassword(QString pass) { return true; }

bool LoginManager::checkForExistingUser(QString uname)
{
    foreach (UserInfo* user, this->userList.values())
        if (user->username == uname) return false;
    return true;
}

void LoginManager::createAvatarButton(QString path)
{
    static int cnt = 0;
    QToolButton* avatarButton = new QToolButton(ui->wAvatarGrid);
    avatarButton->setCheckable(true);
    avatarButton->setIcon(QIcon(path));
    avatarButton->setIconSize(QSize(100, 100));
    avatarButton->setFixedSize(110, 110);
    avatarButton->setAutoExclusive(true);
    avatarButton->setText(path);
    avatarButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    common::cardStyle(ui->wAvatarGrid, avatarButton);
    this->buttonGroup->addButton(avatarButton);
    ui->glAvatarGrid->addWidget(avatarButton, cnt / 4, cnt % 4);
    avatarButton->setChecked(true);
    cnt++;
}

void LoginManager::createUserJson(UserInfo* newUser)
{
    QJsonObject recordObject;
    recordObject.insert("name", QJsonValue::fromVariant(newUser->name));
    recordObject.insert("username", QJsonValue::fromVariant(newUser->username));
    recordObject.insert("password", QJsonValue::fromVariant(newUser->password));
    recordObject.insert("avatar", QJsonValue::fromVariant(newUser->avatar));

    QJsonObject appDataObject;
    appDataObject.insert("level", QJsonValue::fromVariant(newUser->level));
    appDataObject.insert("hoursPlayed",
                         QJsonValue::fromVariant(newUser->hoursPlayed));
    appDataObject.insert("libraryLocation", newUser->libraryLocation);
    recordObject.insert("appData", appDataObject);

    QJsonDocument doc(recordObject);
    QFile file(GNUSICIAN_USERS_DIR + newUser->username + ".json");
    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson());
}