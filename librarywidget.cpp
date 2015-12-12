#include "librarywidget.h"
#include "constants.h"
#include "mainwindow.h"
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include "documentsdb.h"
#include "documentwidget.h"
#include <QDebug>
#include <QTextCursor>
#include <QtSql>
#include <QComboBox>
#include <QLineEdit>

// Values for books in table
enum {UID, TITLE, AUTHOR, GENRE, RATING};

LibraryWidget::LibraryWidget(QString loginUserName,MainWindow* mw, QWidget *parent) : QWidget(parent)
{
    m_parent = mw;
    m_loginName=loginUserName;
    m_db = new DocumentsDB();

    current_row = 0;

    createWidgets();
    createLayouts();
    createActions();

    createRecommend();
    s_refresh();
}

LibraryWidget::~LibraryWidget() {

}

void LibraryWidget::createWidgets() {

    //Create the buttons
    m_hidePreview = new QPushButton("Return to table");
    m_hidePreview->setMaximumSize(QSize(150,50));
    m_openBook = new QPushButton("Open Book");
    m_openBook->setMaximumSize(QSize(150,50));
    m_hideRecommend = new QPushButton("Close Recommendations");
    m_hideRecommend->setMaximumSize(QSize(200,50));
    m_showRecommend = new QPushButton("Open Recommendations");
    m_showRecommend->setMaximumSize(QSize(200,50));
    m_refresh = new QPushButton(tr("Refresh"));
    m_refresh->setFixedSize(QSize(100,50));
    m_startSearch = new QPushButton("Search");
    m_startSearch->setFixedSize(QSize(100,50));

    //Create the labels
    m_recommend = new QLabel("This is our recommendation table of our most viewed documents!\n You can close this table and continue to browse through our library if the recommendations don't interest you.");
    m_title = new QLabel("Title: ");
    m_author = new QLabel("Author: ");
    m_genre = new QLabel("Genre: ");
    m_rating = new QLabel("Rating: ");
    m_booktitle = new QLabel(Title);
    m_bookauthor = new QLabel(Author);
    m_bookgenre = new QLabel(Genre);
    m_bookrating = new QLabel(Rating);

    //Create the Line Edit
    m_search = new QLineEdit();
    m_search->setPlaceholderText("Search");
    m_search->setMaximumSize(QSize(200, 50));

    //Create the Combo Box
    m_searchBy = new QComboBox();
    m_searchBy->setMaximumSize(200, 50);
    m_searchBy->addItem("Select");
    m_searchBy->addItem("Title");
    m_searchBy->addItem("Author");
    m_searchBy->addItem("Genre");

    //Create the Library Table
    m_tableWidget = new QTableWidget(m_db->getNumDocs(), RATING+1);
    m_tableWidget->setColumnHidden(UID,true);
    m_tableWidget->setHorizontalHeaderLabels(QStringList() << "UID" << "Title" << "Author" << "Genre" << "Rating");
    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Create the Preview Table
    m_previewWidget = new QTableWidget();

    //Create the Comment Table
    m_commentWidget = new QTableWidget();
    m_commentWidget->setColumnCount(4);
    m_commentWidget->setColumnHidden(1, true);
    m_commentWidget->setHorizontalHeaderLabels(QStringList() << "User Name" << "Book ID" << "Rating" << "Comment");
    m_commentWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_commentWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Create the Recommendation Table
    m_recommendWidget = new QTableWidget();
    m_recommendWidget->setColumnCount(RATING+1);
    m_recommendWidget->setColumnHidden(UID, true);
    m_recommendWidget->setHorizontalHeaderLabels(QStringList() << "UID" << "Title" << "Author" << "Genre" << "Rating");
    m_recommendWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_recommendWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
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
    m_recommendLayout = new QVBoxLayout();
    m_searchLayout = new QHBoxLayout();

    //Insert widgets into layout
    m_searchLayout->addWidget(m_showRecommend);
    m_searchLayout->addWidget(m_hideRecommend);
    m_searchLayout->addWidget(m_search);
    m_searchLayout->addWidget(m_searchBy);
    m_searchLayout->addWidget(m_startSearch);
    m_searchLayout->setAlignment(Qt::AlignLeft);
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
    m_previewLayout->addWidget(m_previewWidget);
    m_previewLayout->addWidget(m_commentWidget);
    m_previewbuttonLayout->addWidget(m_hidePreview);
    m_previewbuttonLayout->addWidget(m_openBook);
    m_previewLayout->addLayout(m_previewbuttonLayout); //Place the button layout into the Preview Layout
    m_recommendLayout->addWidget(m_recommend);
    m_recommendLayout->addWidget(m_recommendWidget);
    m_tablewithpreviewLayout->addLayout(m_recommendLayout);//Place the layout into the most left side
    m_tablewithpreviewLayout->addWidget(m_tableWidget); //Place the Table Widget into the Preview Layout, will take up middle
    m_tablewithpreviewLayout->addLayout(m_previewLayout); //Place the Preview Layout onto the right side.
    m_mainLayout->addLayout(m_searchLayout);
    m_mainLayout->addLayout(m_tablewithpreviewLayout); //Place the table and preview widgets into the mainlayout
    //m_mainLayout->addWidget(m_refresh);

    //Hide the preview buttons and tables initially
    m_commentWidget->hide();
    m_recommend->hide();
    m_recommendWidget->hide();
    m_hideRecommend->hide();
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

    QSqlQuery current = m_db->getAllDocs();
    
    while(current.next()){
        int rowIndex = m_tableWidget->rowCount();
        m_tableWidget->insertRow(rowIndex);
        
        QString uid(current.value(MainDB::UID).toString());
        QString title(current.value(MainDB::TITLE).toString());
        QString author(current.value(MainDB::POSTEDBY).toString());
        QString genre(genres[current.value(MainDB::GENRE).toInt()]);
        QString rating(current.value(MainDB::RATING).toString());
        
        m_tableWidget->setItem(rowIndex, UID, new QTableWidgetItem(uid, 0));
        m_tableWidget->setItem(rowIndex, TITLE, new QTableWidgetItem(title, 0));
        m_tableWidget->setItem(rowIndex, AUTHOR, new QTableWidgetItem(author, 0));
        m_tableWidget->setItem(rowIndex, GENRE, new QTableWidgetItem(genre, 0));
        m_tableWidget->setItem(rowIndex, RATING, new QTableWidgetItem(rating, 0));
    }
}

//Create recommendation table
void LibraryWidget::createRecommend()
{
    QSqlQuery topFive = m_db->getFiveMostViewed();
    while (topFive.next())
    {
        int rowIndex = m_recommendWidget->rowCount();
        m_recommendWidget->insertRow(rowIndex);

        QString uid(topFive.value(MainDB::UID).toString());
        QString title(topFive.value(MainDB::TITLE).toString());
        QString author(topFive.value(MainDB::POSTEDBY).toString());
        QString genre(topFive.value(MainDB::GENRE).toString());
        QString rating(topFive.value(MainDB::RATING).toString());

        m_recommendWidget->setItem(rowIndex, UID, new QTableWidgetItem(uid, 0));
        m_recommendWidget->setItem(rowIndex, TITLE, new QTableWidgetItem(title, 0));
        m_recommendWidget->setItem(rowIndex, AUTHOR, new QTableWidgetItem(author, 0));
        m_recommendWidget->setItem(rowIndex, GENRE, new QTableWidgetItem(genre, 0));
        m_recommendWidget->setItem(rowIndex, RATING, new QTableWidgetItem(rating, 0));
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
    //connect(m_refresh, SIGNAL(clicked()), this, SLOT(s_refresh()));
    connect(m_tableWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(showPreview()));
    connect(m_tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(selectCell()));
    connect(m_hidePreview, SIGNAL(clicked()), this, SLOT(hidePreview()));
    connect(m_openBook, SIGNAL(clicked()), this, SLOT(s_addHistory()));
    connect(m_openBook, SIGNAL(clicked()), m_parent, SLOT(s_openBook()));
    connect(m_hideRecommend, SIGNAL(clicked()), this, SLOT(hideRecommendations()));
    connect(m_showRecommend, SIGNAL(clicked()), this, SLOT(showRecommendations()));
    connect(m_recommendWidget, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(showPreview()));
    connect(m_recommendWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(selectRecommendation()));
    connect(m_startSearch, SIGNAL(clicked()), this, SLOT(startSearch()));
}

//Show the Preview
void LibraryWidget::showPreview()
{
    m_commentWidget->show();
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
    m_commentWidget->hide();
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
    current_row = row;

    //Get the data in each column for that row
    Title = m_tableWidget->item(row,TITLE)->text();
    Author = m_tableWidget->item(row,AUTHOR)->text();
    Genre = m_tableWidget->item(row,GENRE)->text();
    Rating = m_tableWidget->item(row,RATING)->text();

    QString bookid = m_tableWidget->item(row, UID)->text();
    path = docDir + "/" + bookid + ".txt";

    //Set the Strings
    m_booktitle->setText(Title);
    m_bookauthor->setText(Author);
    m_bookgenre->setText(Genre);
    m_bookrating->setText(Rating);

    //Set up the Summary Table
    int number_ofSummary = m_db->getnumSumm(Title);
    m_previewWidget->clear();
    m_previewWidget->setColumnCount(1);
    m_previewWidget->setRowCount(number_ofSummary+2);
    m_previewWidget->setHorizontalHeaderLabels(QStringList() << "Summary");
    m_previewWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_previewWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Get the summary
    QString current = m_db->getSummary(Title);
    for(int i = 1; i <= number_ofSummary; ++i)
    {
        m_previewWidget->setRowHidden(0, true);
        m_previewWidget->setRowHidden(1, true);
        m_previewWidget->verticalHeader()->setVisible(false);
        m_previewWidget->setItem(i, 1, new QTableWidgetItem(current));
        m_previewWidget->update();
    }

    //Set up the Comment Table
    m_commentWidget->setRowCount(0);

    //Get the Comment for Comment Table
    QSqlQuery getComment = m_db->getCommentsOfDocWithUID(bookid.toInt());

    while(getComment.next())
    {
        int rowIndex = m_commentWidget->rowCount();
         m_commentWidget->insertRow(rowIndex);

        QString username(getComment.value(0).toString());
        QString book_id(getComment.value(1).toString());
        QString rating(getComment.value(2).toString());
        QString comment(getComment.value(3).toString());

        m_commentWidget->setItem(rowIndex, 0, new QTableWidgetItem(username, 0));
        m_commentWidget->setItem(rowIndex, 1, new QTableWidgetItem(book_id, 0));
        m_commentWidget->setItem(rowIndex, 2, new QTableWidgetItem(rating, 0));
        m_commentWidget->setItem(rowIndex, 3, new QTableWidgetItem(comment, 0));
    }
}

//Hide recommendations
void LibraryWidget::hideRecommendations()
{
    m_search->show();
    m_searchBy->show();
    m_startSearch->show();
    m_tableWidget->show();
    m_recommend->hide();
    m_recommendWidget->hide();
    m_hideRecommend->hide();
    m_showRecommend->show();
}

//Show recommendations
void LibraryWidget::showRecommendations()
{
    m_search->hide();
    m_searchBy->hide();
    m_startSearch->hide();
    m_tableWidget->hide();
    m_recommend->show();
    m_recommendWidget->show();
    m_hideRecommend->show();
    m_showRecommend->hide();
}

//select a row  in recommendations and display details in preview
void LibraryWidget::selectRecommendation()
{
    //Get the row
    QModelIndex currentIndex = m_recommendWidget->currentIndex();
    int row = currentIndex.row();
    current_row = row;

    //Get the data in each column for that row
    Title = m_recommendWidget->item(row,TITLE)->text();
    Author = m_recommendWidget->item(row,AUTHOR)->text();
    Genre = m_recommendWidget->item(row,GENRE)->text();
    Rating = m_recommendWidget->item(row,RATING)->text();

    QString bookid = m_tableWidget->item(row, UID)->text();
    path = docDir + "/" + bookid + ".txt";

    //Set the Strings
    m_booktitle->setText(Title);
    m_bookauthor->setText(Author);
    m_bookgenre->setText(Genre);
    m_bookrating->setText(Rating);

    //Set up the Summary Table
    number_ofSummary = m_db->getnumSumm(Title);
    m_previewWidget->clear();
    m_previewWidget->setColumnCount(1);
    m_previewWidget->setRowCount(number_ofSummary+2);
    m_previewWidget->setHorizontalHeaderLabels(QStringList() << "Summary");
    m_previewWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_previewWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //Get the summary
    QString current = m_db->getSummary(Title);
    for(int i = 1; i <= number_ofSummary; ++i)
    {
        m_previewWidget->setRowHidden(0, true);
        m_previewWidget->setRowHidden(1, true);
        m_previewWidget->verticalHeader()->setVisible(false);
        m_previewWidget->setItem(i, 1, new QTableWidgetItem(current));
        m_previewWidget->update();
    }

    //Set up the Comment Table
    m_commentWidget->setRowCount(0);

    //Get the Comment for Comment Table
    QSqlQuery getComment = m_db->getCommentsOfDocWithUID(bookid.toInt());

    while(getComment.next())
    {
        int rowIndex = m_commentWidget->rowCount();
         m_commentWidget->insertRow(rowIndex);

        QString username(getComment.value(0).toString());
        QString book_id(getComment.value(1).toString());
        QString rating(getComment.value(2).toString());
        QString comment(getComment.value(3).toString());

        m_commentWidget->setItem(rowIndex, 0, new QTableWidgetItem(username, 0));
        m_commentWidget->setItem(rowIndex, 1, new QTableWidgetItem(book_id, 0));
        m_commentWidget->setItem(rowIndex, 2, new QTableWidgetItem(rating, 0));
        m_commentWidget->setItem(rowIndex, 3, new QTableWidgetItem(comment, 0));
    }
}

//Get the current row
//Change this to get book id
int LibraryWidget::getRow()
{
    return current_row+1;
}

//Return the path
QString LibraryWidget::getPath()
{
    return path;
}

//Add to history
void LibraryWidget::s_addHistory()
{
    HistoryDB *h =new HistoryDB();
    h->addHistory(m_loginName,m_booktitle->text(),m_bookauthor->text());
}

//Search the table
void LibraryWidget::startSearch()
{
    //Empty the table
    m_tableWidget->setRowCount(0);

    //Get the Search and Column
    QString text = m_search->text();
    int column = m_searchBy->currentIndex();

    if(column == TITLE || column == AUTHOR || column == GENRE)
    {
        QSqlQuery matched = m_db->matchSearch(text, column);
        while (matched.next())
        {
            //Insert into the table
            int rowIndex = m_tableWidget->rowCount();
            m_tableWidget->insertRow(rowIndex);

            QString uid(matched.value(MainDB::UID).toString());
            QString title(matched.value(MainDB::TITLE).toString());
            QString author(matched.value(MainDB::POSTEDBY).toString());
            QString genre(matched.value(MainDB::GENRE).toString());
            QString rating(matched.value(MainDB::RATING).toString());

            m_tableWidget->setItem(rowIndex, UID, new QTableWidgetItem(uid, 0));
            m_tableWidget->setItem(rowIndex, TITLE, new QTableWidgetItem(title, 0));
            m_tableWidget->setItem(rowIndex, AUTHOR, new QTableWidgetItem(author, 0));
            m_tableWidget->setItem(rowIndex, GENRE, new QTableWidgetItem(genre, 0));
            m_tableWidget->setItem(rowIndex, RATING, new QTableWidgetItem(rating, 0));
        }
    }
    else
        s_refresh();
}
