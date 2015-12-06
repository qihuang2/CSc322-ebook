#include "superuser.h"

SuperUser::SuperUser(QString username) : BaseUser()
{
    m_username = username;
    m_userType = SUPER;
}

