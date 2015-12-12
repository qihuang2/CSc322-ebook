#include "documentsdb.h"
#include <QString>
#include <QDebug>
#include <QtSql>
#include "registereduser.h"


//returns new average rating of book
float getNewAverageRating(float newRating, float avgRating, int totalNumOfRatings);

DocumentsDB::DocumentsDB() : MainDB()
{
}

QSqlQuery DocumentsDB::getDocInfoForUID(int id){
    QSqlQuery query;
    //if command runs
    if(!query.exec("SELECT * FROM doc_info WHERE u_id = "+QString::number(id))) {
        qDebug() << "getDocInfoForUID: " + QString::number(id)  +" failed.";
        qDebug()<<query.lastError();
    }
    return query;
}

QSqlQuery DocumentsDB::getDocsUploadedByUser(QString username){
    QSqlQuery query;
    //there is no check to see if this command is run
    //I did it this way so it is easier to iterate through using : while (query.next())
    if(!query.exec("SELECT * FROM doc_info WHERE posted_by = '"+username+"' AND is_deleted = 0")){
        qDebug()<<"getDocUploadedByUser: "+username+"failed";
        qDebug()<<query.lastError();
    }
    return query;
}

QSqlQuery DocumentsDB::getAllDocs(){
    QSqlQuery q;
    if(!q.exec("SELECT * FROM doc_info WHERE approved = 3 AND is_deleted = 0")){
        qDebug()<<"getAllDocs failed";
        qDebug()<<q.lastError();
    }
    return q;
}


//FIX ME: DON't AUTOAPPROVE
void DocumentsDB::addDocument(QString title, QString posted_by, int genre, QString summary, QString askingPrice){
    QSqlQuery query;
    //add document into doc_info DB with some initial values
    if (query.exec("INSERT INTO doc_info(title,posted_by,genre, upload_date, rating, num_of_ratings, views, num_of_complaints, approved, asking_price, counter_offer, summary, is_deleted) "
                   "VALUES ('"+title+"','"+posted_by+"',"+QString::number(genre)+",CURRENT_TIMESTAMP, 0, 0, 0, 0, 0,"+askingPrice+",null," + "'" + summary + "',0)"))
        qDebug()<<"Document added";
    else{
        qDebug() <<"addDocument: "+title+" "+posted_by+" "+QString::number(genre)+ " " + summary + " " + askingPrice + " failed";
        qDebug()<<query.lastError();
    }
}

void DocumentsDB::deleteDocumentWithUID(int id){
    QSqlQuery q;
    //delete row where u_id == id
    if(q.exec("UPDATE doc_info SET is_deleted = 1 WHERE u_id = "+QString::number(id)))
        qDebug()<< "Document has been deleted.";
    else{
        qDebug()<<"deleteDocumentWitUID: "+QString::number(id)+ " failed";
        qDebug()<<q.lastError();
    }
}

void DocumentsDB::modifyCounterForUID(int id, int counter) {
    QString query = QString("UPDATE doc_info SET approved = %1 WHERE u_id = %2").arg(QString::number(counter), QString::number(id));
    qDebug() << "Query: " << query;
    QSqlQuery q;
    if(!(q.exec(query))) {
        qDebug() << "Error while countering.";
    }
}

void DocumentsDB::addComplaintToDocumentWithUID(QString username, int book_id, QString reason){
    QSqlQuery q = this->getDocInfoForUID(book_id);
    //if doc was found
    if(q.first()){
        //get current number of complaints
        int currentComplaints = q.value(8).toInt();

        QString uploaderName = q.value(2).toString();
        RegisteredUser uploader = RegisteredUser(uploaderName);

        //add complaint and update database value
        if(++currentComplaints >= 3){ //delete book if reached complaint limit

            deleteDocumentWithUID(book_id); //delete document
            int creditPenalty = q.value(10).toInt() + 100;
            uploader.changeCreditsBy(-creditPenalty); //decrement credits

            uploader.incrementBooksDeletedBy(1);//add num of books deleted

            if(uploader.getNumOfDeletedBooks() >= 2){ //user has 2 or more deleted books so ban
                if(!q.exec("UPDATE users SET is_banned = 1 WHERE username = '"+uploader.getUsername()+"'")){
                    qDebug() << "Error autobanning user inside addComplaintToDocumentWithUID :" + username + " " + QString::number(book_id)+ " "+ reason;
                    qDebug()<< q.lastError();
                }
            }
        }

        if(!q.exec("UPDATE doc_info SET num_of_complaints = "+QString::number(currentComplaints)+" WHERE u_id = "+QString::number(book_id))){
            qDebug() << "Error adding complaint inside addComplaintToDocumentWithUID :" + username + " " + QString::number(book_id)+ " "+ reason;
            qDebug()<< q.lastError();
        }


        //add to report_info
        //this is to determine if user has reported the document already: users can't report the same doc twice
        if(!q.exec("INSERT INTO report_info VALUES ('"+username+ "',"+QString::number(book_id)+",'" + reason +"')")){
            qDebug() << "Error adding into report_info inside addComplaintToDocumentWithUID :" + username + " " + QString::number(book_id)+ " "+ reason;
            qDebug()<<q.lastError();
        }
    }
}

//after openning document, add a view to the doc
void DocumentsDB::addViewToDocWithUID(int id){
    QSqlQuery q = this->getDocInfoForUID(id);
    //if doc exists
    if (q.first()){
        //get current number of views
        int currentViews = q.value(7).toInt();
        //add complaint and update database value
        if(!q.exec("UPDATE doc_info SET views = "+QString::number(currentViews+1)+" WHERE u_id = "+QString::number(id))){
            qDebug()<< "Error using addViewToDocWithUID: " + QString::number(id);
            qDebug()<< q.lastError();
        }
    }
}

void DocumentsDB::addRatingToDocWithUID(QString username, int id, float newRating){
    QSqlQuery q = this->getDocInfoForUID(id);
    //if q exists
    if (q.first()){
        //get current avg rating and total num of ratings
        float avgRating = q.value(5).toFloat();
        int totalNumOfRatings = q.value(6).toInt();

        //update to new rating
        if(!q.exec("UPDATE doc_info SET rating = "+QString::number(getNewAverageRating(newRating, avgRating, totalNumOfRatings))+" WHERE u_id = "+QString::number(id))){
            qDebug()<< "Error updating new rating addRatingToDoc: "+username+ " " + QString::number(id)+ " " + QString::number(newRating);
            qDebug()<<q.lastError();
        }

        //update total number of ratings made
        if(!q.exec("UPDATE doc_info SET num_of_ratings = "+QString::number(totalNumOfRatings+1)+" WHERE u_id = "+QString::number(id))){
            qDebug()<< "Error updating total ratings addRatingToDoc: "+username+ " " + QString::number(id)+ " " + QString::number(newRating);
            qDebug()<<q.lastError();
        }

        //add user to user rated_info
        //so users can't rate twice
        if(!q.exec("INSERT INTO rating_info VALUES ('"+username+"',"+QString::number(id)+")")){
            qDebug()<< "Error adding into rated_info addRatingToDoc: "+username+ " " + QString::number(id)+ " " + QString::number(newRating);
            qDebug()<<q.lastError();
        }
    }
}

//COMMENTS: use this if we are supporting comments
//USE THIS ONE TO PUSH FROM DOCUMENT TO DB
void DocumentsDB::addRatingToDocWithUID(QString username, int id, float newRating, QString comment){
    QSqlQuery q = this->getDocInfoForUID(id);
    //if q exists
    if (q.first()){
        //get current avg rating and total num of ratings
        float avgRating = q.value(5).toFloat();
        int totalNumOfRatings = q.value(6).toInt();

        //update to new rating
        if(!q.exec("UPDATE doc_info SET rating = "+QString::number(getNewAverageRating(newRating, avgRating, totalNumOfRatings))+" WHERE u_id = "+QString::number(id))){
            qDebug()<< "Error updating new rating addRatingToDoc: "+username+ " " + QString::number(id)+ " " + QString::number(newRating);
            qDebug()<<q.lastError();
        }

        //update total number of ratings made
        if(!q.exec("UPDATE doc_info SET num_of_ratings = "+QString::number(totalNumOfRatings+1)+" WHERE u_id = "+QString::number(id))){
            qDebug()<< "Error updating total ratings addRatingToDoc: "+username+ " " + QString::number(id)+ " " + QString::number(newRating);
            qDebug()<<q.lastError();
        }

        //add user to user rated_info
        //so users can't rate twice
        if(!q.exec("INSERT INTO rating_info VALUES ('"+username+"',"+QString::number(id)+", "+QString::number(newRating)+ ",'"+ comment+"')")){
            qDebug()<< "Error adding into rated_info addRatingToDoc: "+username+ " " + QString::number(id)+ " " + QString::number(newRating);
            qDebug()<<q.lastError();
        }
    }
}

//return the new average rating
float getNewAverageRating(float newRating, float avgRating, int totalNumOfRatings){
    float currentTotal = avgRating * totalNumOfRatings + newRating;
    return currentTotal / (totalNumOfRatings +1);
}

//change this if we move the "books" folder somewhere else
QString DocumentsDB::getPathToDocWithUID(int id){
    return "/books/"+QString::number(id)+".txt";
}

//returns -1 if error
int DocumentsDB::getNumDocs() {
    QSqlQuery q;
    if(q.exec("SELECT COUNT(*) FROM doc_info WHERE approved = 3 AND is_deleted = 0")){
        return q.first() ? q.value(0).toInt() : -1;
    }
    else {
        qDebug()<<"Error getNumDocs";
        qDebug()<<q.lastError();
        return -1;
    }
}

//returns 0 if nothing in table
int DocumentsDB::getLastInsertRowUID(){
    QSqlQuery q;
    if(q.exec("SELECT last_insert_rowid() AS rowid FROM doc_info")){
        return q.first() ? q.value(0).toInt() : 0;
    }
   else {
        qDebug()<<"Error in getLastInsertRowUID";
        qDebug() << q.lastError();
        return 0;
    }
}

//Get the number of summaries for all books
int DocumentsDB::getnumSumm(QString book_Name)
{
    QSqlQuery q;
    QString char_quot = "'";
    if(q.exec("select count(summary) from doc_info where approved = 3 and is_deleted = 0 and title = "+char_quot+book_Name+char_quot))
    {
        return q.first() ? q.value(0).toInt() : -1;
    }
    else
    {
        qDebug()<<"Error in getnumSumm";
        qDebug() << q.lastError();
        return -1;
    }
}

QString DocumentsDB::getSummary(QString book_Name)
{
    QSqlQuery query;
    QString char_quot = "'";
    if(query.exec("select summary from doc_info where title = "+char_quot+book_Name+char_quot))
    {
        QString summary;
        while(query.next())
        {
            summary = query.value(0).toString();
        }
        return summary;
    }
    else
    {
        qDebug()<<"Error in getSummary";
        QString blank = "";
        qDebug() << query.lastError();
        return blank;
    }
}

bool DocumentsDB::userHasReportedBook(QString username, int book_id){
    QSqlQuery query;
    if(query.exec("SELECT * FROM report_info  WHERE username = '"+username+"' AND book_id = " + QString::number(book_id) )){
        if(query.next()){ //got something so user reported book already
            return true;
        }else return false; //no entry so user hasn't reported book yet
    }else {
        qDebug()<<"Error userHasReportedBook: "+username+ " "+QString::number(book_id);
        qDebug()<<query.lastError();
       return false;
    }
}

bool DocumentsDB::userHasRatedBook(QString username, int book_id){
    QSqlQuery query;
    if(query.exec("SELECT * FROM rating_info  WHERE username = '"+username+"' AND book_id = " + QString::number(book_id) )){
        if(query.next()){ //got something so user rated book already
            return true;
        }else return false; //no entry so user hasn't rated book yet
    }else {
        qDebug()<<"Error userHasRatedBook: "+username + QString::number(book_id);
        qDebug()<<query.lastError();
       return false;
    }
}

QSqlQuery DocumentsDB::getFiveMostViewed(){
    QSqlQuery q;
    if(!q.exec("SELECT * FROM doc_info WHERE approved = 3 AND is_deleted = 0 ORDER BY views DESC LIMIT 5")){
        qDebug()<<"Error getFiveMostViewed";
        qDebug()<<q.lastError();
     }
    return q;
}

//COMMENTS: use if we want to add comments
QSqlQuery DocumentsDB::getCommentsOfDocWithUID(int uid){
    QSqlQuery q;
    if(!q.exec("SELECT * FROM rating_info WHERE book_id = "+QString::number(uid))){
        qDebug()<<"Error in getCommentsOfDocWithUID: " + QString::number(uid);
        qDebug()<< q.lastError();
    }
    return q;
}

QSqlQuery DocumentsDB::matchSearch(QString text, int column)
{
    QString col;
    if(column == 1)
        col = "title";
    else if(column == 2)
        col = "posted_by";
    else
        col = "genre";
    QSqlQuery q;
    if(!q.exec("select * from doc_info where "+col+" = '"+text+"';"))
    {
        qDebug() << "Error in matchSearch";
        qDebug() <<  q.lastError();
    }
    return q;
}
