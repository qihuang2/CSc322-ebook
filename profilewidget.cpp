#include "profilewidget.h"
#include <QTableWidget>
#include <QPushButton>
#include "historydb.h"
#include "librarywidget.h"
#include "documentwidget.h"
#include <QHeaderView>

ProfileWidget::ProfileWidget(RegisteredUser *user, QWidget *parent) : QWidget(parent)
{

    //Create the History Table
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

    //Create the buttons
    m_giftButton = new QPushButton("Gift to a friend");
    m_giftButton->setMaximumSize(QSize(200, 50));
    m_showHistory = new QPushButton("Show my history");
    m_showHistory->setMaximumSize(QSize(200,50));
    m_hideHistory = new QPushButton("Hide the History Table");
    m_hideHistory->setMaximumSize(QSize(200, 50));
    m_submitGift = new QPushButton("Send this gift");
    m_submitGift->setMaximumSize(200, 50);

    //Create the Line Edit
    m_sendCredits = new QLineEdit();
    m_sendCredits->setPlaceholderText("Enter an amount here");
    m_sendCredits->setMaximumSize(QSize(200, 50));

    //Create the Combo Box
    m_userList = new QComboBox();
    m_userList->setMaximumSize(200, 50);
    QSqlQuery user_list = user->getAllUsers();
    while (user_list.next())
    {
        QString user(user_list.value(0).toString());
        m_userList->addItem(user);
    }

    //Create the Layout
    QVBoxLayout *QV=new QVBoxLayout();
    giftLayout = new QHBoxLayout();
    giftLayout->addWidget(m_userList);
    giftLayout->addWidget(m_sendCredits);
    giftLayout->addWidget(m_submitGift);
    QV->addWidget(new QLabel("Username: " + user->getUsername()));
    QV->addWidget(new QLabel("Remaining Credits: " + QString::number(user->getNumOfCredits())));
    QV->addWidget(m_giftButton);
    QV->addLayout(giftLayout);
    QV->addWidget(m_showHistory);
    QV->addWidget(m_hideHistory);
    QV->addWidget(m_historyText);
    QV->setAlignment(Qt::AlignTop);

    setLayout(QV);

    createActions();

    //Hide the gift layout and history table
    m_hideHistory->hide();
    m_historyText->hide();
    m_userList->hide();
    m_sendCredits->hide();
    m_submitGift->hide();
}

void ProfileWidget::createActions()
{
    connect(m_showHistory, SIGNAL(clicked()), this, SLOT(showHistory()));
    connect(m_hideHistory, SIGNAL(clicked()), this, SLOT(hideHistory()));
    connect(m_giftButton, SIGNAL(clicked()), this, SLOT(showGift()));
    connect(m_submitGift, SIGNAL(clicked()), this, SLOT(hideGift()));
}

void ProfileWidget::showHistory()
{
    m_historyText->show();
    m_hideHistory->show();
    m_showHistory->hide();
}

void ProfileWidget::hideHistory()
{
    m_historyText->hide();
    m_hideHistory->hide();
    m_showHistory->show();
}

void ProfileWidget::showGift()
{
    m_userList->show();
    m_sendCredits->show();
    m_submitGift->show();
    m_giftButton->hide();
}

void ProfileWidget::hideGift()
{
    m_userList->hide();
    m_sendCredits->hide();
    m_submitGift->hide();
    m_giftButton->show();
}


void ProfileWidget::update_History(RegisteredUser* user)
{
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
}


ProfileWidget::~ProfileWidget() {}
