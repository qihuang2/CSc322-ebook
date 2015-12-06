#include "superuser.h"
#include <QtSql>

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
        qDebug()<<"Error getting docs that need superuser approval";
        qDebug()<<query.lastError();
    }
    return query;
}

void SuperUser::acceptDocumentWithUID(int bookID){
    QSqlQuery q;
    if(!q.exec("UPDATE doc_info SET approved = 2 WHERE u_id = "+QString::number(bookID))){
        qDebug()<<"Error approving book by superuser";
        qDebug()<<q.lastError();
    }
}

void SuperUser::declineDocumentWithUID(int bookID, int counterOffer){
    QSqlQuery q;
    if(!q.exec("UPDATE doc_info SET approved = 2, counter_offer = " + QString::number(counterOffer) + " WHERE u_id = "+QString::number(bookID))){
        qDebug()<<"Error declining book by superuser";
        qDebug()<<q.lastError();
    }
}

void SuperUser::deleteBookWithUID(int uid){
    QSqlQuery q;
    if(!q.exec("UPDATE doc_info SET is_deleted = 1 WHERE u_id = "+ QString::number(uid))){
        qDebug()<<"Error deleting book by superuser";
        qDebug()<<q.lastError();
    }
}

void SuperUser::banUser(QString username){
    QSqlQuery q;
    if(!q.exec("UPDATE users SET is_banned = 1 WHERE username = '"+ username + "'")){
        qDebug()<<"Error banning user by superuser";
        qDebug()<<q.lastError();
    }
}

//NOTE: only returns follwing information
//username of person who reported the book
//book_id of reported book
//reason for report
QSqlQuery SuperUser::getAllDocumentsWithComplaints(){
    QSqlQuery query;
    if(query.exec("SELECT * FROM report_info"))
        return query;
    else {
        qDebug()<<"Problem getting list of reported books";
        return query;
    }
}

void SuperUser::changeCreditsBy(int credits) {
    credits = 0;   // to silence warning
}
