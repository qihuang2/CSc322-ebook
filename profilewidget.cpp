#include "profilewidget.h"
#include <QTableWidget>
#include <QPushButton>
#include "historydb.h"
#include "librarywidget.h"
#include "documentwidget.h"
#include <QHeaderView>

ProfileWidget::ProfileWidget(RegisteredUser *user, QWidget *parent) : QWidget(parent)
{
    m_historyText = new QTableWidget();

    HistoryDB *db=new HistoryDB();
    int row = db->getHistoryRow(user->getUsername());

    m_historyText->setRowCount(row+2);
    m_historyText->setColumnCount(1);
    m_historyText->setHorizontalHeaderLabels(QStringList() << "Recently Viewed");
    m_historyText->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_historyText->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(int i = 1; i <= row; ++i)
    {
        m_historyText->setRowHidden(0, true);
        m_historyText->setRowHidden(1, true);
        m_historyText->verticalHeader()->setVisible(false);
        QString s = db->getHistory(user->getUsername(),i-1);
        m_historyText->setItem(i, 1, new QTableWidgetItem(s));
    }

    m_giftButton = new QPushButton("Gift to a friend");
    m_giftButton->setMaximumSize(QSize(150, 50));
    //Add the history to the Profile layout
    QVBoxLayout *QV=new QVBoxLayout();
    QV->addWidget(new QLabel("Username: " + user->getUsername()));
    QV->addWidget(new QLabel("Remaining Credits: " + QString::number(user->getNumOfCredits())));
    QV->addWidget(m_giftButton);
    QV->addWidget(m_historyText);

    setLayout(QV);
}

void ProfileWidget::update_History()
{
    /*
    HistoryDB *db=new HistoryDB();
    int row = db->getHistoryRow(user->getUsername());
    m_historyText->setRowCount(row+2);
    m_historyText->setColumnCount(1);
    m_historyText->setHorizontalHeaderLabels(QStringList() << "History Table");
    m_historyText->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_historyText->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i = 1; i <= row; ++i)
    {
        m_historyText->setRowHidden(0, true);
        m_historyText->setRowHidden(1, true);
        m_historyText->verticalHeader()->setVisible(false);
        QString s = db->getHistory(user->getUsername(),i-1);
        m_historyText->setItem(i, 1, new QTableWidgetItem(s));
    }
    */
}


ProfileWidget::~ProfileWidget() {}
