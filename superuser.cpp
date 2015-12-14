#include "superuser.h"
#include <QtSql>
#include "documentsdb.h"
#include <QDebug>

class QSqlQuery;

SuperUser::SuperUser(QString username) : RegisteredUser(username)
{
    m_username = username;
    m_userType = SUPER;
}

//Returns all documents that need superuser approval
QSqlQuery SuperUser::getSupersPendingDocuments(){
    QSqlQuery query;
    if (!query.exec("SELECT * FROM doc_info WHERE approved = 0 AND is_deleted = 0")){
        qDebug()<<"Error in getSuperPendinDocuments";
        qDebug()<<query.lastError();
    }
    return query;
}

void SuperUser::acceptDocumentWithUID(int bookID){
    QSqlQuery q;
    if(!q.exec("UPDATE doc_info SET approved = 3 WHERE u_id = "+QString::number(bookID))){
        qDebug()<<"Error in acceptDocumentWithUID by superuser";
        qDebug()<<q.lastError();
    }
}

void SuperUser::declineDocumentWithUID(int bookID, int counterOffer){
    QSqlQuery q;
    if(!q.exec("UPDATE doc_info SET approved = 1, counter_offer = " + QString::number(counterOffer) + " WHERE u_id = "+QString::number(bookID))){
        qDebug()<<"Error in declineDocumentWithUID by superuser";
        qDebug()<<q.lastError();
    }
}

//deletes book and increments number of books deleted for a user
void SuperUser::deleteReportedBookWithUID(int uid){

    this->deleteBookWithUID(uid); //delete book


    //get uploader of document
    DocumentsDB* db = new DocumentsDB();
    QSqlQuery q = db->getDocInfoForUID(uid);
    if(q.first()){
        QString uploader = q.value(DocumentsDB::POSTEDBY).toString();
        RegisteredUser* user = new RegisteredUser(uploader);

        int creditsForBook = q.value(DocumentsDB::ASKINGPRICE).toInt()+100;
        user->changeCreditsBy(-creditsForBook);

        //increment number of deleted books

        user->incrementBooksDeletedBy(1);

        if(user->getNumOfDeletedBooks() >=2) this->banUser(uploader); //if 2 more more, ban user
        delete user;
    }else {
        qDebug()<<"ERROR in deleteReportedBookWithUID";
    }
    delete db;
}

void SuperUser::deleteBookWithUID(int uid){
    QSqlQuery q;
    if(!q.exec("UPDATE doc_info SET is_deleted = 1 WHERE u_id = "+ QString::number(uid))){
        qDebug()<<"Error in deleteBookWithUID by superuser";
        qDebug()<<q.lastError();
    }
}

void SuperUser::banUser(QString username){
    QSqlQuery q;
    if(!q.exec("UPDATE users SET is_banned = 1 WHERE username = '"+ username + "'")){
        qDebug()<<"Error in banUser by SU";
        qDebug()<<q.lastError();
    }
}

//NOTE: only returns follwing information
//username of person who reported the book
//book_id of reported book
//reason for report
QSqlQuery SuperUser::getAllDocumentsWithComplaints(){
    QSqlQuery query;
    if(query.exec("SELECT report_info.book_id, doc_info.title, report_info.username,"
            " report_info.reason  FROM report_info, doc_info WHERE report_info.book_id = doc_info.u_id"
            " AND doc_info.is_deleted = 0"))
        return query;
    else {
        qDebug()<<"Error in getAllDocumentsWithComplaints by SU";
        qDebug()<<query.lastError();
        return query;
    }
}

void SuperUser::changeCreditsBy(int credits) {
    credits = 0;   // to silence warning
}
