#ifndef SUPERUSER_H
#define SUPERUSER_H

#include "baseuser.h"
class QSqlQuery;
class QString;

class SuperUser : BaseUser
{
public:
    SuperUser(QString username);

    //Returns list of documents that need a Superusers Approval
    QSqlQuery getSupersPendingDocuments();

    //accept the book without a counter offer
    void acceptDocumentWithUID(int bookID);

    //decline book and offer counter offer
    void declineDocumentWithUID(int bookID, int counterOffer);

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


};

#endif // SUPERUSER_H
