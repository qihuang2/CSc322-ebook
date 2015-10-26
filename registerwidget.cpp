#include "registerwidget.h"

RegisterWidget::RegisterWidget(QWidget *parent) : QDialog(parent)
{
    setFixedSize(320, 250);
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("Register");

    LOGIN_DB = new LoginDB();

    userLabel = new QLabel("Username:");
    passLabel = new QLabel("Password:");
    confirmLabel = new QLabel("Confrm:");
    userLineEdit = new QLineEdit();
    userLineEdit->setMaxLength(12);
    passLineEdit = new QLineEdit();
    passLineEdit->setMaxLength(14);
    passLineEdit->setEchoMode(QLineEdit::Password);
    confirmLineEdit = new QLineEdit();
    confirmLineEdit->setMaxLength(14);
    confirmLineEdit->setEchoMode(QLineEdit::Password);
    registerButton = new QPushButton("Register");
    cancelButton = new QPushButton("Cancel");

    QVBoxLayout* vbox = new QVBoxLayout(this);
    QHBoxLayout* hbox1 = new QHBoxLayout();
    QHBoxLayout* hbox2 = new QHBoxLayout();
    QHBoxLayout* hbox3 = new QHBoxLayout();
    QHBoxLayout* hbox4 = new QHBoxLayout();

    hbox1->addWidget(userLabel, 1);
    hbox1->addWidget(userLineEdit, 2);
    hbox2->addWidget(passLabel, 1);
    hbox2->addWidget(passLineEdit,2);
    hbox3->addWidget(confirmLabel,1);
    hbox3->addWidget(confirmLineEdit,2);
    hbox4->addWidget(registerButton, 1);
    hbox4->addWidget(cancelButton, 1);

    vbox->addSpacing(1);
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    vbox->addLayout(hbox3);
    vbox->addLayout(hbox4);

    connect(cancelButton, SIGNAL(clicked()), this, SLOT(onCancel()));
    connect(registerButton, SIGNAL(clicked()), this, SLOT(onRegister()));
}

void RegisterWidget::onCancel()
{
    LOGIN_DB->closeDB();
    this->destroy();
}

void RegisterWidget::reject()
{
    onCancel();
}

void RegisterWidget::onRegister(){
    QString username = userLineEdit->text();
    QString password = passLineEdit->text();
    QString confirm = confirmLineEdit->text();
    if (LOGIN_DB->userExists(username)){
        QMessageBox::information(this, tr("Warning"), "Username already taken");
    }else if (!passwordsMatch(password,confirm)) {
        QMessageBox::information(this, tr("Warning"), "Passwords don't match.");
    }else if (!isValidPassword(password)) {
        QMessageBox::information(this, tr("Warning"), "Passwords must be 6-14 characters.");
    }else {
        // REGISTER
        LOGIN_DB->addUser(username,password,"1");
        LOGIN_DB->closeDB();
        this->destroy();
    }
}

bool RegisterWidget::isValidPassword(QString password){
   QChar c;
   if (password.length() < 6 || password.length() > 16) return false;
   for (int i = 0; i < password.length(); i++){
       c = password.at(i);
       if (!(c.toLatin1() >= 33 && c.toLatin1() <= 126)) return false;
   }
   return true;
}

bool RegisterWidget:: passwordsMatch(QString first, QString second){
    return (first.compare(second) == 0);
}

RegisterWidget::~RegisterWidget(){

}
