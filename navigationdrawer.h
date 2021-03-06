#ifndef NAVIGATIONDRAWER_H
#define NAVIGATIONDRAWER_H

#include <QLabel>
#include <QWidget>

#include "ui_navigationdrawer.h"
#include "common.h"

namespace ui
{
class NavigationDrawer;
}
QT_END_NAMESPACE

class NavigationDrawer : public QWidget
{
    Q_OBJECT
public:
    NavigationDrawer(QWidget* parent = nullptr);
    ~NavigationDrawer();

    void connectSignals();

public slots:
    void signIn(UserInfo* user);
    void signOutSlot();

signals:
    void signOutClicked();
    void settingsClicked();
    void homeClicked();

private:
    Ui::NavigationDrawer* ui;
    QPushButton* avatar;
    QLabel* username;
};

#endif