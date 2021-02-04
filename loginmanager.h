#ifndef LoginManager_H
#define LoginManager_H

#include <QButtonGroup>
#include <QScrollArea>
#include <QWidget>

#include "userinfo.h"
#include "qtmaterialflatbutton.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialtextfield.h"
#include "ui_loginmanager.h"

namespace ui
{
class LoginManager;
}
QT_END_NAMESPACE

/**
 * The LoginManager class creates the widgets on the login page.
 * The account picker, and the the new account creation widgets.
 * The LoginManager class handles the creation of accounts and (in the future)
 * contacting a server to log in to an account
 */
class LoginManager : public QWidget
{
    Q_OBJECT
public:
    LoginManager(QWidget* parent = nullptr);
    ~LoginManager();

    void loadAvatars();
    void loadUsers();
    void resetLoginManager();

signals:
    void snackMessage(QString);
    void loginDone(UserInfo*);

public slots:
    void switchView();
    void validateAccount();
    void createAccount();

private slots:
    bool validateUsername(QString uname);
    bool validatePassword(QString pass);
    bool checkForExistingUser(QString uname);
    void createAvatarButton(QString path);
    void createUserJson(UserInfo*);

private:
    UserInfo* getUser(QString path);

    Ui::LoginManager* ui;

    QtMaterialTextField* mtfCreateUsername;
    QtMaterialTextField* mtfCreatePassword;
    QtMaterialTextField* mtfCreateName;
    QtMaterialRaisedButton* mrbCreateButton;
    QtMaterialRaisedButton* mrbAvatarButton;

    QMap<QPushButton*, UserInfo*> userList;
    UserInfo* user;

    QButtonGroup* buttonGroup;
};

#endif