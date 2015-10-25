#include "mainwindow.h"
#include <QApplication>
#include <logindb.h>

int main(int argc, char *argv[])
{

    // init variables and application font
    QString	      program = argv[0];
    QApplication  app(argc, argv);

    // invoke  MainWindow constructor
    MainWindow window(program);
    // display MainWindow
    window.show();
    return app.exec();
}
