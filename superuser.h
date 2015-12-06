#ifndef SUPERUSER_H
#define SUPERUSER_H

#include "registereduser.h"

class SuperUser : public RegisteredUser
{
public:
    SuperUser(QString username);

    void changeCreditsBy(int credits);
};

#endif // SUPERUSER_H
