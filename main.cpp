#include "mainwindow.h"
#include "welcomedialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bool loginSuccessful = false;
    WelcomeDialog initialDialog(&loginSuccessful);

    if(initialDialog.exec() == QDialog::Accepted) {
        // if dialog was accepted, show main window
        MainWindow w(loginSuccessful);
        w.show();
        return a.exec();
    }else {
        // User exited with logging in
        return EXIT_SUCCESS;
    }
}
