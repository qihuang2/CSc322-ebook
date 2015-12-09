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

enum {TITLE, USER, REQCRED, APPROVE, DECLINE, COUNTER, COUNTERVAL};

SuperWidget::SuperWidget(SuperUser* user, QWidget* parent) : QWidget(parent)
{
    m_user = user;
    createWidgets();
    createLayouts();
    createActions();
}

void SuperWidget::createWidgets() {
    //m_pending = new QTableWidget(m_user->getSupersPendingDocuments().value(0).toInt(), COUNTERVAL+1);
    m_pending = new QTableWidget();
    m_pending->setColumnCount(COUNTERVAL+1);
    m_pending->setHorizontalHeaderLabels(QStringList() << "Title" << "User" << "Cred. Request" << "Approve" << "Decline" << "Counter" << "Counter Value");
    m_pending->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_pending->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_accept = new QPushButton(tr("Accept"));
    m_decline = new QPushButton(tr("Decline"));
    m_counter = new QPushButton(tr("Counter"));
    m_counterValue = new QSpinBox();
}

void SuperWidget::createLayouts() {
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->addWidget(m_pending);

    setLayout(m_mainLayout);
}

void SuperWidget::createActions() {

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
        // retrieve doc info
        QString title(pending.value(MainDB::TITLE).toString());
        QString user(pending.value(MainDB::POSTEDBY).toString());
        QString reqCreds(pending.value(MainDB::ASKINGPRICE).toString());

        // insert items to row
        m_pending->setItem(index, TITLE, new QTableWidgetItem(title));
        m_pending->setItem(index, USER, new QTableWidgetItem(user));
        m_pending->setItem(index, REQCRED, new QTableWidgetItem(reqCreds));

        m_pending->setCellWidget(index, APPROVE, m_accept);
        m_pending->setCellWidget(index, DECLINE, m_decline);
        m_pending->setCellWidget(index, COUNTER, m_counter);
        m_pending->setCellWidget(index, COUNTERVAL, m_counterValue);
    }
}
