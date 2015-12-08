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
        if(q.first()){
            return q.value(0).toInt();
        }else {
            qDebug()<<"Error in getIntForKey: "+username+" "+key;
            return 0;
        }
    }
    else {
        qDebug()<<"Error in getIntForKey: "+username+" "+key;
        qDebug()<<q.lastError();
        return 0;
    }
}

void UserInfoDB::setIntForKey(QString username, QString key, int value){
    QSqlQuery q;
    if(q.exec("UPDATE user_info SET "+key+ " = "+QString::number(value)+" WHERE username = '"+username+"'")){
        qDebug()<< key + " updated.";
    }else {
        qDebug()<<"Error in setIntForKey: "+username+" "+key;
        qDebug()<<q.lastError();
    }
}

//Be sure the value returned is a string
QString UserInfoDB::getStringForKey(QString username, QString key){
    QSqlQuery q;
    if(q.exec("SELECT "+key+ " FROM user_info WHERE username = '"+username+"'")){
        if (q.first()){
            return q.value(0).toString();
        }else {
            qDebug()<<"Error in getStringForKey: "+username+" "+key;
            return "";
        }
    }
    else {
        qDebug()<<"Error in getStringForKey: "+username+" "+key;
        qDebug()<<q.lastError();
        return "";
    }
}

void UserInfoDB::banUser(QString username){
    QSqlQuery q;
    if(q.exec("UPDATE users SET is_banned = 1 WHERE username = '"+username+"'")){
        qDebug() << username + " has been banned.";
    }
    else{
        qDebug()<<"Error in banUser: "+username;
        qDebug()<<q.lastError();
    }
}

void UserInfoDB::unbanUser(QString username){
    QSqlQuery q;
    if(q.exec("UPDATE users SET is_banned = 0 WHERE username = '"+username+"'")){
        qDebug() << username + " has been unbanned.";
    }
    else{
        qDebug()<<"Error in unbanUser: "+username;
        qDebug()<<q.lastError();
    }
}

