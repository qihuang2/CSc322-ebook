#include "baseuser.h"

BaseUser::BaseUser()
{
    m_username = "Visiting User";
    m_userType = VISITING;
}

QString BaseUser::getUsername(){
    return m_username;
}

BaseUser::UserType BaseUser::getUserType(){
    return m_userType;
}
