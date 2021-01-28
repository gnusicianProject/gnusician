#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include <QButtonGroup>
#include <QScrollArea>
#include <QWidget>

#include "qtmaterialflatbutton.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialtextfield.h"
#include "ui_loginManager.h"
#include "userInfo.h"

namespace ui
{
class loginManager;
}
QT_END_NAMESPACE

/**
 * The loginManager class creates the widgets on the login page.
 * The account picker, and the the new account creation widgets.
 * The loginManager class handles the creation of accounts and (in the future)
 * contacting a server to log in to an account
 */
class loginManager : public QWidget
{
    Q_OBJECT
public:
    loginManager(QWidget* parent = nullptr);
    ~loginManager();

    void loadAvatars();
    void loadUsers();

signals:
    void snackMessage(QString);
    void loginDone(userInfo*);

public slots:
    void switchView();
    void validateAccount();
    void createAccount();

private slots:
    bool validateUsername(QString uname);
    bool validatePassword(QString pass);
    bool checkForExistingUser(QString uname);
    void createAvatarButton(QString path);
    void createUserJson(userInfo*);

private:
    userInfo* getUser(QString path);

    Ui::loginManager* ui;

    QtMaterialTextField* mtfCreateUsername;
    QtMaterialTextField* mtfCreatePassword;
    QtMaterialTextField* mtfCreateName;
    QtMaterialRaisedButton* mrbCreateButton;
    QtMaterialRaisedButton* mrbAvatarButton;

    QMap<QPushButton*, userInfo*> userList;
    userInfo* user;

    QButtonGroup* buttonGroup;
};

#endif