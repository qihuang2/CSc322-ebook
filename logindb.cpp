#include "logindb.h"
#include <QStringList>

LoginDB::LoginDB()
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

    this->loginDB = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    loginDB->setDatabaseName("loginDB.db");

    if(!loginDB->open()){
        qDebug()<<"Something went wrong connecting to DB.";
    }

    QSqlQuery qry;

    //creates the table 'users' if it doesn't exist
    qry.prepare( "CREATE TABLE IF NOT EXISTS users (username VARCHAR(12), password VARCHAR(14), account_type TINYINT, is_banned TINYINT)" );
    if( !qry.exec() )
      qDebug() << qry.lastError();
}

LoginDB::~LoginDB(){
    closeDB();
}

bool LoginDB::isConnected(){
    return (loginDB->open());
}

bool LoginDB::userExists(QString username){
    QSqlQuery query;
    if (query.exec("select * from users where username = '"+username+"'")){
        if(query.next())
            return true;
    }
    return false;
}

void LoginDB::addUser(QString username, QString password, QString account_type){
    if (!userExists(username)) {
        QSqlQuery query;
        if (query.exec("INSERT INTO users(username,password,account_type,is_banned) VALUES ('"+username+"','"+password+"',"+account_type+",0)")){
            qDebug()<<"User added.";
        }else {
            qDebug()<<query.lastError();
        }
    }
}

void LoginDB::printTables(){
    QStringList tables=loginDB->tables();
    for (QStringList::iterator it = tables.begin();
        it != tables.end(); ++it) {
        QString current = *it;
        qDebug() << "[[" << current << "]]";
   }
}

void LoginDB::deleteTable(QString tableName){
    QSqlQuery query;
    if (query.exec("DROP TABLE "+tableName)){
        qDebug()<<"Table Deleted";
    }else {
        qDebug()<<query.lastError();
    }
}

void LoginDB::printUsers(){
    QSqlQuery q;
    if (q.exec("SELECT username FROM users")){
        while(q.next()){
            qDebug()<<q.value(0).toString();
        }
    }else {
        qDebug()<<"Unable to get users";
    }
}


bool LoginDB::checkUserAndPass(QString username, QString password){
    if (!userExists(username)) return false;
    QSqlQuery q;
    if(q.exec("SELECT password FROM users WHERE username = '"+username+"'")){
        q.next();
        return (q.value(0).toString().compare(password) == 0) ? true : false ;
    }else {
        qDebug()<<q.lastError();
        return false;
    }
}

bool LoginDB::isBanned(QString username){
    QSqlQuery q;
    if(q.exec("SELECT is_banned FROM users WHERE username = '"+username+"'")){
        q.next();
        return (q.value(0).toBool()) ? true : false;
    }else {
        qDebug() << q.lastError();
        return false;
    }
}

void LoginDB::banUser(QString username){
    QSqlQuery q;
    if(q.exec("UPDATE users SET is_banned = 1 WHERE username = '"+username+"'")){
        qDebug() << username + " has been banned.";
    }
}

void LoginDB::unbansUser(QString username){
    QSqlQuery q;
    if(q.exec("UPDATE users SET is_banned = 0 WHERE username = '"+username+"'")){
        qDebug() << username + " has been unbanned.";
    }
}

void LoginDB::closeDB(){
    if (loginDB->open()){
        QString c = loginDB->connectionName();
        loginDB->close();
        delete loginDB;
        QSqlDatabase::removeDatabase(c);
    }
}
