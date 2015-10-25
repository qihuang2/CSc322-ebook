#include "loginwidget.h"
#include <QPushButton>
#include <QLabel>
#include <QChar>


LoginWidget::LoginWidget(QWidget *parent) : QDialog(parent)
{
    setFixedSize(320, 150);
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("Log in");

    LOGIN_DB = new LoginDB();
    
    userLabel = new QLabel("Username:");
    passLabel = new QLabel("Password:");
    userLineEdit = new QLineEdit();
    userLineEdit->setMaxLength(12);
    passLineEdit = new QLineEdit();
    passLineEdit->setMaxLength(14);
    passLineEdit->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton("Login");
    cancelButton = new QPushButton("Cancel");

    QVBoxLayout* vbox = new QVBoxLayout(this);
    QHBoxLayout* hbox1 = new QHBoxLayout();
    QHBoxLayout* hbox2 = new QHBoxLayout();
    QHBoxLayout* hbox3 = new QHBoxLayout();

    hbox1->addWidget(userLabel, 1);
    hbox1->addWidget(userLineEdit, 2);
    hbox2->addWidget(passLabel, 1);
    hbox2->addWidget(passLineEdit, 2);
    hbox3->addWidget(loginButton, 1);
    hbox3->addWidget(cancelButton, 1);

    vbox->addSpacing(1);
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    vbox->addLayout(hbox3);

    connect(cancelButton, SIGNAL(clicked()), this, SLOT(onCancel()));
    connect(loginButton, SIGNAL(clicked()), this, SLOT(onLogin()));
}

void LoginWidget::onCancel()
{
    LOGIN_DB->closeDB();
    this->destroy();
}

void LoginWidget::reject()
{
    onCancel();
}

void LoginWidget::onLogin(){
    QString username = userLineEdit->text();
    QString password = passLineEdit->text();
    if (!isValidPassword(password) || !LOGIN_DB->checkUserAndPass(username,password)){
        QMessageBox::information(this, tr("Warning"), "Invalid username or password.");
    }else if(LOGIN_DB->isBanned(username)){
        QMessageBox::information(this, tr("Warning"), "Account is banned.");
    }else {
        LOGIN_DB->closeDB();
        this->destroy();
        //NEED WAY TO LINK THIS BACK
    }

}

bool LoginWidget::isValidPassword(QString password){
   QChar c;
   if (password.length() < 6 || password.length() > 16) return false;
   for (int i = 0; i < password.length(); i++){
       c = password.at(i);
       if (!(c.toLatin1() >= 33 && c.toLatin1() <= 126)) return false;
   }
   return true;
}

LoginWidget::~LoginWidget(){
    delete LOGIN_DB;
    delete userLabel;
    delete passLabel;
    delete userLineEdit;
    delete passLineEdit;
    delete loginButton;
    delete cancelButton;
}

