#ifndef LOGINDB_H
#define LOGINDB_H

#include <QtSql>
#include <QDebug>
#include <QString>

class LoginDB
{
public:
    LoginDB();
    ~LoginDB();

    bool isConnected();   //check if connected to DB
    void printTables();     //print list of tables

    void deleteTable(QString tableName); //deletes table

    void printUsers(); //print list of uses


    bool userExists(QString username);                         //checks if username is being used
    bool checkUserAndPass(QString username, QString password); //check if password is correct
    bool isBanned(QString username); //check if banned
    void banUser(QString username);  //bans user
    void unbansUser(QString username);

    void addUser(QString username, QString password, QString account_type);     //adds user to DB

    void closeDB();  //MAKE SURE YOU CLOSE THE DB WHEN YOU FINISH USING IT

private:
    QSqlDatabase *loginDB;  //our user info database
};

#endif // LOGINDB_H
