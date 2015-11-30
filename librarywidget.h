#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>

class QTableWidget;
class QVBoxLayout;

class LibraryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LibraryWidget(QWidget *parent = 0);

private:
    QVBoxLayout*        m_mainLayout;
    QTableWidget*       m_tableWidget;

    // Number of books in library to be used as number of rows
    int                 m_numBooks;

    void createWidgets();
    void createLayouts();
    void createActions();
};

#endif // LIBRARYWIDGET_H
