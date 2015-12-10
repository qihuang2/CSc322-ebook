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
enum {TITLE, USER, REQCRED, APPROVE, DECLINE, COUNTER, COUNTERVAL};

SuperWidget::SuperWidget(SuperUser* user, QWidget* parent) : QWidget(parent)
{
    m_user = user;

    m_lastRowClicked = -1;
    m_lastColClicked = -1;

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
    m_pending->setMouseTracking(true);
}

void SuperWidget::createLayouts() {
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->addWidget(m_pending);

    setLayout(m_mainLayout);
}

void SuperWidget::createActions() {
    connect(m_pending, SIGNAL(cellChanged(int,int)),
            this, SLOT(s_cellEntered(int,int)));
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

        QTablePushButton* approveButton = new QTablePushButton(tr("Accept"), index, APPROVE, this);
        QTablePushButton* declineButton = new QTablePushButton(tr("Decline"), index, DECLINE, this);
        QTablePushButton* counterButton = new QTablePushButton(tr("Counter"), index, COUNTER, this);

        connect(approveButton, SIGNAL(sendLoc(int,int)),
                this, SLOT(s_cellEntered(int,int)));
        connect(declineButton, SIGNAL(sendLoc(int,int)),
                this, SLOT(s_cellEntered(int,int)));
        connect(counterButton, SIGNAL(sendLoc(int,int)),
                this, SLOT(s_cellEntered(int,int)));


        // insert items to row
        m_pending->setItem(index, TITLE, new QTableWidgetItem(title));
        m_pending->setItem(index, USER, new QTableWidgetItem(user));
        m_pending->setItem(index, REQCRED, new QTableWidgetItem(reqCreds));

        m_pending->setCellWidget(index, APPROVE, approveButton);
        m_pending->setCellWidget(index, DECLINE, declineButton);
        m_pending->setCellWidget(index, COUNTER, counterButton);
    }
}

void SuperWidget::s_buttonClicked() {
    if(m_lastColClicked == APPROVE) {
        accept(m_lastRowClicked);
    }else if(m_lastColClicked == DECLINE) {
        decline(m_lastRowClicked);
    }else if(m_lastColClicked == COUNTER) {
        counter(m_lastRowClicked);
    }
}

void SuperWidget::accept(int row)
{
    //use m_user->acceptDocumentWithUID(int bookID)
    //afterwards, RU still has to confirm

    qDebug() << "Accepted row " << row;
}

void SuperWidget::decline(int row)
{
    //use m_user->deleteBookWithUID(int uid) to delete the book
    qDebug() << "Declined row " << row;
}

void SuperWidget::counter(int row)
{
    //user m_user->declineDocumentWithUID(int bookID, int counterOffer)
    qDebug() << "Countered row " << row;
}

void SuperWidget::s_cellEntered(int row, int col) {
    qDebug() << "Row: " << row << " Col: " << col;
}
