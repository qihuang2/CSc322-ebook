#ifndef HISTORYDB_H
#define HISTORYDB_H
#include "maindb.h"
#include <QString>
#include <QtSql>
class QSqlQuery;
class HistoryDB : public MainDB
{
public:
    HistoryDB();
    ~HistoryDB();
    void addHistory(QString Username,QString bookName,QString Author);
    QString getHistory(QString Username, int row);
    int getHistoryRow(QString);
private:

};
#endif // HISTORYDB_H
