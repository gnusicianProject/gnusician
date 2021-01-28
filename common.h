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

// Global functions
namespace common
{
void cardStyle(QWidget* parent, QWidget* widget);
}

#endif