#ifndef MAINDB_H
#define MAINDB_H

class QSqlDatabase;
class QString;

class MainDB
{
public:
    MainDB();
    ~MainDB();

    bool isConnected();   //check if connected to DB

    //print list of tables in DB
    void printTables();

    //deletes table
    void deleteTable(QString tableName);

    //print list of users
    void printUsers();

    //checks if username already in user
    bool userExists(QString username);

    //check if user is banned
    bool isBanned(QString username);

    //get account type
    int getAccountType(QString username);

     //MAKE SURE YOU CLOSE THE DB WHEN YOU FINISH USING IT
    void closeDB();

private:
    QSqlDatabase *m_mainDB;  //our user info database
};

#endif // MAINDB_H
