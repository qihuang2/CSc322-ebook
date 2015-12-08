#include "mainwindow.h"
#include "welcomedialog.h"
#include "constants.h"
#include "superuser.h"
#include "maindb.h"
#include <QApplication>
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{   
    QApplication a(argc, argv);

    // if application directory doesn't already exist, create it
    if(!QDir(appDir).exists()) {
        qDebug() << "Application directory doesn't exist.";
        qDebug() << "Creating directory " << appDir;
        QDir().mkdir(appDir); // main directory
        QDir().mkdir(docDir); // folder to hold documents
    }

    QString loginUsername = QString();              // will hold username after executing dialogs
    WelcomeDialog initialDialog(&loginUsername);

    if(initialDialog.exec() == QDialog::Accepted) {
        // if dialog was accepted, show main window
        MainDB db;
        BaseUser* user;
        QSqlQuery userQuery = db.getAccount(loginUsername);
        userQuery.first();     //go to valid entry
        if(userQuery.value(2) == BaseUser::VISITING) {
            user = new BaseUser();
        }else if(userQuery.value(2) == BaseUser::REGISTERED) {
            user = new RegisteredUser(loginUsername);
        }else{
            user = new SuperUser(loginUsername);
        }
        MainWindow w(user);
        w.show();
        return a.exec();
    }else {
        // User exited with logging in
        return EXIT_SUCCESS;
    }
}
