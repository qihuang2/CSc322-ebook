#include "maindb.h"
#include <QtSql>
#include <QDebug>
#include <QString>


MainDB::MainDB()
{
    /*
     * MYSQL CODE
     * this->loginDB = QSqlDatabase::addDatabase("QMYSQL");
     * loginDB.setHostName("sql5.freesqldatabase.com");
     * loginDB.setDatabaseName("sql594107");
     * loginDB.setUserName("sql594107");
     * loginDB.setPassword("rG8*cQ1%");
     * loginDB.setPort(3306);
    */

    //Creates a sqlite file that is hidden

    this->m_mainDB = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    m_mainDB->setDatabaseName("ebookDB.db");

    if(!m_mainDB->open()){
        qDebug()<<"Something went wrong connecting to DB.";
    }

    QSqlQuery qry;
    //creates the table 'users' if it doesn't exist

    qry.prepare( "CREATE TABLE IF NOT EXISTS users (username VARCHAR(12), password VARCHAR(14), account_type TINYINT, is_banned TINYINT)" );
    if( !qry.exec() )
      qDebug() << qry.lastError();

    //creates the table 'user_info' if it does't exist
    //So far the DB has username, num of credits, num of complaints, num of uploads, date account created
    qry.prepare( "CREATE TABLE IF NOT EXISTS user_info (username VARCHAR(12), credits INT, complaints TINYINT, uploads INT, created TEXT)" );
    if( !qry.exec() )
      qDebug() << qry.lastError();
}


bool MainDB::isConnected(){
    return (m_mainDB->open());
}



bool MainDB::userExists(QString username){
    //username is stored in lowercase in DB.   WtfisloL == wtfizlol
    username = username.toLower();
    QSqlQuery query;
    if (query.exec("SELECT * FROM users WHERE username = '"+username+"'")){
        //if query returned a value, then user exists
        if(query.next())
            return true;
    }
    //else username not taken
    return false;
}


void MainDB::printTables(){
    QStringList tables = m_mainDB->tables();
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
        qDebug()<<"Unable to get users";
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
        qDebug() << q.lastError();
        return false;
    }
}

int MainDB::getAccountType(QString username){
    username = username.toLower();
    QSqlQuery q;
    if(q.exec("SELECT account_type FROM users WHERE username = '"+username+"'")){
        q.next();
        return (q.value(0).toInt()) ;
    }else {
        qDebug() << q.lastError();
        return 0;
    }
}

//removes connection to DB
void MainDB::closeDB(){
    if (m_mainDB->open()){
        QString c = m_mainDB->connectionName();
        m_mainDB->close();

        // Don't take this out. The DB won't close if this is taken out for
        // some reason. You can try playing around with it if you want.
        delete m_mainDB;

        QSqlDatabase::removeDatabase(c);
    }
}


