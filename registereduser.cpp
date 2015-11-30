#include "registereduser.h"
#include <QString>
#include "userinfodb.h"


RegisteredUser::RegisteredUser(QString username, int userType) : BaseUser(username, userType)
{
    m_userInfoDB = new UserInfoDB();
}

QString RegisteredUser::getDateCreated(){
    return m_userInfoDB->getStringForKey(m_username, "created");
}

int RegisteredUser::getNumOfComplaints(){
    return m_userInfoDB->getIntForKey(m_username, "complaints");
}

int RegisteredUser::getNumOfCredits(){
    return m_userInfoDB->getIntForKey(m_username, "credits");
}

int RegisteredUser::getNumOfUploads(){
    return m_userInfoDB->getIntForKey(m_username, "uploads");
}

void RegisteredUser::incrementComplaintsBy(int complaints){
    m_userInfoDB->setIntForKey(m_username, "complaints", getNumOfComplaints() + complaints);
}

void RegisteredUser::changeCreditsBy(int credits){
    m_userInfoDB->setIntForKey(m_username, "credits", getNumOfCredits() + credits);
}

void RegisteredUser::incrementNumOfUploads(){
    m_userInfoDB->setIntForKey(m_username, "uploads", getNumOfUploads() + 1);
}
