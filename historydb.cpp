#include "historydb.h"

HistoryDB::HistoryDB(): MainDB()
{

}

QString HistoryDB::getHistory(QString username)
{
     QSqlQuery query;
     QString q="";
     if(query.exec("SELECT * FROM History WHERE username = '"+username+"'"))
     {
        while(query.next())
        {
            q+=query.value(1).toString();
            q+=" By ";
            q+=query.value(2).toString();
            q+="\n";
        }
    }
     return q;
}

void HistoryDB::addHistory(QString Username,QString bookName,QString Author)
{
    QSqlQuery q;
    if(q.exec("INSERT INTO History VALUES('"+Username+"','"+bookName+"','"+Author+"')"))
            qDebug()<<"add History";
    else
        qDebug()<<q.lastError();
}

HistoryDB::~HistoryDB()
{

}

