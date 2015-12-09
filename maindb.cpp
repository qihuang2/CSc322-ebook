#include "maindb.h"
#include <QtSql>
#include <QDebug>
#include <QString>


QSqlDatabase* MainDB::st_mainDB;

MainDB::MainDB()
{
    /*
     * MySQL code to connect to DB.
     *
     * this->loginDB = QSqlDatabase::addDatabase("QMYSQL");
     * loginDB.setHostName("sql5.freesqldatabase.com");
     * loginDB.setDatabaseName("sql594107");
     * loginDB.setUserName("sql594107");
     * loginDB.setPassword("rG8*cQ1%");
     * loginDB.setPort(3306);
    */

    //If our static DB hasn't been initialized yet, then set DB. This way, we only connect to
    //DB once
    //Creates a sqlite file that is hidden
    if(MainDB::st_mainDB == NULL){

        MainDB::st_mainDB = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
        MainDB::st_mainDB->setDatabaseName("/Users/youshenghua/Desktop/ebookDB.db");

        if(!MainDB::st_mainDB->open()){
            qDebug()<<"Something went wrong connecting to DB.";
        }

        QSqlQuery qry;

        //creates the table 'users' if it doesn't exist
        //
        //CONTAINS-
        //username: username of user
        //password: password of user
        //account_type: 0 for visitor, 1 for RU, 2 for SU
        //is_banned: determine if user is banned
        qry.prepare( "CREATE TABLE IF NOT EXISTS users ("
                                                        "username VARCHAR(12) PRIMARY KEY, "
                                                        "password VARCHAR(14) NOT NULL, "
                                                        "account_type TINYINT NOT NULL, "
                                                        "is_banned TINYINT NOT NULL"
                                                        ");" );
        if( !qry.exec() ){
            qDebug()<<"Error creating users in MainDB()";
            qDebug() << qry.lastError();
        }


        //add admin account
        if(!qry.exec("INSERT OR IGNORE INTO users VALUES ('admin', 'password', 2, 0)")){
            qDebug()<<"Error creating SuperUser in MainDB()";
            qDebug() << qry.lastError();
        }

        //creates the table 'user_info' if it does't exist
        //
        //CONTAINS-
        //username: username of user
        //credits: number of credits user has
        //complaints: total number of complaints
        //uploads: total number of uploads
        //created: when account was created
        qry.prepare( "CREATE TABLE IF NOT EXISTS user_info ("
                                                            "username VARCHAR(12) PRIMARY KEY, "
                                                            "credits INT NOT NULL, "
                                                            "complaints TINYINT NOT NULL, "
                                                            "uploads INT NOT NULL, "
                                                            "created TEXT NOT NULL, "
                                                            "FOREIGN KEY (username) REFERENCES users(username)"
                                                            ");" );
        if( !qry.exec() ){
            qDebug()<<"Error creating user_info in MainDB()";
           qDebug() << qry.lastError();
        }

        //add admin to user_info
        if(!qry.exec("INSERT OR IGNORE INTO user_info VALUES ('admin', 999, 0, 0, CURRENT_TIMESTAMP)")){
            qDebug()<<"Error creating SuperUser user_info in MainDB()";
            qDebug() << qry.lastError();
        }

        //creates the table 'doc_info' if it does't exist
        //doc_info keeps track of documents that have been uploaded
        //
        //CONTAINS -
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
        qry.prepare( "CREATE TABLE IF NOT EXISTS doc_info ("
                                                           "u_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                                           "title VARCHAR(25) NOT NULL, "
                                                           "posted_by VARCHAR(12) NOT NULL, "
                                                           "genre INT NOT NULL, "
                                                           "upload_date TEXT NOT NULL, "
                                                           "rating REAL NOT NULL, "
                                                           "num_of_ratings INT NOT NULL, "
                                                           "views INT NOT NULL,"
                                                           "num_of_complaints INT NOT NULL, "
                                                           "approved TINYINT NOT NULL, "
                                                           "asking_price INT NOT NULL,"
                                                           "counter_offer INT,"
                                                           "summary VARCHAR(250),"
                                                           "is_deleted INT NOT NULL,"
                                                           "FOREIGN KEY (posted_by) REFERENCES user_info(username)"
                                                        ");");
        if( !qry.exec() ){
            qDebug()<<"Error creating doc_info in MainDB()";
           qDebug() << qry.lastError();
        }


          qry.prepare( "CREATE TABLE IF NOT EXISTS History ("
                                                              "username VARCHAR(12), "
                                                              "bookname VARCHAR(25), "
                                                              "author VARCHAR(25) NOT NULL,   PRIMARY KEY(username,bookname) "
                                                              ");" );
           if( !qry.exec() ){
               qDebug()<<"Error creating History in MainDB()";
              qDebug() << qry.lastError();
           }

           //creates the table 'rating_info' if it doesn't exist
           //
           //List of user and the books they rated
           //CONTAINS-
           //username: username of user
           //book_id: id of book
           qry.prepare( "CREATE TABLE IF NOT EXISTS rating_info ("
                                                           "username VARCHAR(12) NOT NULL, "
                                                           "book_id INTEGER NOT NULL, "
                                                           "PRIMARY KEY (username, book_id)"
                                                           ");" );
           if( !qry.exec() ){
               qDebug()<<"Error creating rating_info in MainDB()";
               qDebug() << qry.lastError();
           }

           //creates the table 'report_info' if it doesn't exist
           //
           //List of user and the books the reason for reporting
           //CONTAINS-
           //username: username of user
           //book_id: id of book
           //reason: reason for reporting
           qry.prepare( "CREATE TABLE IF NOT EXISTS report_info ("
                                                                 "username VARCHAR(12) NOT NULL, "
                                                                 "book_id INTEGER NOT NULL, "
                                                                 "reason VARCHAR(100) NOT NULL,"
                                                                 "PRIMARY KEY (username, book_id)"
                                                                 ");");
           if( !qry.exec() ){
               qDebug()<<"Error creating report_info in MainDB()";
                qDebug() << qry.lastError();
           }

    }
}

MainDB::~MainDB() {}

bool MainDB::isConnected(){
    return (MainDB::st_mainDB->open());
}



bool MainDB::userExists(QString username){
    //username is stored in lowercase in DB.   WtfisloL == wtfizlol
    username = username.toLower();
    QSqlQuery query;
    if (query.exec("SELECT * FROM users WHERE username = '"+username+"'")){
        //if query returned a value, then user exists
        if(query.first())
            return true;
    }else {
        qDebug()<<"Error in userExists: "+username;
    }
    //else username not taken
    return false;
}


void MainDB::printTables(){
    QStringList tables = MainDB::st_mainDB->tables();
    //gets list of tables in DB
    //prints table names
    for (QStringList::iterator it = tables.begin();
        it != tables.end(); ++it) {
        QString current = *it;
        qDebug() << "[[" << current << "]]";
   }
}


void MainDB::deleteTable(QString tableName){
    QSqlQuery query;
    if (query.exec("DROP TABLE "+tableName)){
        qDebug()<<"Table Deleted";
    }else {
        qDebug()<<"Error in deleteTable: "+tableName;
        qDebug()<<query.lastError();
    }
}


//Prints a list of registered users.

void MainDB::printUsers(){
    QSqlQuery q;

    if (q.exec("SELECT username, password FROM users")){
        while(q.next()){
            qDebug()<<q.value(0).toString()<<q.value(1).toString();
        }
    }else {
        qDebug()<<"Error in PrintUsers";
        qDebug()<<q.lastError();
    }
}

bool MainDB::isBanned(QString username){
    //username is stored in lower case in DB
    username = username.toLower();
    QSqlQuery q;
    if(q.exec("SELECT is_banned FROM users WHERE username = '"+username+"'")){
        q.next();
        return (q.value(0).toBool()) ? true : false;
    }else {
        qDebug()<<"Error isBanned: "+username;
        qDebug() << q.lastError();
        return false;
    }
}

QSqlQuery MainDB::getAccount(QString username){
    username = username.toLower();
    QSqlQuery q;
    if(q.exec("SELECT * FROM users WHERE username = '"+username+"'")){
        return (q) ;
    }else {
        qDebug()<<"Error getAccount: "+username;
        qDebug() << q.lastError();
        return q;
    }
}

//removes connection to DB
void MainDB::closeDB(){
    if (MainDB::st_mainDB->open()){
        QString c = MainDB::st_mainDB->connectionName();
        MainDB::st_mainDB->close();

        // Don't take this out. The DB won't close if this is taken out for
        // some reason. You can try playing around with it if you want.
        delete MainDB::st_mainDB;

        QSqlDatabase::removeDatabase(c);
    }
}
