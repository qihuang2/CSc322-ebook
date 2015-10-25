#include "mainwindow.h"
#include "ui_mainwindow.h"

const int COLS = 2;

tableWindow::tableWindow(QWidget *parent) : QWidget(parent)
{
    mainTable  = new QSplitter(this);
    table = new QTableWidget(0, COLS);
    QHeaderView *header = new QHeaderView(Qt::Horizontal,table);
    table->setHorizontalHeader(header);
    table->setHorizontalHeaderLabels(QStringList() << "Title" << "Genre" );
    table->setAlternatingRowColors(1);
    table->setEditTriggers (QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    mainTable->addWidget(table);
    setMinimumSize(400,400);
}
