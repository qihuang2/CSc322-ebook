#include "librarywidget.h"
#include "constants.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include "documentsdb.h"
#include <QDebug>
#include <QtSql>

// Values for books in table
enum {TITLE, AUTHOR, GENRE, RATING};

LibraryWidget::LibraryWidget(QWidget *parent) : QWidget(parent)
{
    m_db = new DocumentsDB();

    createWidgets();
    createLayouts();
    createActions();

    s_refresh();
}

LibraryWidget::~LibraryWidget() {

}

void LibraryWidget::createWidgets() {
    m_refresh = new QPushButton(tr("Refresh"));
    m_refresh->setFixedSize(QSize(100,50));

    m_tableWidget = new QTableWidget(m_db->getNumDocs(), RATING+1);
    m_tableWidget->setHorizontalHeaderLabels(QStringList() << "Title" << "Author" << "Genre" << "Rating");
    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void LibraryWidget::createLayouts() {
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->addWidget(m_tableWidget);
    //m_mainLayout->addWidget(m_refresh);
    setLayout(m_mainLayout);
}

void LibraryWidget::s_refresh() {
    // empty table
    while(m_tableWidget->rowCount() > 0) m_tableWidget->removeRow(0);
    int numDocs = m_db->getNumDocs();

    qDebug() << "Number of documents: " << numDocs;

    // i = 1 and <= numDocs because UID starts at 1
    for(int i = 1; i <= numDocs; ++i) {
        QSqlQuery current = m_db->getDocInfoForUID(i);
        // check if query was successful, otherwise indicates document with uid: i was deleted, do not display
        if(current.first()) {
            int rowIndex = m_tableWidget->rowCount();
            m_tableWidget->insertRow(rowIndex);

            QString title(current.value(MainDB::TITLE).toString());
            QString author(current.value(MainDB::POSTEDBY).toString());
            QString genre(current.value(MainDB::GENRE).toString());
            QString rating(current.value(MainDB::RATING).toString());

            m_tableWidget->setItem(rowIndex, TITLE, new QTableWidgetItem(title, 0));
            m_tableWidget->setItem(rowIndex, AUTHOR, new QTableWidgetItem(author, 0));
            m_tableWidget->setItem(rowIndex, GENRE, new QTableWidgetItem(genre, 0));
            m_tableWidget->setItem(rowIndex, RATING, new QTableWidgetItem(rating, 0));
        }else {
            qDebug() << "Document with id " << i << " doesn't exist.";
        }
    }
}

void LibraryWidget::removeFileWithID(int id) {
    m_db->deleteDocumentWithUID(id);
    QDir().remove(docDir + "/" + QString::number(id) + ".txt");
}

void LibraryWidget::refreshTable() {
    s_refresh();
}

void LibraryWidget::createActions() {
    connect(m_refresh, SIGNAL(clicked()),
            this, SLOT(s_refresh()));
}
