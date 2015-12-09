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
    connect(m_pending, SIGNAL(cellClicked(int, int)),
            this, SLOT(s_buttonClicked(int,int)));
}

void SuperWidget::populateTable() {
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

        m_pending->setCellWidget(index, APPROVE, new QPushButton(tr("Accept")));
        m_pending->setCellWidget(index, DECLINE, new QPushButton(tr("Decline")));
        m_pending->setCellWidget(index, COUNTER, new QPushButton(tr("Counter")));
    }
}

void SuperWidget::s_buttonClicked(int row, int col) {
    if(col == APPROVE) {
        accept(row);
    }else if(col == DECLINE) {
        decline(row);
    }else if(col == COUNTER) {
        counter(row);
    }
}

void SuperWidget::accept(int row)
{

}

void SuperWidget::decline(int row)
{

}

void SuperWidget::counter(int row)
{

}
