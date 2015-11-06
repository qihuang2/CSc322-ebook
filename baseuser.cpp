#include "baseuser.h"

BaseUser::BaseUser(QString username, int userType)
{
    m_username = username;
    m_userType = userType;
}

QString BaseUser::getUsername(){
    return m_username;
}

int BaseUser::getUserType(){
    return m_userType;
}
