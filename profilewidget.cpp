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
    m_creditLabel=new QLabel("Remaining Credits: " + QString::number(user->getNumOfCredits()));

    //Create the Layout
    QVBoxLayout *QV=new QVBoxLayout();
    giftLayout = new QHBoxLayout();
    giftLayout->addWidget(m_userList);
    giftLayout->addWidget(m_sendCredits);
    giftLayout->addWidget(m_submitGift);
    QV->addWidget(new QLabel("Username: " + user->getUsername()));
    QV->addWidget(m_creditLabel);
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
    connect(m_submitGift, SIGNAL(clicked()), m_parent, SLOT(s_updateCredit()));
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

ProfileWidget::~ProfileWidget() {}
