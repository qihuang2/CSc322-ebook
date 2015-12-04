#include "welcomedialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "loginwidget.h"
#include "registerwidget.h"
#include "logindb.h"

WelcomeDialog::WelcomeDialog(QString *username, int *userType)
{
    m_username = username;
    m_userType = userType;
    m_loginDB = new LoginDB();

    //m_loginDB->deleteTable("doc_info");

    // Create and configure buttons
    createWidgets();
    // Add buttons to the layout
    createLayouts();
    // Connect buttons to slots
    createActions();

    // Configure window
    setWindowTitle(tr("Welcome!"));
    setFixedSize(QSize(300, 150));

    setLayout(m_mainLayout);
}

void WelcomeDialog::createWidgets() {
    QSize buttonSize(100, 50);
    // Create buttons and set their maxmimum sized
    m_login = new QPushButton(tr("Login"));
    m_login->setMaximumSize(buttonSize);
    m_register = new QPushButton(tr("Register"));
    m_register->setMaximumSize(buttonSize);
    m_visit = new QPushButton(tr("Visit"));
    m_visit->setMaximumSize(buttonSize);
    m_exit = new QPushButton(tr("Exit"));
    m_exit->setMaximumSize(buttonSize);
}

void WelcomeDialog::createLayouts() {
    // Configure layout (add buttons, manage size)
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->addWidget(m_login);
    m_mainLayout->addWidget(m_register);
    m_mainLayout->addWidget(m_visit);
    m_mainLayout->addWidget(m_exit);
    m_mainLayout->setAlignment(Qt::AlignCenter);
}

void WelcomeDialog::createActions() {
    connect(m_login, SIGNAL(clicked()),
            this, SLOT(s_login()));
    connect(m_register, SIGNAL(clicked()),
            this, SLOT(s_register()));
    connect(m_visit, SIGNAL(clicked()),
            this, SLOT(s_visit()));
    connect(m_exit, SIGNAL(clicked()),
            this, SLOT(s_exit()));
}

void WelcomeDialog::s_login() {
    // If login was accepted, show main window
    LoginWidget* lWidget = new LoginWidget(m_loginDB, m_username, m_userType);
    if(lWidget->exec() == QDialog::Accepted) {
        //username and usertype will be set by lWidget
        accept();
    }
}

void WelcomeDialog::s_register() {
    // If successfully registered, show main window
    RegisterWidget* regWidget = new RegisterWidget(m_loginDB, m_username, m_userType);
    if(regWidget->exec() == QDialog::Accepted) {
        // username and usertype will have been set by regWidget
        accept();
    }

}

void WelcomeDialog::s_visit() {
    // No login or registration required, show main window
    // return accepted and that user is NOT logged in
    accept();
}

void WelcomeDialog::s_exit() {
    reject();
}
