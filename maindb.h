#ifndef MAINDB_H
#define MAINDB_H

class QSqlDatabase;
class QString;
class QSqlQuery;

class MainDB
{
public: 
    enum documentKeys {
        UID,
        TITLE,
        POSTEDBY,
        GENRE,
        UPLOADDATE,
        RATING,
        NUMRATINGS,
        VIEWS,
        NUMCOMPLAINTS,
        APPROVED,
        SUMMARY
    };

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

    //get account
    QSqlQuery getAccount(QString username);

     //MAKE SURE YOU CLOSE THE DB WHEN YOU FINISH USING IT
    static void closeDB();

private:
    static QSqlDatabase* st_mainDB;

};

#endif // MAINDB_H
