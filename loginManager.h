#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include <qboxlayout.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <quiloader.h>
#include <QWidget>
#include <QScrollArea>
#include <QUiLoader>
#include "qtmaterialtextfield.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialflatbutton.h"


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

public slots:
    void switchView();

private:
    QUiLoader* uiLoader;
    QVBoxLayout* mainLayout;
    QWidget* loginPageWidget;

    QWidget* frameSelectWidget;
    QWidget* frameCreateWidget;

    QtMaterialTextField* mtfCreateUsername;
    QtMaterialTextField* mtfCreatePassword;
    QtMaterialRaisedButton* mrbCreateButton;

    QScrollArea* saSelect;
    QPushButton* pbSwitchView;
    QVector<QPushButton*> selectUserList;
};

#endif