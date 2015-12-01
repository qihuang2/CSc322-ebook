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
//9     approved:             document has been approved by SU
//10    summary               document summary. LIMITED TO 250 CHARACTERS



class DocumentsDB : public MainDB
{
public:
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
    void addDocument(QString title, QString posted_by, int genre, QString summary);

    //approve uploaded document
    void approveDocumentWithUID(int id);

    //delete document with uid
    void deleteDocumentWithUID(int id);

    //adds 1 complaint to document
    void addComplaintToDocumentWithUID(int id);

    //increment view count of document with u_id == id
    void addViewToDocWithUID(int id);

    //add new rating
    void addRatingToDocWithUID(int id, float newRating);

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
};

#endif // DOCUMENTSDB_H
