#include "mainwindow.h"
#include "librarywidget.h"
#include "registereduser.h"
#include "uploadwidget.h"
#include "documentwidget.h"
#include "profilewidget.h"
#include "superwidget.h"
#include "superuser.h"
#include "historydb.h"
#include <documentsdb.h>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QtSql>

enum {LIB, UP, DOC, HISTORY, SUPER};

MainWindow::MainWindow(BaseUser *user)
{
    m_user = user;

    if(m_user->getUserType() == BaseUser::VISITING) {
        qDebug() << "Visiting";
    }else if(m_user->getUserType() == BaseUser::REGISTERED) {
        qDebug() << "Reg";
    }else {
        qDebug() << "SUPER";
    }

    //init DB that keeps track of uploaded documents
    this->m_docDB = new DocumentsDB();

    createWidgets();
    createLayouts();
    createActions();

    setCentralWidget(m_centralWidget);
    setMinimumSize(600, 400);
    setWindowTitle("图书馆");
}

void MainWindow::createWidgets() {
    m_tabWidget = new QTabWidget();

    // create the widgets to be added to the tabs

    // library for all users
    LibraryWidget* lib = new LibraryWidget(m_user->getUsername(), this, m_tabWidget);
    m_tabWidget->addTab(lib, tr("Library"));

    //  only for registered/super
    if(!(m_user->getUserType() == BaseUser::VISITING)) {
        RegisteredUser* tmpUser = static_cast<RegisteredUser*>(m_user);
        UploadWidget* up = new UploadWidget(tmpUser, m_tabWidget);
        m_tabWidget->addTab(up, tr("Upload"));

        DocumentWidget* doc = new DocumentWidget(m_tabWidget, this, tmpUser,m_tabWidget);
        m_tabWidget->addTab(doc, tr("Document"));

        ProfileWidget* prof = new ProfileWidget(tmpUser, this, m_tabWidget);
        m_tabWidget->addTab(prof, tr("Profile"));

        m_credit = QString::number(tmpUser->getNumOfCredits());
    }

    if(m_user->getUserType() == BaseUser::SUPER) {
        SuperWidget* sw = new SuperWidget(static_cast<SuperUser*>(m_user));
        m_tabWidget->addTab(sw, tr("Super"));
    }

    m_name = m_user->getUsername();

    //Create the labels
    m_username = new QLabel();
    m_usercredits = new QLabel();
    m_username->setText("User Name: " + m_name);
    m_usercredits->setText("Credit(s) Remaining: " + m_credit);

    // if registered user show profile tab
    if(!(m_user->getUserType() == BaseUser::VISITING)) {
        RegisteredUser* tmp;
        if(m_user->getUserType() == BaseUser::REGISTERED) tmp = new RegisteredUser(m_user->getUsername());
        else tmp = new SuperUser(m_user->getUsername());
        ProfileWidget* pf = new ProfileWidget(tmp, this,m_tabWidget);
        m_tabWidget->addTab(pf,"My Profile");
    }

    // super user show super widget
    if(m_user->getUserType() == BaseUser::SUPER) {
        SuperWidget* sup = new SuperWidget((SuperUser*)m_user, m_tabWidget);
        m_tabWidget->addTab(sup, "Super User");
    }
    m_loginLabel = new QLabel();

    //Set username
    m_loginLabel->setText(QString("Logged in as: %1 %2").arg(m_user->getUsername()).arg(m_user->getUserType() == BaseUser::SUPER ? "(SU)" : ""));

    //if it's a registered user or super user, print info
    if (m_user->getUserType() != 0) {
        //Test info
        RegisteredUser* t = static_cast<RegisteredUser*>(m_user); //cast to registered user  
        qDebug()<< "Username: "<<t->getUsername()<< "   Credits: "<<t->getNumOfCredits();
        qDebug()<<"Complaints: "<<t->getNumOfDeletedBooks()<<"   Date Created: "<< t->getDateCreated();
        qDebug()<<"Uploads: "<<t->getNumOfUploads()<< "   UserType: "<< ((t->getUserType() == 1) ? "RU" : "SU") ;

    }

    //Create Buttons
    m_exitButton = new QPushButton("Exit");
    m_exitButton->setMaximumSize(QSize(100, 50));


    m_centralWidget = new QWidget();
}

void MainWindow::createLayouts() {
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->addWidget(m_loginLabel);
    m_mainLayout->addWidget(m_tabWidget);
    m_mainLayout->addWidget(m_exitButton);

    m_tabWidget->widget(HISTORY);

    m_centralWidget->setLayout(m_mainLayout);
}

void MainWindow::createActions() {
    connect(m_exitButton, SIGNAL(clicked()),
            this, SLOT(close()));
    connect(m_tabWidget, SIGNAL(currentChanged(int)),
            this, SLOT(s_refreshTable(int)));
    //connect(lib->m_openBook, SIGNAL(clicked()),this,SLOT(s_openBook()));
}

void MainWindow::s_refreshTable(int current) {
    if(current == LIB) {
        LibraryWidget* w = (LibraryWidget*)m_tabWidget->widget(LIB);
        w->s_refresh();
    }
    else if(current == DOC)
    {
        DocumentWidget*d=(DocumentWidget*)m_tabWidget->widget(DOC);
        d->ResumeTimer();
    }
}

void MainWindow::s_openBook()
{
    LibraryWidget* lib = (LibraryWidget*)m_tabWidget->widget(LIB);
    DocumentWidget* doc = (DocumentWidget*)m_tabWidget->widget(DOC);
    //Get the Path
    QString p = lib->getPath();

    //Update the view, match the book id, add one to its row it the view column
    m_docDB->addViewToDocWithUID(lib->getRow());

    //Open the Book after prompting yes or no
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Test", "Opening this document will cost you 15 credits.\n Do you wish to continue?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes)
      {
            s_updateHistory();
            doc->readFile(p);
            s_updateCredit();
            m_tabWidget->setCurrentIndex(2);
      }
}

void MainWindow::s_updateHistory()
{
    ProfileWidget* pw = (ProfileWidget*)m_tabWidget->widget(HISTORY);
    if(!(m_user->getUserType() == BaseUser::VISITING)) {
        RegisteredUser* tmp;
        if(m_user->getUserType() == BaseUser::REGISTERED)
            tmp = new RegisteredUser(m_user->getUsername());
        else
            tmp = new SuperUser(m_user->getUsername());
        pw->update_History(tmp);
    }
}

void MainWindow::s_updateCredit()
{
    DocumentWidget* dw = (DocumentWidget*)m_tabWidget->widget(DOC);
    ProfileWidget* pw = (ProfileWidget*)m_tabWidget->widget(HISTORY);
    dw->updateCredits();
    pw->updatepwCredits();
}


MainWindow::~MainWindow() {}
