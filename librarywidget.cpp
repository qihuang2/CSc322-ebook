#include "librarywidget.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>

// Values for books in table
enum {TITLE, AUTHOR, GENRE, RATING};

LibraryWidget::LibraryWidget(QWidget *parent) : QWidget(parent)
{
    m_numBooks = 10;    // this will be set to the number of books in the library
    m_mainLayout = new QVBoxLayout();
    m_tableWidget = new QTableWidget(m_numBooks, RATING+1);
    // Set titles for columns
    m_tableWidget->setHorizontalHeaderLabels(QStringList() << "Title" << "Author" << "Genre" << "Rating");
    // Makes column labels stretchable
    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // Make cells read only
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_mainLayout->addWidget(m_tableWidget);
    setLayout(m_mainLayout);
}
