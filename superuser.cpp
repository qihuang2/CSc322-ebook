#include "superuser.h"

SuperUser::SuperUser(QString username) : RegisteredUser(username)
{
    m_username = username;
    m_userType = SUPER;
}

void SuperUser::changeCreditsBy(int credits) {
    credits = 0;   // to silence warning
}
