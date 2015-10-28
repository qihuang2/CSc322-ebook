#ifndef BASEUSER_H
#define BASEUSER_H

#include <QString>

class BaseUser
{
public:
    BaseUser(QString username, int userType);

    QString getUsername();
    int getUserType();

protected:
    QString m_username;
    int m_userType;

};

#endif // BASEUSER_H
