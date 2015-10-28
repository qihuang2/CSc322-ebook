#include "registerwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include "logindb.h"

RegisterWidget::RegisterWidget(LoginDB* db, QString* username, int* userType, QWidget *parent) : QDialog(parent)
{
    m_loginDB = db;
    m_userType = userType;
    m_username = username;

    setFixedSize(320, 250);
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("Register");

    createWidgets();
    createLayouts();
    createActions();
}

void RegisterWidget::createWidgets(){
    m_userLabel = new QLabel("Username:");
    m_passLabel = new QLabel("Password:");
    m_confirmLabel = new QLabel("Confrm:");
    m_userLineEdit = new QLineEdit();
    m_userLineEdit->setMaxLength(12);
    m_passLineEdit = new QLineEdit();
    m_passLineEdit->setMaxLength(14);
    m_passLineEdit->setEchoMode(QLineEdit::Password);
    m_confirmLineEdit = new QLineEdit();
    m_confirmLineEdit->setMaxLength(14);
    m_confirmLineEdit->setEchoMode(QLineEdit::Password);
    m_registerButton = new QPushButton("Register");
    m_cancelButton = new QPushButton("Cancel");
}

void RegisterWidget::createLayouts(){
    QVBoxLayout* vbox = new QVBoxLayout(this);
    QHBoxLayout* hbox1 = new QHBoxLayout();
    QHBoxLayout* hbox2 = new QHBoxLayout();
    QHBoxLayout* hbox3 = new QHBoxLayout();
    QHBoxLayout* hbox4 = new QHBoxLayout();

    hbox1->addWidget(m_userLabel, 1);
    hbox1->addWidget(m_userLineEdit, 2);
    hbox2->addWidget(m_passLabel, 1);
    hbox2->addWidget(m_passLineEdit,2);
    hbox3->addWidget(m_confirmLabel,1);
    hbox3->addWidget(m_confirmLineEdit,2);
    hbox4->addWidget(m_registerButton, 1);
    hbox4->addWidget(m_cancelButton, 1);

    vbox->addSpacing(1);
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    vbox->addLayout(hbox3);
    vbox->addLayout(hbox4);
}

void RegisterWidget::createActions(){
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(m_registerButton, SIGNAL(clicked()), this, SLOT(s_onRegister()));
}


void RegisterWidget::s_onRegister(){
    QString username = m_userLineEdit->text();
    username = username.toLower();
    QString password = m_passLineEdit->text();
    QString confirm = m_confirmLineEdit->text();

    //make sure username and passwords are valid
    if (!isValidUsername(username))
        QMessageBox::information(this, tr("Warning"), "Usernames can only contain letters and numbers.");
    else if (m_loginDB->userExists(username)){
        QMessageBox::information(this, tr("Warning"), "Username already taken.");
    }else if (!passwordsMatch(password,confirm)) {
        QMessageBox::information(this, tr("Warning"), "Passwords don't match.");
    }else if (!isValidPassword(password)) {
        QMessageBox::information(this, tr("Warning"), "Passwords must be 6-14 characters.");
    }else {
        m_loginDB->addUser(username,password,"1");
        *m_username = username;
        *m_userType = m_loginDB->getAccountType(username);
        this->accept();
    }
}

bool RegisterWidget::isValidPassword(QString password){
   if (password.length() < 6 || password.length() > 16) return false;
   for (int i = 0; i < password.length(); i++){
       int c = password.at(i).toLatin1();
       //We dont allow the chacaters ' "
       if (c == 39 || c == 34) return false;
       if (!(c >= 33 && c <= 122)) return false;
   }
   return true;
}

bool RegisterWidget::passwordsMatch(QString first, QString second){
    return (first.compare(second) == 0);
}

bool RegisterWidget::isValidUsername(QString username){
    //can't be named anon. Visiters will be called anon
    if(username.compare("anon") == 0) return false;
    for(int i = 0 ; i < username.length() ; i++){
        int c = username.at(i).toLatin1();
        //not number or letter, return false
        if( !((c >= 48 && c <= 57) || (c >= 97 && c <= 122)) ) return false;
    }
    return true;
}

RegisterWidget::~RegisterWidget(){}
