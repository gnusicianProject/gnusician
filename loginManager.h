#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include <qboxlayout.h>
#include <qlabel.h>
#include <QWidget>
#include <QScrollArea>
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

private:
    QVBoxLayout* mainLayout;

    QWidget* createAccoutWidget;
    QVBoxLayout* vlCreateAccout;
    QLabel* lCreateAccout;
    QtMaterialTextField* mtfCreateUsername;
    QtMaterialTextField* mtfCreatePassword;
    QtMaterialRaisedButton* mrbCreateButton;

    QWidget* selectAccoutWidget;
    QVBoxLayout* vlSelectAccout;
    QLabel* lSelectAccout;
    QScrollArea* saSelect;
    QVBoxLayout* vlSelectScrollArea;

    QVector<QtMaterialFlatButton*> selectUserList;
};

#endif