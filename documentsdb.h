#ifndef DOCUMENTSDB_H
#define DOCUMENTSDB_H

#include "maindb.h"

class QSqlQuery;


//doc_info has the following columns -
//0     u_id:                 unique book id. The value is automatically incremented so
//                              we don't have to worry about that
//1     title:                title of the book. Limited to 25 characters
//2     posted_by:            username of user who posted document
//3     genre:                genre of book. saved as an int
//4     upload_date:          date document was uploaded
//5     rating:               average rating of book. stored as a float
//6     num_of_ratings:       total number of people who rated the book
//7     views:                total number of people that read the document
//8     num_of_complaints:    number of users who complained about the book
//9     approved:             0 - pending SU approval, 1 - SU denied with counter offer,
//                              2 - SU approved without counter offer, 3 - user approves / approves counter
//10    asking_price          how much the user wants for uplaoding document
//11    counter_offer         SU counter offer for document
//12    summary               document summary. LIMITED TO 250 CHARACTERS
//13    is_deleted            document has been deleted



//the column "approved" has 3 states:
//0 : user just uploaded it. Still need a superUSer to approve it
//1 : super user denied document and has presented a counter offer
//2 : super user approved without a counter offer
//3 : document has been approved by superuser and user confirms the counter offer if counter offer was present




//rating_info has the following columns
//0         username        name of the user
//1         book_id         u_id of the book

//report_info has the following columns:
//0         username        name of user
//1         book_id         book id
//2         reason          reason for report



class DocumentsDB : public MainDB
{
public:

    typedef enum {
        WAITING,
        DENIED,
        COUNTERED,
        CONFIRMED
    } ApprovalStatus;

    DocumentsDB();
    //returns a QSqlQuery object of document where u_id == id
    //
    //to get the title, you can do the following:
    //q = getDocInfoForUID(userID);
    //if (q.first()){
    //qDebug() << q.value(1).toString();
    //}
    QSqlQuery getDocInfoForUID(int id);

    //get QSqlQuery of documents where posted_by == username
    //
    //to loop through it and print each title, you can do the following:
    //q = getDocInfoForUID(userID);
    //while(q.next()) qDebug() << q.value(1).toString();
    QSqlQuery getDocsUploadedByUser(QString username);

    //get QSQLQuery of all documents
    QSqlQuery getAllDocs();

    //add document to doc_info
    //NOTE: summary has to be limited to 250 characters
    void addDocument(QString title, QString posted_by, int genre, QString summary, QString askingPrice);

    //delete document with uid
    void deleteDocumentWithUID(int id);

    //adds 1 complaint to document
    void addComplaintToDocumentWithUID(QString username, int book_id, QString reason);

    //increment view count of document with u_id == id
    void addViewToDocWithUID(int id);

    //add new rating
    void addRatingToDocWithUID(QString username, int id, float newRating);

    //COMMENTS: use this function if we are supporting comments
    void addRatingToDocWithUID(QString username, int id, float newRating, QString comment);

    //return a QString with path to document
    QString getPathToDocWithUID(int id);

    //returns next UID we will use
    //returns -1 if error occurs
    int getNumDocs();

    //returns the last inserted row's UID
    //returns 0 if nothing in table
    /*
     *  NOTE: can use this to rename files :
     *  first add the document to doc_info using addDocument(title, posted_by, genre, summary)
     *  then rename file to getLastInsertRowID() + ".txt"
     */
    int getLastInsertRowUID();

    int getnumSumm(QString);

    QString getSummary(QString);

    //check if user has reported book already
    bool userHasReportedBook(QString username, int book_id);

    //checks if user has rated book
    bool userHasRatedBook(QString username, int book_id);

    //get top 5 most views documents
    QSqlQuery getFiveMostViewed();

    int getbookID(QString, QString, int, float);

    //returns comments of document
    QSqlQuery getCommentsOfDocWithUID(int uid);
};

#endif // DOCUMENTSDB_H
