#include "userinfodb.h"
#include "maindb.h"
#include <QString>
#include <QDebug>
#include <QtSql>

UserInfoDB::UserInfoDB():MainDB()
{}

//Make sure the value returned is an int
int UserInfoDB::getIntForKey(QString username, QString key){
    QSqlQuery q;
    if(q.exec("SELECT "+key+ " FROM user_info WHERE username = '"+username+"'")){
        q.next();
        return q.value(0).toInt();
    }
    else {
        qDebug()<<q.lastError();
        return 0;
    }
}

void UserInfoDB::setIntForKey(QString username, QString key, int value){
    QSqlQuery q;
    if(q.exec("UPDATE user_info SET "+key+ " = "+QString::number(value)+" WHERE username = '"+username+"'")){
        qDebug()<< key + " updated.";
    }else {
        qDebug()<<q.lastError();
    }
}

//Be sure the value returned is a string
QString UserInfoDB::getStringForKey(QString username, QString key){
    QSqlQuery q;
    if(q.exec("SELECT "+key+ " FROM user_info WHERE username = '"+username+"'")){
        q.next();
        return q.value(0).toString();
    }
    else {
        qDebug()<<q.lastError();
        return "";
    }
}

void UserInfoDB::banUser(QString username){
    QSqlQuery q;
    if(q.exec("UPDATE users SET is_banned = 1 WHERE username = '"+username+"'")){
        qDebug() << username + " has been banned.";
    }
}

void UserInfoDB::unbanUser(QString username){
    QSqlQuery q;
    if(q.exec("UPDATE users SET is_banned = 0 WHERE username = '"+username+"'")){
        qDebug() << username + " has been unbanned.";
    }
}

