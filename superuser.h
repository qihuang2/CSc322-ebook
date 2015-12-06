#ifndef SUPERUSER_H
#define SUPERUSER_H

class QSqlQuery;
class QString;
#include "registereduser.h"

class SuperUser : public RegisteredUser
{
public:
    SuperUser(QString username);

    //Returns list of documents that need a Superusers Approval
    QSqlQuery getSupersPendingDocuments();

    void acceptDocumentWithUID(int bookID);
    void declineDocumentWithUID(int bookID, int counterOffer);
    void approveSuperUserCounterForBook(int uid, bool approve);

    //ban user
    void banUser(QString username);

    //delete book
    void deleteBookWithUID(int uid);

    //list of documents that have complaints
    //NOTE: The documents only have the following information:
    //username : name of user who reported the book
    //book_id : book id of the book
    //reason : reason for reporting the book
    QSqlQuery getAllDocumentsWithComplaints();

    void changeCreditsBy(int credits);
};

#endif // SUPERUSER_H
