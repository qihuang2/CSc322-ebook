#include "mainwindow.h"
#include "welcomedialog.h"
#include "constants.h"
#include <QApplication>
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{   
    QApplication a(argc, argv);
    QString loginUsername = QString();              // will hold username after executing dialogs

    // if application directory doesn't already exist, create it
    if(!QDir(appDir).exists()) {
        qDebug() << "Application directory doesn't exist.";
        qDebug() << "Creating directory " << appDir;
        QDir().mkdir(appDir); // main directory
        QDir().mkdir(docDir); // folder to hold documents
    }

   //Visiter = 0, User = 1, or Superuser = 2; Change to Enums? -> yup
    int userType = 0;

    WelcomeDialog initialDialog(&loginUsername, &userType);

    if(initialDialog.exec() == QDialog::Accepted) {
        // if dialog was accepted, show main window
        MainWindow w(loginUsername);
        w.show();
        return a.exec();
    }else {
        // User exited with logging in
        return EXIT_SUCCESS;
    }
}
