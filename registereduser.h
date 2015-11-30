#ifndef REGISTEREDUSER_H
#define REGISTEREDUSER_H

#include "baseuser.h"
class QString;
class UserInfoDB;

class RegisteredUser:public BaseUser
{
public:
    RegisteredUser(QString username, int userType = 1);
    ~RegisteredUser();

    //getters
    int getNumOfCredits();
    int getNumOfComplaints();
    QString getDateCreated();
    int getNumOfUploads();

    //setters
    void changeCreditsBy(int credits);
    void incrementComplaintsBy(int complaints);
    void incrementNumOfUploads();

protected:
    UserInfoDB* m_userInfoDB;
};

#endif // REGISTEREDUSER_H
