#include "mainwindow.h"
#include "welcomedialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString loginUsername = QString();              // will hold username after executing dialogs
    WelcomeDialog initialDialog(&loginUsername);

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
