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

    QWidget* widget = new QWidget();

    m_hidePreview = new QPushButton("Return to table");
    m_hidePreview->setMaximumSize(QSize(150,50));
    m_openBook = new QPushButton("Open Book");
    m_openBook->setMaximumSize(QSize(150,50));

    m_title = new QLabel("Title: ");
    m_author = new QLabel("Author: ");
    m_genre = new QLabel("Genre: ");
    m_rating = new QLabel("Rating: ");
    m_booktitle = new QLabel(Title);
    m_bookauthor = new QLabel(Author);
    m_bookgenre = new QLabel(Genre);
    m_bookrating = new QLabel(Rating);


    m_previewText = new QTextEdit(widget);

    m_refresh = new QPushButton(tr("Refresh"));
    m_refresh->setFixedSize(QSize(100,50));

    m_tableWidget = new QTableWidget(m_db->getNumDocs(), RATING+1);
    m_tableWidget->setHorizontalHeaderLabels(QStringList() << "Title" << "Author" << "Genre" << "Rating");
    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_previewWidget = new QTableWidget(); //Change this later to getRateDocs
    m_previewWidget->setHorizontalHeaderLabels(QStringList() << "Ratings");
    m_previewWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_previewWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void LibraryWidget::createLayouts() {

    //Create the layout
    m_mainLayout = new QVBoxLayout();
    m_tablewithpreviewLayout = new QHBoxLayout();
    m_titleLayout = new QHBoxLayout();
    m_authorLayout = new QHBoxLayout();
    m_genreLayout = new QHBoxLayout();
    m_ratingLayout = new QHBoxLayout();
    m_previewLayout = new QVBoxLayout();
    m_previewbuttonLayout = new QHBoxLayout();

    m_previewLayout->addWidget(m_previewText); //Place textbox on top of preview layout
    m_titleLayout->addWidget(m_title);
    m_titleLayout->addWidget(m_booktitle);
    m_previewLayout->addLayout(m_titleLayout); //Place title into preview layout
    m_authorLayout->addWidget(m_author);
    m_authorLayout->addWidget(m_bookauthor);
    m_previewLayout->addLayout(m_authorLayout); //author into preview layout
    m_genreLayout->addWidget(m_genre);
    m_genreLayout->addWidget(m_bookgenre);
    m_previewLayout->addLayout(m_genreLayout); // Place genre into preview layout
    m_ratingLayout->addWidget(m_rating);
    m_ratingLayout->addWidget(m_bookrating);
    m_previewLayout->addLayout(m_ratingLayout); //Place rating into preview layout
    m_previewLayout->addWidget(m_previewWidget); //reviews + ratings
    m_previewbuttonLayout->addWidget(m_hidePreview);
    m_previewbuttonLayout->addWidget(m_openBook);
    m_previewLayout->addLayout(m_previewbuttonLayout); //Place the button layout into the Preview Layout
    m_tablewithpreviewLayout->addWidget(m_tableWidget); //Place the Table Widget into the Preview Layout, will take up left side
    m_tablewithpreviewLayout->addLayout(m_previewLayout); //Place the Preview Layout onto the right side.
    m_mainLayout->addLayout(m_tablewithpreviewLayout); //Place the table and preview widgets into the mainlayout
    //m_mainLayout->addWidget(m_refresh);

    //Hide the preview buttons and tables initially
    m_previewText->hide();
    m_title->hide();
    m_author->hide();
    m_genre->hide();
    m_rating->hide();
    m_previewWidget->hide();
    m_hidePreview->hide();
    m_openBook->hide();
    m_booktitle->hide();
    m_bookauthor->hide();
    m_bookgenre->hide();
    m_bookrating->hide();

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

//Refresh the table
void LibraryWidget::refreshTable() {
    s_refresh();
}

//Triggers for each button or (double) click on table
void LibraryWidget::createActions() {
    connect(m_refresh, SIGNAL(clicked()), this, SLOT(s_refresh()));
    connect(m_tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(showPreview()));
    connect(m_tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(selectCell()));
    connect(m_hidePreview, SIGNAL(clicked()), this, SLOT(hidePreview()));
}

//Show the Preview
void LibraryWidget::showPreview()
{
    m_previewText->show();
    m_title->show();
    m_author->show();
    m_genre->show();
    m_previewWidget->show();
    m_hidePreview->show();
    m_openBook->show();
    m_booktitle->show();
    m_bookauthor->show();
    m_bookgenre->show();
    m_rating->show();
    m_bookrating->show();
}

//Hide the Preview
void LibraryWidget::hidePreview()
{
    m_previewText->hide();
    m_title->hide();
    m_author->hide();
    m_genre->hide();
    m_previewWidget->hide();
    m_hidePreview->hide();
    m_openBook->hide();
    m_booktitle->hide();
    m_bookauthor->hide();
    m_bookgenre->hide();
    m_rating->hide();
    m_bookrating->hide();
}

//Get data of selected row and display in Preview
void LibraryWidget::selectCell()
{
    //Get the row
    QModelIndex currentIndex = m_tableWidget->currentIndex();
    int row = currentIndex.row();

    //Get the data in each column for that row
    Title = m_tableWidget->item(row,0)->text();
    Author = m_tableWidget->item(row,1)->text();
    Genre = m_tableWidget->item(row,2)->text();
    Rating = m_tableWidget->item(row,3)->text();

    //Set the Strings
    m_booktitle->setText(Title);
    m_bookauthor->setText(Author);
    m_bookgenre->setText(Genre);
    m_bookrating->setText(Rating);
}
