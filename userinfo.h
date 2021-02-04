#ifndef UserInfo_H
#define UserInfo_H

#include <QIcon>
#include <QString>

class UserInfo
{
public:
    UserInfo();
    ~UserInfo();

    QString name;
    QString username;
    QString password;
    QString avatar;

    unsigned level = 0;
    float hoursPlayed = 0;
    QString libraryLocation;

private:
};

#endif