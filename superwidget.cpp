#include "superwidget.h"
#include "superuser.h"
#include <QSqlQuery>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include "qtablepushbutton.h"
#include <QSpinBox>
#include "documentsdb.h"
#include <QDebug>
#include <QLabel>

enum {UID, TITLE, USER, REQCRED, APPROVE, DECLINE, COUNTER, COUNTERVAL};

SuperWidget::SuperWidget(SuperUser* user, QWidget* parent) : QWidget(parent)
{
    m_user = user;

    createWidgets();
    createLayouts();
    createActions();
    populateTable();
    populateComplaint();
    initialLayout();
}

void SuperWidget::createWidgets() {
    //pending table
    m_pending = new QTableWidget();
    m_pending->setColumnCount(COUNTERVAL+1);
    m_pending->setHorizontalHeaderLabels(QStringList() << "UID" << "Title" << "User" << "Cred. Request" << "" << "" << "" << "Counter Value");
    m_pending->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_pending->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_counterField = new QComboBox();

    // complaint table
    m_complaint = new QTableWidget();
    m_complaint->setColumnCount(4);
    m_complaint->setHorizontalHeaderLabels(QStringList() <<"User" << "Title" << "Reason" << "");
    m_complaint->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_complaint->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // todo combo box 
    m_banuser = new QComboBox();
    QSqlQuery user_list = m_user->getAllUsers();
    while (user_list.next())
    {
        QString am_user(user_list.value(0).toString());
        if (am_user == m_user->getUsername())
            continue;
        else
            m_banuser->addItem(am_user);
    }

    // setup buttons
    m_showPending =new QPushButton("Show Pending Table");
    m_hidePending =new QPushButton("Hide Pending Table");
    m_showComplaint= new QPushButton("Show Complaint Table");
    m_hideComplaint= new QPushButton("Hide Complaint Table");
    m_ban = new QPushButton("Ban");
    m_ban->setMaximumWidth(50);
    m_banuser->setMinimumWidth(150);
    m_showPending->setMaximumWidth(200);
    m_hidePending->setMaximumWidth(200);
    m_showComplaint->setMaximumWidth(200);
    m_hideComplaint->setMaximumWidth(200);
}

void SuperWidget::createLayouts() {
    m_mainLayout = new QVBoxLayout();
    QHBoxLayout *banLayout= new QHBoxLayout();
    banLayout->setAlignment(Qt::AlignLeft);
    banLayout->addWidget(m_banuser);
    banLayout->addWidget(m_ban);
    m_mainLayout->addLayout(banLayout);
    m_mainLayout->addWidget(m_showPending);
    m_mainLayout->addWidget(m_hidePending);
    m_mainLayout->addWidget(m_showComplaint);
    m_mainLayout->addWidget(m_pending);
    m_mainLayout->addWidget(m_hideComplaint);
    m_mainLayout->addWidget(m_complaint);
    m_mainLayout->setAlignment(Qt::AlignTop);
    setLayout(m_mainLayout);
}

void SuperWidget::createActions() {
    connect(m_ban, SIGNAL(clicked()), this, SLOT(s_ban()));
    connect(m_showPending, SIGNAL(clicked()), this, SLOT(s_showPendingTable()));
    connect(m_hidePending, SIGNAL(clicked()), this, SLOT(s_hidePendingTable()));
    connect(m_showComplaint, SIGNAL(clicked()), this, SLOT(s_showComplaintTable()));
    connect(m_hideComplaint, SIGNAL(clicked()), this, SLOT(s_hideComplaintTable()));
}

void SuperWidget::populateTable() {
    clearTable();

    QSqlQuery pending = m_user->getSupersPendingDocuments();
    while(pending.next()) {
        int index = m_pending->rowCount();
        m_pending->insertRow(index);

        // retrieve doc info
        QString uid(pending.value(MainDB::UID).toString());
        QString title(pending.value(MainDB::TITLE).toString());
        QString user(pending.value(MainDB::POSTEDBY).toString());
        QString reqCreds(pending.value(MainDB::ASKINGPRICE).toString());

        QTablePushButton*   approveButton = new QTablePushButton(tr("Accept"), index, APPROVE, this);
        QTablePushButton*   declineButton = new QTablePushButton(tr("Decline"), index, DECLINE, this);
        QTablePushButton*   counterButton = new QTablePushButton(tr("Counter"), index, COUNTER, this);
        QSpinBox*           counterValue = new QSpinBox();

        connect(approveButton, SIGNAL(sendLoc(int,int)),
                this, SLOT(s_buttonClicked(int,int)));
        connect(declineButton, SIGNAL(sendLoc(int,int)),
                this, SLOT(s_buttonClicked(int,int)));
        connect(counterButton, SIGNAL(sendLoc(int,int)),
                this, SLOT(s_buttonClicked(int,int)));


        // insert items to row
        m_pending->setItem(index, UID, new QTableWidgetItem(uid));
        m_pending->setItem(index, TITLE, new QTableWidgetItem(title));
        m_pending->setItem(index, USER, new QTableWidgetItem(user));
        m_pending->setItem(index, REQCRED, new QTableWidgetItem(reqCreds));

        m_pending->setCellWidget(index, APPROVE, approveButton);
        m_pending->setCellWidget(index, DECLINE, declineButton);
        m_pending->setCellWidget(index, COUNTER, counterButton);
        m_pending->setCellWidget(index, COUNTERVAL, counterValue);
    }
}

void SuperWidget::populateComplaint()
{
    QSqlQuery complaints=m_user->getAllDocumentsWithComplaints();
    while(complaints.next()) {
        int index = m_complaint->rowCount();
        m_complaint->insertRow(index);
        QString uid(complaints.value(0).toString());
        QString user(complaints.value(1).toString());
        QString reason(complaints.value(2).toString());

        QTablePushButton*   DeleteButton = new QTablePushButton(tr("Delete"), index, 3, this);
        connect(DeleteButton, SIGNAL(sendLoc(int,int)),
                this, SLOT(s_delete(int,int)));


        m_complaint->setItem(index, 0, new QTableWidgetItem(uid));
        m_complaint->setItem(index, 1, new QTableWidgetItem(user));
        m_complaint->setItem(index, 2, new QTableWidgetItem(reason));
        m_complaint->setCellWidget(index, 3, DeleteButton);
    }
}

void SuperWidget::s_delete(int row, int col)
{
    if(col == 3) {
        qDebug()<<"delete the document";
        m_user->deleteBookWithUID(m_complaint->item(row, 1)->text().toInt());
    }
}

void SuperWidget::accept(int row)
{
    qDebug() << "Accepted row " << row;
    //afterwards, RU still has to confirm

    int uid = m_pending->item(row, UID)->text().toInt();
    m_giveCredit = m_pending->item(row, REQCRED)->text().toInt();

    RegisteredUser* user = new RegisteredUser(m_pending->item(row, USER)->text());
    user->changeCreditsBy(m_giveCredit);
    delete user;

    //upload the book to the table
    m_user->acceptDocumentWithUID(uid);

    // Get username
    // create registered user
    // change credits by

    // get username
    // update database info for username key credits

}

void SuperWidget::decline(int row)
{
    qDebug() << "Declined row " << row;
    /*
    //use m_user->deleteBookWithUID(int uid) to delete the book
    qDebug() << "Declined row " << row;
    m_title=m_pending->item(row,0)->text();
    m_username=m_pending->item(row,1)->text();
    DocumentsDB *db=new DocumentsDB();
    int m_id=db->getbookID(m_title,m_username,1,0);
    m_user->deleteBookWithUID(m_id);
    */

}

void SuperWidget::counter(int row)
{
    /*
    QSqlQuery q;
    //delete row where u_id == id
    if(q.exec("UPDATE doc_info SET is_deleted = 1 WHERE u_id = "+QString::number(id)))
        qDebug()<< "Document has been deleted.";
    else{
        qDebug()<<"deleteDocumentWitUID: "+QString::number(id)+ " failed";
        qDebug()<<q.lastError();
    }
    */

    QSpinBox* box = dynamic_cast<QSpinBox*>(m_pending->cellWidget(row, COUNTERVAL));
    qDebug() << "Countered row " << row << " for " << box->value();

    int uid = m_pending->item(row, UID)->text().toInt();
    int counterVal = box->value();

    DocumentsDB* db = new DocumentsDB();
    db->modifyCounterForUID(uid, counterVal);


}

void SuperWidget::s_buttonClicked(int row, int col) {
    qDebug() << "Row: " << row << " Col: " << col;

    /*
    m_title=m_pending->item(row,0)->text();
    m_username=m_pending->item(row,1)->text();
    DocumentsDB *db=new DocumentsDB();
    int m_id=db->getbookID(m_title,m_username,1,0);
    m_user->declineDocumentWithUID(m_id,5);
    */

    if(col == APPROVE) {
        accept(row);
    }else if(col == DECLINE) {
        decline(row);
    }else if(col == COUNTER) {
        counter(row);
    }
    clearTable();
    populateTable();
}

void SuperWidget::clearTable()
{
    while (m_pending->rowCount() > 0)
    {
        m_pending->removeRow(0);
    }
}

void SuperWidget::s_ban()
{

    QString picked = m_banuser->currentText();
    m_user->banUser(picked);
    QMessageBox::information(this, tr("Ban!"),
                             "The use has been baned");
}

void SuperWidget::s_showPendingTable()
{
    m_pending->show();
    m_showPending->hide();
    m_hidePending->show();
}

void SuperWidget::s_hidePendingTable()
{
    m_pending->hide();
    m_showPending->show();
    m_hidePending->hide();
}

void SuperWidget::s_showComplaintTable()
{
    m_complaint->show();
    m_showComplaint->hide();
    m_hideComplaint->show();
}

void SuperWidget::s_hideComplaintTable()
{
    m_complaint->hide();
    m_showComplaint->show();
    m_hideComplaint->hide();
}

void SuperWidget::initialLayout()
{
    m_complaint->hide();
    m_pending->hide();
    m_hidePending->hide();
    m_hideComplaint->hide();
}



