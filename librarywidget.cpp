#include "librarywidget.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include "documentsdb.h"
#include <QDebug>
#include <QtSql>

// Values for books in table
enum {TITLE, AUTHOR, GENRE, RATING};

LibraryWidget::LibraryWidget(QWidget *parent) : QWidget(parent)
{
    m_db = new DocumentsDB();


    m_numBooks = m_db->getNumDocs();    // this will be set to the number of books in the library

    createWidgets();
    createLayouts();
    createActions();
}

LibraryWidget::~LibraryWidget() {

}

void LibraryWidget::populateTable() {

}

void LibraryWidget::createWidgets() {
    m_tableWidget = new QTableWidget(m_numBooks, RATING+1);
    // Set titles for columns
    m_tableWidget->setHorizontalHeaderLabels(QStringList() << "Title" << "Author" << "Genre" << "Rating");
    // Makes column labels stretchable
    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // Make cells read only
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void LibraryWidget::createLayouts() {
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->addWidget(m_tableWidget);
    setLayout(m_mainLayout);
}

void LibraryWidget::createActions() {

}

