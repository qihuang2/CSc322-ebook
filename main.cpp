#include "mainwindow.h"
#include "welcomedialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString loginUsername = QString();              // will hold username after executing dialogs

   //Visiter = 0, User = 1, or Superuser = 2; Change to Enums?
    int userType = 0;

    WelcomeDialog initialDialog(&loginUsername, &userType);

    if(initialDialog.exec() == QDialog::Accepted) {
        // if dialog was accepted, show main window
        MainWindow w(loginUsername, userType);
        w.show();
        return a.exec();
    }else {
        // User exited with logging in
        return EXIT_SUCCESS;
    }
}
