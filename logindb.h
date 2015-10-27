#ifndef LOGINDB_H
#define LOGINDB_H

#include "maindb.h"

class LoginDB : public MainDB
{
public:
    LoginDB();
    ~LoginDB();

    //check if password is correct
    bool checkUserAndPass(QString username, QString password);

    //adds user to DB
    void addUser(QString username, QString password, QString account_type);
};

#endif // LOGINDB_H
