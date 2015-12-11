#include "profilewidget.h"
#include <QTableWidget>
#include <QPushButton>
#include "historydb.h"
#include "librarywidget.h"
#include "documentwidget.h"
#include <QHeaderView>

enum {UID, TITLE, ASKINGPRC, CO, ACCEPT, DECLINE};

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
    m_counterofferTable->setColumnCount(DECLINE+1);
    m_counterofferTable->setHorizontalHeaderLabels(QStringList() << "UID" << "DOC Title" << "Asking Price" <<
                                                   "Counter Offer"<<"Accept"<<"Decline");
    m_counterofferTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_counterofferTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    populateTable();
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
    connect(m_counterofferTable, SIGNAL(cellClicked(int, int)),
            this, SLOT(s_buttonClicked(int,int)));
    connect(m_counterofferTable, SIGNAL(cellClicked(int,int)), m_parent, SLOT(s_updateCredit()));
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

void ProfileWidget::s_accept(int row)
{

    //TODO: get book uid
    //call m_user->approveSuperUserCounterForBook(book uid, true);
    //the function above changes the users credits for us
    QString title=m_counterofferTable->item(row,TITLE)->text();
    int id = m_counterofferTable->item(row, UID)->text().toInt();
    m_user->approveSuperUserCounterForBook(id,true);
}

void ProfileWidget::s_decline(int row)
{
    //what happen if decline?
    //get book uid
    //call m_user->approveSuperUserCounterForBook(book uid, false)
    QString title=m_counterofferTable->item(row,0)->text();
    DocumentsDB *docDB=new DocumentsDB();
    int id = m_counterofferTable->item(row, UID)->text().toInt();
    m_user->approveSuperUserCounterForBook(id,false);

}

void ProfileWidget::s_buttonClicked(int row, int col) {
    if(col == 3) {
        s_accept(row);
        ClearTable();
        populateTable();
    }else if(col == 4) {
        s_decline(row);
        ClearTable();
        populateTable();
    }
}

void ProfileWidget::ClearTable()
{
    while (m_counterofferTable->rowCount() > 0)
    {
        m_counterofferTable->removeRow(0);
    }
}

void ProfileWidget::populateTable()
{

    //TODO: maybe change this table to the following columns:
    //DOC Title
    //Asking Price  //getPending().value(10)
    //Counter Offer //if (column named 'approved' == 1) counterOffer = getPending.value(11) else counterOffer = null
    //Accept
    //Decline
    QSqlQuery getPending = m_user->getPendingDocuments();
    while(getPending.next())
    {
        int rowIndex = m_counterofferTable->rowCount();
        m_counterofferTable->insertRow(rowIndex);
        QString Ask_price(getPending.value(MainDB::ASKINGPRICE).toString());
        QString offer(getPending.value(MainDB::COUNTEROFFER).toString());
        QString title(getPending.value(MainDB::TITLE).toString());
        QString id(getPending.value(MainDB::UID).toString());

        m_counterofferTable->setItem(rowIndex, UID, new QTableWidgetItem(id));
        m_counterofferTable->setItem(rowIndex, TITLE, new QTableWidgetItem(title));
        m_counterofferTable->setItem(rowIndex, ASKINGPRC, new QTableWidgetItem(Ask_price));
        m_counterofferTable->setItem(rowIndex, CO, new QTableWidgetItem(offer));
        m_counterofferTable->setCellWidget(rowIndex, ACCEPT, new QLabel(tr("Accept")));
        m_counterofferTable->setCellWidget(rowIndex, DECLINE, new QLabel(tr("Decline")));
    }
}

ProfileWidget::~ProfileWidget() {}
