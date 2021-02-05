#ifndef COMMON_H
#define COMMON_H

#include <QGraphicsDropShadowEffect>
#include <QWidget>

// Defines
#define GNUSICIAN_DIR QDir::homePath() + "/.gnusician/"
#define GNUSICIAN_USERS_DIR GNUSICIAN_DIR + "users/"

// Define color pallete
#define CHARCOAL "#2F4858"
#define QUEENBLUE "#33658A"
#define DARKSKY "#86BBD8"
#define HONEY "#F6AE2D"
#define SAFETYORANGE "#F26419"

#define DEFAULT_FONT "Ubuntu"

// Global functions
namespace common
{
void cardStyle(QWidget* parent, QWidget* widget);
}

class UserInfo
{
public:
    QString name;
    QString username;
    QString password;
    QString avatar;

    unsigned level = 0;
    float hoursPlayed = 0;
    QString libraryLocation;

private:
};

class Settings
{
public:
// library settings
// audio settings
// developer options
private:
};

#endif