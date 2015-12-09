#include "logindb.h"
#include <QString>
#include <QDebug>
#include <QtSql>

LoginDB::LoginDB() : MainDB()
{

}

bool LoginDB::checkUserAndPass(QString username, QString password){
    //Username is stored in lowercase in DB
    username = username.toLower();
    //if user doesn't exist, return false
    if (!userExists(username)) return false;
    QSqlQuery q;
    if(q.exec("SELECT password FROM users WHERE username = '"+username+"'")){
        if(q.first()){
            return (q.value(0).toString().compare(password) == 0) ? true : false ;
        }
        else {
            qDebug()<<"Error in checkUserAndPass: "+username+ " "+password;
            return false;
        }
    }
    else {
        qDebug()<<"Error in checkUserAndPass: "+username+ " "+password;
        qDebug()<<q.lastError();
        return false;
    }
}


void LoginDB::addUser(QString username, QString password, QString account_type){
    //username is stored in lowercase in DB
    username = username.toLower();
    if (!userExists(username)) {
        QSqlQuery query;
        //Adds account to the tables 'users' and 'user_info'
        if (!query.exec("INSERT INTO users(username,password,account_type,is_banned) VALUES ('"+username+"','"+password+"',"+account_type+",0)")){
            qDebug()<<"Error adding into users in addUser: " + username + " " + password + " "+ account_type;
            qDebug()<<query.lastError();
        }
        if (!query.exec("INSERT INTO user_info(username,credits,complaints,uploads,created) VALUES ('"+username+"', 500, 0, 0, CURRENT_TIMESTAMP)")){
            qDebug()<<"Error adding into user_info in addUser: " + username + " " + password + " "+ account_type;
            qDebug()<<query.lastError();
        }
    }
}
