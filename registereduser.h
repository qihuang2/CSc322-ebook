#ifndef REGISTEREDUSER_H
#define REGISTEREDUSER_H

#include "baseuser.h"
class QString;
class UserInfoDB;
class QSqlQuery;
class DocumentsDB;

class RegisteredUser : public BaseUser
{
public:
    RegisteredUser(QString username);

    //getters
    int getNumOfCredits();
    int getNumOfDeletedBooks();
    QString getDateCreated();
    int getNumOfUploads();

    //setters
    void changeCreditsBy(int);
    void incrementBooksDeletedBy(int);
    void incrementNumOfUploads();

    //this returns documents currently in state 0, 1 or 2
    //0 meaning SU still needs to approve or deny
    //1 - SU denied and gave counter offer
    //2 - SU accepted and no counter offer
    QSqlQuery getPendingDocuments();

    void uploadDocument(QString title, QString author, int genre, QString summary, int suggestedCredits);


    //approved or rejects the document or accept/rejects superuser counter offer
    //even if super user doesn't counteroffer, we still need to approve book again
    //@para approve - user approves or rejects
    //credits is already taken into acount by this function
    //you don't change to change the users credits
    void approveSuperUserCounterForBook(int uid, bool approve);

    //gift credits
    void giftCreditsToUser(int, QString);

    //get list of all users
    QSqlQuery getAllUsers();

protected:
    UserInfoDB* m_userInfoDB;
    DocumentsDB* m_docDB;
};

#endif // REGISTEREDUSER_H
