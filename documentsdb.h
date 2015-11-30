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



// TODO : add KEY: book_summary


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
    void addDocument(QString title, QString posted_by, int genre);

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
};

#endif // DOCUMENTSDB_H
