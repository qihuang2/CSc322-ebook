#ifndef MAINDB_H
#define MAINDB_H

class QSqlDatabase;
class QSqlQuery;
class QString;
class QSqlQuery;

class MainDB
{
public: 
    //u_id: unique book id. The value is automatically incremented so we don't have to worry about that
    //title: title of the book. Limited to 25 characters
    //posted_by: username of user who posted document
    //genre: genre of book. saved as an int
    //upload_date: date document was uploaded
    //rating: average rating of book. stored as a float
    //num_of_ratings: total number of people who rated the book
    //views: total number of people that read the document
    //num_of_complaints: number of users who complained about the book
    //approved: document has been approved by SU
    //asking_price: how much user asks for uploud
    //counter_offer: super user presents a counter offer
    //summary: document summary. Limited to 250 characters
    //is_deleted: document has been deleted
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
        ASKINGPRICE,
        COUNTEROFFER,
        SUMMARY,
        ISDELETED
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
