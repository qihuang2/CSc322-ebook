#include "superwidget.h"
#include "superuser.h"
#include <QSqlQuery>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QSpinBox>
#include "documentsdb.h"
#include <QDebug>
#include <QLabel>
enum {TITLE, USER, REQCRED, APPROVE, DECLINE, COUNTER, COUNTERVAL};

SuperWidget::SuperWidget(SuperUser* user, QWidget* parent) : QWidget(parent)
{
    m_user = user;
    createWidgets();
    createLayouts();
    createActions();
    populateTable();
}

void SuperWidget::createWidgets() {
    //m_pending = new QTableWidget(m_user->getSupersPendingDocuments().value(0).toInt(), COUNTERVAL+1);
    m_pending = new QTableWidget();
    m_pending->setColumnCount(COUNTERVAL+1);
    m_pending->setHorizontalHeaderLabels(QStringList() << "Title" << "User" << "Cred. Request" << "" << "" << "" << "Counter Value");
    m_pending->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_pending->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void SuperWidget::createLayouts() {
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->addWidget(m_pending);

    setLayout(m_mainLayout);
}

void SuperWidget::createActions() {
    connect(m_pending, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(s_accept()));
    connect(m_pending, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(s_decline()));
}

void SuperWidget::populateTable() {
    /*Create the Approve/Decline Counter Offer Table
    m_counterofferTable = new QTableWidget();
    m_counterofferTable->setColumnCount(3);
    m_counterofferTable->setHorizontalHeaderLabels(QStringList() << "Counter Offers from the Super-User" << "Accept" << "Decline");
    m_counterofferTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_counterofferTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QSqlQuery getPending = user->getPendingDocuments();
    while(getPending.next())
    {
        int rowIndex = m_counterofferTable->rowCount();
        m_counterofferTable->insertRow(rowIndex);

        QString pending(getPending.value(0).toString());

        m_counterofferTable->setItem(rowIndex, 0, new QTableWidgetItem(pending, 0));
        m_counterofferTable->setCellWidget(rowIndex, 1, m_approveButton);
        m_counterofferTable->setCellWidget(rowIndex, 2, m_declineButton);
    }*/


    QSqlQuery pending = m_user->getSupersPendingDocuments();
    while(pending.next()) {
        int index = m_pending->rowCount();
        m_pending->insertRow(index);
        // retrieve doc info
        QString title(pending.value(MainDB::TITLE).toString());
        QString user(pending.value(MainDB::POSTEDBY).toString());
        QString reqCreds(pending.value(MainDB::ASKINGPRICE).toString());

        // insert items to row
        m_pending->setItem(index, TITLE, new QTableWidgetItem(title));
        m_pending->setItem(index, USER, new QTableWidgetItem(user));
        m_pending->setItem(index, REQCRED, new QTableWidgetItem(reqCreds));

        m_accept = new QPushButton(tr("Accept"));
        m_decline = new QPushButton(tr("Decline"));
        m_counter = new QPushButton(tr("Counter"));
        m_counterValue = new QSpinBox();
        m_counterValue->setMaximum(1000);
        QLabel* acceptLabel=new QLabel("Accept");
        QLabel* declineLabel=new QLabel("Decline");
        m_pending->setCellWidget(index, APPROVE, acceptLabel);
        m_pending->setCellWidget(index, DECLINE, declineLabel);
        m_pending->setCellWidget(index, COUNTER, m_counter);
        m_pending->setCellWidget(index, COUNTERVAL, m_counterValue);
    }
}

void SuperWidget::s_accept()
{
    QModelIndex currentIndex = m_pending->currentIndex();
    int row = currentIndex.row();
    int column=currentIndex.column();
    if(column==3)
    {
        m_title=m_pending->item(row,0)->text();
        m_username=m_pending->item(row,1)->text();
        m_credits=m_pending->item(row,2)->text();
        qDebug()<<row<<m_title<<m_username<<m_credits;
        //get ID and accept
        DocumentsDB *db=new DocumentsDB();
        int m_id=db->getbookID(m_title,m_username,0,0);
        qDebug()<<"m_id"<<m_id<<" Accept";
        m_user->acceptDocumentWithUID(m_id);
    }
}

void SuperWidget::s_decline()
{
    QModelIndex currentIndex = m_pending->currentIndex();
    int row = currentIndex.row();
    m_title=m_pending->item(row,0)->text();
    m_username=m_pending->item(row,1)->text();
    m_credits=m_pending->item(row,2)->text();
    int column=currentIndex.column();
    if(column==4)
    {
        DocumentsDB *db=new DocumentsDB();
        int m_id=db->getbookID(m_title,m_username,0,0);
        m_user->deleteBookWithUID(m_id);
        qDebug()<<"m_id"<<m_id<<" Decline";
    }
}

void SuperWidget::s_counter()
{

}
