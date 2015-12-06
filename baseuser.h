#ifndef BASEUSER_H
#define BASEUSER_H

#include <QString>

class BaseUser
{
public:
    BaseUser();

    typedef enum _UserType {
        VISITING,
        REGISTERED,
        SUPER
    } UserType;

    QString getUsername();
    UserType getUserType();

protected:
    QString m_username;
    UserType m_userType;
};

#endif // BASEUSER_H
