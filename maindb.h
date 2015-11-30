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
    static void closeDB();

private:
    //our user info database. I made it static so there aren't multiple connections
    //to the same DB.
    //(subclasses of this class might try connecting to the DB when a connection already exists)
    static QSqlDatabase* st_mainDB;
};

#endif // MAINDB_H
