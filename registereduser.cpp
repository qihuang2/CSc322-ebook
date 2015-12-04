#include "registereduser.h"
#include <QString>
#include "userinfodb.h"
#include <QtSql>


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


//this returns documents currently in state 0, 1 or 2
//0 meaning SU still needs to approve or deny
//1 - SU denied and gave counter offer
//2 - SU accepted and no counter offer
QSqlQuery RegisteredUser::getPendingDocuments(){
    QSqlQuery query;
    //there is no check to see if this command is run
    //I did it this way so it is easier to iterate through using : while (query.next())
    query.exec("SELECT * FROM doc_info WHERE posted_by = '"+m_username+"' AND approved != 3 AND is_deleted = 0");
    return query;
}

void RegisteredUser::approveSuperUserCounterForBook(int uid){
    QSqlQuery q;
    q.exec("SELECT * FROM doc_info WHERE u_id = "+ QString::number(uid));
    if(q.next()){
        int credits;
        if (q.value(9) == 2 ? true : false) { //has counter offer
            credits = q.value(11).toInt();
        }else{
            credits = q.value(10).toInt();
        }
        changeCreditsBy(credits);
        if(q.exec("UPDATE doc_info SET approved = 3 WHERE u_id = "+QString::number(uid))){
            qDebug()<<"Document approved by RegisterUser";
        }else {
            qDebug()<<"ERROR changing approval state by RU";
        }
    }else {
        qDebug()<<"ERROR approving doc by registered user";
    }
}

void RegisteredUser::rejectSuperUserCounterOffer(int uid){
    QSqlQuery q;
    if(q.exec("UPDATE doc_info SET is_deleted = 1 WHERE u_id = "+QString::number(uid))){
        qDebug()<<"Document rejected by Registered User";
    }else {
        qDebug()<<"ERROR changing approval state by RU";
    }
}
