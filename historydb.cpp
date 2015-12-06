#include "historydb.h"

HistoryDB::HistoryDB(): MainDB()
{

}

QString HistoryDB::getHistory(QString username,int row)
{
     QSqlQuery query;
     QString q;
     if(query.exec("SELECT * FROM History WHERE username = '"+username+"' LIMIT 1 OFFSET "+QString::number(row)))
     {
         if(query.next())
         {
             q=query.value(1).toString();
             q+=" by ";
             q+=query.value(2).toString();
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

int HistoryDB::getHistoryRow(QString username)
{
    QSqlQuery q;
    if(q.exec("SELECT count(*) FROM History WHERE username = '"+username+"'"))
        return q.first() ? q.value(0).toInt() : -1;
    else
    {
        qDebug() << q.lastError();
        return -1;
    }
}

HistoryDB::~HistoryDB()
{

}

