#ifndef USERINFODB_H
#define USERINFODB_H

//This DB is used to manipulate the 'user_info' table


#include "maindb.h"
class QString;

class UserInfoDB : public MainDB
{
public:
    UserInfoDB();

    void banUser(QString username);
    void unbanUser(QString username);

    //return int value for key; credits, complaints, uploads
    int getIntForKey(QString username, QString key);

    //return QString value for key; Date account created
    QString getStringForKey(QString username, QString key);

    //set new int value for key
    void setIntForKey(QString username, QString key, int value);
};

#endif // USERINFODB_H
