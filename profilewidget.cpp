#include "profilewidget.h"
#include <QTableWidget>
#include <QPushButton>
#include "historydb.h"
#include "librarywidget.h"
#include "documentwidget.h"
#include <QHeaderView>

ProfileWidget::ProfileWidget(RegisteredUser *user, MainWindow* mw, QWidget *parent) : QWidget(parent)
{

    m_parent = mw;

    //Create the buttons
    m_giftButton = new QPushButton("Gift to a friend");
    m_giftButton->setMaximumSize(QSize(200, 50));
    m_showHistory = new QPushButton("Show my history");
    m_showHistory->setMaximumSize(QSize(200,50));
    m_hideHistory = new QPushButton("Hide the History Table");
    m_hideHistory->setMaximumSize(QSize(200, 50));
    m_submitGift = new QPushButton("Send this gift");
    m_submitGift->setMaximumSize(200, 50);
    m_counteroffer = new QPushButton("Show Upload Requests");
    m_counteroffer->setMaximumSize(200, 50);
    m_hideCOTable = new QPushButton("Hide Upload Requests");
    m_hideCOTable->setMaximumSize(200, 50);
    m_approveButton = new QPushButton("Accept");
    m_approveButton->setMaximumSize(QSize(250, 50));
    m_declineButton = new QPushButton("Decline");
    m_declineButton->setMaximumSize(QSize(250, 50));

    //Create the History Table
    m_historyText = new QTableWidget();
    m_user=user;
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

    //Create the Approve/Decline Counter Offer Table
    m_counterofferTable = new QTableWidget();
    m_counterofferTable->setRowCount(1);
    m_counterofferTable->setColumnCount(3);

    //TODO: maybe change this table to the following columns:
    //DOC Title
    //Asking Price  //getPending().value(10)
    //Counter Offer //if (column named 'approved' == 1) counterOffer = getPending.value(11) else counterOffer = null
    //Accept
    //Decline
    m_counterofferTable->setHorizontalHeaderLabels(QStringList() << "Counter Offers from the Super-User" << "Accept" << "Decline");
    m_counterofferTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_counterofferTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QSqlQuery getPending = user->getPendingDocuments();
    while(getPending.next())
    {
        int rowIndex = m_counterofferTable->rowCount();
        m_counterofferTable->insertRow(rowIndex);

        QString pending(getPending.value(11).toString());

        m_counterofferTable->setItem(rowIndex-1, 0, new QTableWidgetItem(pending, 0));
//        m_counterofferTable->setCellWidget(rowIndex, 1, m_approveButton);
//        m_counterofferTable->setCellWidget(rowIndex, 2, m_declineButton);
        QLabel* acceptLabel=new QLabel("Accept");
        QLabel* declineLabel=new QLabel("Decline");
        m_counterofferTable->setCellWidget(rowIndex-1, 1, acceptLabel);
        m_counterofferTable->setCellWidget(rowIndex-1, 2, declineLabel);
    }
//    m_counterofferTable->setCellWidget(0, 1, m_approveButton);
//    m_counterofferTable->setCellWidget(0, 2, m_declineButton);
    //Create the Line Edit
    m_sendCredits = new QLineEdit();
    m_sendCredits->setPlaceholderText("Enter an amount here, has to be an integer");
    m_sendCredits->setMaximumSize(QSize(300, 50));

    //Create the Combo Box
    m_userList = new QComboBox();
    m_userList->setMaximumSize(200, 50);
    QSqlQuery user_list = user->getAllUsers();
    while (user_list.next())
    {
        QString am_user(user_list.value(0).toString());
        if (am_user == user->getUsername())
            continue;
        else
            m_userList->addItem(am_user);
    }

    //Create the label
    m_creditLabel = new QLabel("Remaining Credits: " + QString::number(user->getNumOfCredits()));
    m_complaintLabel = new QLabel("Number of Complaint(s): " + QString::number(user->getNumOfDeletedBooks()));
    m_datecreateLabel = new QLabel("Member Since: " + user->getDateCreated());

    //Create the Layout
    QVBoxLayout *QV=new QVBoxLayout();
    giftLayout = new QHBoxLayout();
    giftLayout->addWidget(m_userList);
    giftLayout->addWidget(m_sendCredits);
    giftLayout->addWidget(m_submitGift);
    QV->addWidget(new QLabel("Username: " + user->getUsername()));
    QV->addWidget(m_creditLabel);
    QV->addWidget(m_complaintLabel);
    QV->addWidget(m_datecreateLabel);
    QV->addWidget(m_giftButton);
    QV->addLayout(giftLayout);
    QV->addWidget(m_showHistory);
    QV->addWidget(m_hideHistory);
    QV->addWidget(m_counteroffer);
    QV->addWidget(m_historyText);
    QV->addWidget(m_hideCOTable);
    QV->addWidget(m_counterofferTable);
    QV->setAlignment(Qt::AlignTop);

    setLayout(QV);

    createActions();

    //Hide the gift layout and history table
    m_hideCOTable->hide();
    m_counterofferTable->hide();
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
    connect(m_submitGift, SIGNAL(clicked()), m_parent, SLOT(s_updateCredit()));
    connect(m_counteroffer, SIGNAL(clicked()), this, SLOT(showCOTable()));
    connect(m_hideCOTable, SIGNAL(clicked()), this, SLOT(hideCOTable()));
    connect(m_counterofferTable, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(s_accept()));
    connect(m_counterofferTable, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(s_decline()));
    connect(m_counterofferTable, SIGNAL(cellDoubleClicked(int,int)), m_parent, SLOT(s_updateCredit()));
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
    QString credits = m_sendCredits->text();
    QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
    if (re.exactMatch(credits) && credits.toInt() <= m_user->getNumOfCredits())
    {
        m_user->changeCreditsBy(-credits.toInt());
        m_creditLabel->setText("Remaining Credits: " + QString::number(m_user->getNumOfCredits()));
        QString picked = m_userList->currentText();
        RegisteredUser* r_user = new RegisteredUser(picked);
        r_user->changeCreditsBy(credits.toInt());
        QMessageBox::information(this, tr("Sent!"),
            "Your gift has been sent!");
    }
    else
        QMessageBox::information(this, tr("Error"),
            "Your gift can only be integers and your gift cannot exceed your total credits.");
    m_userList->hide();
    m_sendCredits->hide();
    m_sendCredits->clear();
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

void ProfileWidget::updatepwCredits()
{
    m_creditLabel->setText("Remaining Credits: " + QString::number(m_user->getNumOfCredits()));
}

void ProfileWidget::showCOTable()
{
    m_counteroffer->hide();
    m_hideCOTable->show();
    m_counterofferTable->show();
}

void ProfileWidget::hideCOTable()
{
    m_counteroffer->show();
    m_hideCOTable->hide();
    m_counterofferTable->hide();
}

void ProfileWidget::s_accept()
{
    QModelIndex currentIndex = m_counterofferTable->currentIndex();
    int row = currentIndex.row();
    int column=currentIndex.column();
    if(column==1)
    {
        //TODO: get book uid
        //call m_user->approveSuperUserCounterForBook(book uid, true);
        //the function above changes the users credits for us
       QString m_credits=m_counterofferTable->item(row,0)->text();
        m_creditLabel->setText("Remaining Credits: " + QString::number(m_user->getNumOfCredits()));
        qDebug()<<"registered user accept counter offer";
    }
    //should have a function to set Approved to 3 when register user accept.
}

void ProfileWidget::s_decline()
{
    //what happen if decline?
    //get book uid
    //call m_user->approveSuperUserCounterForBook(book uid, false)
}

ProfileWidget::~ProfileWidget() {}
