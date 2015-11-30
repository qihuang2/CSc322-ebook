#include "loginwidget.h"
#include "logindb.h"
#include <QChar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>


LoginWidget::LoginWidget(LoginDB* db, QString* username, int* userType, QWidget* parent) : QDialog(parent)
{
    m_loginDB = db;
    m_username = username;
    m_userType = userType;


    setFixedSize(320, 150);
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("Log in");

    createWidgets();
    createLayouts();
    createActions();
}


void LoginWidget::createWidgets(){
    m_userLabel = new QLabel("Username:");
    m_passLabel = new QLabel("Password:");
    m_userLineEdit = new QLineEdit();
    m_userLineEdit->setMaxLength(12);
    m_passLineEdit = new QLineEdit();
    m_passLineEdit->setMaxLength(14);
    m_passLineEdit->setEchoMode(QLineEdit::Password);
    m_loginButton = new QPushButton("Login");
    m_cancelButton = new QPushButton("Cancel");
}

void LoginWidget::createLayouts(){
    QVBoxLayout* vbox = new QVBoxLayout(this);
    QHBoxLayout* hbox1 = new QHBoxLayout();
    QHBoxLayout* hbox2 = new QHBoxLayout();
    QHBoxLayout* hbox3 = new QHBoxLayout();

    hbox1->addWidget(m_userLabel, 1);
    hbox1->addWidget(m_userLineEdit, 2);
    hbox2->addWidget(m_passLabel, 1);
    hbox2->addWidget(m_passLineEdit, 2);
    hbox3->addWidget(m_loginButton, 1);
    hbox3->addWidget(m_cancelButton, 1);

    vbox->addSpacing(1);
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    vbox->addLayout(hbox3);
}

void LoginWidget::createActions(){
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(m_loginButton, SIGNAL(clicked()), this, SLOT(s_onLogin()));
}

void LoginWidget::s_onLogin(){
    QString username = m_userLineEdit->text();
    username = username.toLower();
    QString password = m_passLineEdit->text();
    
    //if not valid username, password, show message box
    if (!isValidUsername(username) || !isValidPassword(password) || !m_loginDB->checkUserAndPass(username,password)){
        QMessageBox::information(this, tr("Warning"), "Invalid username or password.");
    }else if(m_loginDB->isBanned(username)){
        //if banned, show message box
        QMessageBox::information(this, tr("Warning"), "Account is banned.");
    }else {
        *m_username = username;
        *m_userType = m_loginDB->getAccountType(username);
        accept();
    }
}

bool LoginWidget::isValidPassword(QString password){
   if (password.length() < 6 || password.length() > 16) return false;
   for (int i = 0; i < password.length(); i++){
       int c = password.at(i).toLatin1();
       //We dont allow the chacaters ' "
       if (c == 39 || c == 34) return false;
       if (!(c >= 33 && c <= 122)) return false;
   }
   return true;
}

bool LoginWidget::isValidUsername(QString username){
    for(int i = 0 ; i < username.length() ; i++){
        int c = username.at(i).toLatin1();
        //not number or letter, return false
        if( !((c >= 48 && c <= 57) || (c >= 97 && c <= 122)) ) return false;
    }
    return true;
}

LoginWidget::~LoginWidget() {}

