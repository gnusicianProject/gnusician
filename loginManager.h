#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include <qboxlayout.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <QWidget>
#include <QScrollArea>
#include "qtmaterialtextfield.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialflatbutton.h"
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

    void loadUsers();


public slots:
    void switchView();

private:
    userInfo* getUser(QString path);

    Ui::loginManager* ui;

    QtMaterialTextField* mtfCreateUsername;
    QtMaterialTextField* mtfCreatePassword;
    QtMaterialRaisedButton* mrbCreateButton;

    QVector<QPushButton*> userButtonList;
    QVector<userInfo*> userList;
    userInfo* user;
};

#endif