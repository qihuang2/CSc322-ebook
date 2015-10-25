#include "mainwindow.h"
#include "ui_mainwindow.h"

const int COLS = 2;

uploadWindow::uploadWindow(QWidget *parent) : QWidget(parent)
{
    mainUpload  = new QSplitter(this);

    //mainUpload->addWidget(table);
}

