#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>

class QTableWidget;
class QVBoxLayout;
class DocumentsDB;

class LibraryWidget : public QWidget
{
    Q_OBJECT
public:
    LibraryWidget(QWidget *parent = 0);
    ~LibraryWidget();

private:
    QVBoxLayout*        m_mainLayout;
    QTableWidget*       m_tableWidget;
    DocumentsDB*        m_db;

    // Number of books in library to be used as number of rows
    int                 m_numBooks;

    void populateTable();

    void createWidgets();
    void createLayouts();
    void createActions();
};

#endif // LIBRARYWIDGET_H
