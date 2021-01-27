#ifndef USERINFO_H
#define USERINFO_H

#include <QString>

class userInfo
{
public:
    userInfo();
    ~userInfo();

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