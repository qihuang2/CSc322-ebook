#include "mainwindow.h"
#include "librarywidget.h"
#include "registereduser.h"
#include "visitinguser.h"
#include "uploadwidget.h"
#include "documentwidget.h"
#include<documentsdb.h>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include<QDebug>
#include <QtSql>

enum {LIB, UP, DOC};

MainWindow::MainWindow(QString loginUsername, int userType)
{
    //if is visiting user
    if (userType == 0) m_user = new VisitingUser();

    //if is registered user
    else if (userType == 1) m_user = new RegisteredUser(loginUsername);

    //need a superuser class. using registed user for the moment
    else m_user = new RegisteredUser(loginUsername);

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
    LibraryWidget* lib = new LibraryWidget(m_tabWidget);
    UploadWidget* up = new UploadWidget(m_tabWidget);
    DocumentWidget* doc = new DocumentWidget(m_tabWidget);

    m_tabWidget->addTab(lib, "Library");
    m_tabWidget->addTab(up, "Upload");
    m_tabWidget->addTab(doc, "Document");

    m_loginLabel = new QLabel();

    //Set username
    m_loginLabel->setText(QString("Logged in as: %1").arg(m_user->getUsername()));

    //if it's a registered user or super user, print info
    if (m_user->getUserType() != 0) {

        //Test info
        RegisteredUser* t = static_cast<RegisteredUser*>(m_user); //cast to registered user
        
        qDebug()<< "Username: "<<t->getUsername()<< "   Credits: "<<t->getNumOfCredits();
        qDebug()<<"Complaints: "<<t->getNumOfComplaints()<<"   Date Created: "<< t->getDateCreated();
        qDebug()<<"Uploads: "<<t->getNumOfUploads();
        

    }

    m_exitButton = new QPushButton("Exit");
    m_exitButton->setMaximumSize(QSize(100, 50));

    m_centralWidget = new QWidget();
}

void MainWindow::createLayouts() {
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->addWidget(m_loginLabel);
    m_mainLayout->addWidget(m_tabWidget);
    m_mainLayout->addWidget(m_exitButton);

    m_centralWidget->setLayout(m_mainLayout);
}

void MainWindow::createActions() {
    connect(m_exitButton, SIGNAL(clicked()),
            this, SLOT(close()));
    connect(m_tabWidget, SIGNAL(currentChanged(int)),
            this, SLOT(s_refreshTable(int)));
}

void MainWindow::s_refreshTable(int current) {
    if(current == LIB) {
        LibraryWidget* w = (LibraryWidget*)m_tabWidget->widget(LIB);
        w->s_refresh();
    }
}

MainWindow::~MainWindow() {}
