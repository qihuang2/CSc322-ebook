#include "documentsdb.h"
#include <QString>
#include <QDebug>
#include <QtSql>


//returns new average rating of book
float getNewAverageRating(float newRating, float avgRating, int totalNumOfRatings);


DocumentsDB::DocumentsDB() : MainDB()
{
}


QSqlQuery DocumentsDB::getDocInfoForUID(int id){
    QSqlQuery query;
    //if command runs
    query.exec("SELECT * FROM doc_info WHERE u_id = "+QString::number(id));
    return query;
}


QSqlQuery DocumentsDB::getDocsUploadedByUser(QString username){
    QSqlQuery query;
    //there is no check to see if this command is run
    //I did it this way so it is easier to iterate through using : while (query.next())
    query.exec("SELECT * FROM doc_info WHERE posted_by = '"+username+"'");
    return query;
}

QSqlQuery DocumentsDB::getAllDocs(){
    QSqlQuery q;
    q.exec("SELECT * FROM doc_info");
    return q;
}

void DocumentsDB::addDocument(QString title, QString posted_by, int genre){
    QSqlQuery query;
    //add document into doc_info DB with some initial values
    if (query.exec("INSERT INTO doc_info(title,posted_by,genre, upload_date, rating, num_of_ratings, views, num_of_complaints, approved) "
                   "VALUES ('"+title+"','"+posted_by+"',"+QString::number(genre)+",CURRENT_TIMESTAMP, 0, 0, 0, 0, 0)"))
        qDebug()<<"Document added";
    else qDebug()<<query.lastError();
}

void DocumentsDB::approveDocumentWithUID(int id){
    QSqlQuery q;
    //update approved to true
    if(q.exec("UPDATE doc_info SET approved = 1 WHERE u_id = "+QString::number(id)))
        qDebug()<< "Document has been approved.";
    else qDebug()<<q.lastError();
}

void DocumentsDB::deleteDocumentWithUID(int id){
    QSqlQuery q;
    //delete row where u_id == id
    if(q.exec("DELETE FROM doc_info WHERE u_id = "+QString::number(id)))
        qDebug()<< "Document has been deleted.";
    else qDebug()<<q.lastError();
}

void DocumentsDB::addComplaintToDocumentWithUID(int id){
    QSqlQuery q = this->getDocInfoForUID(id);
    //if doc was found
    if(q.first()){
        //get current number of complaints
        int currentComplaints = q.value(8).toInt();
        //add complaint and update database value
        if(q.exec("UPDATE doc_info SET num_of_complaints = "+QString::number(currentComplaints+1)+" WHERE u_id = "+QString::number(id)))
            qDebug()<< "Complaint recorded.";
        else qDebug()<<q.lastError();
    }
}


void DocumentsDB::addViewToDocWithUID(int id){
    QSqlQuery q = this->getDocInfoForUID(id);
    //if doc exists
    if (q.first()){
        //get current number of views
        int currentViews = q.value(7).toInt();
        //add complaint and update database value
        if(q.exec("UPDATE doc_info SET views = "+QString::number(currentViews+1)+" WHERE u_id = "+QString::number(id)))
            qDebug()<< "Views updated.";
        else qDebug()<<q.lastError();
    }
}


void DocumentsDB::addRatingToDocWithUID(int id, float newRating){
    QSqlQuery q = this->getDocInfoForUID(id);
    //if q exists
    if (q.first()){
        //get current avg rating and total num of ratings
        float avgRating = q.value(5).toFloat();
        int totalNumOfRatings = q.value(6).toInt();

        //update to new rating
        if(q.exec("UPDATE doc_info SET rating = "+QString::number(getNewAverageRating(newRating, avgRating, totalNumOfRatings))+" WHERE u_id = "+QString::number(id)))
            qDebug()<< "Rating updated.";
        else qDebug()<<q.lastError();

        //update total number of ratings made
        if(q.exec("UPDATE doc_info SET num_of_ratings = "+QString::number(totalNumOfRatings+1)+" WHERE u_id = "+QString::number(id)))
            qDebug()<< "Total number of ratings updated.";
        else qDebug()<<q.lastError();
    }
}

//return the new average rating
float getNewAverageRating(float newRating, float avgRating, int totalNumOfRatings){
    float currentTotal = avgRating * totalNumOfRatings + newRating;
    return currentTotal / (totalNumOfRatings +1);
}

//change this if we move the "books" folder somewhere else
QString DocumentsDB::getPathToDocWithUID(int id){
    return "/books/"+QString::number(id)+".txt";
}

int DocumentsDB::getNumDocs() {
    QSqlQuery q;
    if(q.exec("SELECT COUNT(*) FROM doc_info")){
        int out = q.first() ? q.value(0).toInt() : -1;
        return out;
    }
    else {
        qDebug()<<q.lastError();
        return -1;
    }
}

