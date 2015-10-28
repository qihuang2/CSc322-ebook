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
    void decrementCreditsBy(int credits);
    void incrementCreditsBy(int credits);
    void incrementComplaintsBy(int complaints);
    void incrementNumOfUploads();

    //When we add a logout feature, we need to close this DB before we create a new User object
    void closeDB();

protected:
    UserInfoDB* m_userInfoDB;
};

#endif // REGISTEREDUSER_H
