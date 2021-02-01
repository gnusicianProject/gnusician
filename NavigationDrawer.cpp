#include "NavigationDrawer.h"

#include <QPushButton>

#include "common.h"
#include "ui_NavigationDrawer.h"

NavigationDrawer::NavigationDrawer(QWidget* parent)
    : QWidget(parent), ui(new Ui::NavigationDrawer)
{
    ui->setupUi(this);
    this->connectSignals();
    this->signOutSlot();
}

NavigationDrawer::~NavigationDrawer() {}

void NavigationDrawer::connectSignals()
{
    connect(ui->pbSignOut, SIGNAL(clicked()), this, SIGNAL(signOutClicked()));
    connect(ui->pbSettings, SIGNAL(clicked()), this, SIGNAL(settingsClicked()));
    connect(ui->pbHome, SIGNAL(clicked()), this, SIGNAL(homeClicked()));
}

void NavigationDrawer::signIn(UserInfo* user)
{
    ui->lPlaceholder->hide();
    this->avatar = new QPushButton(ui->frameProfile);
    this->username = new QLabel(ui->frameProfile);
    this->username->setText(user->username);
    this->username->setAlignment(Qt::AlignCenter);
    this->username->setFont(QFont(DEFAULT_FONT, 32, 64));
    this->avatar->setIcon(QIcon(user->avatar));
    this->avatar->setFlat(true);
    this->avatar->setIconSize(QSize(128, 128));
    ui->vlProfile->addWidget(this->avatar);
    ui->vlProfile->addWidget(this->username);
    ui->pbSignOut->setEnabled(true);
}

void NavigationDrawer::signOutSlot()
{
    ui->pbSignOut->setEnabled(false);
    ui->pbTuner->setEnabled(false);
}
