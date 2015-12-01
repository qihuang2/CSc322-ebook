#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>

class QTableWidget;
class QVBoxLayout;
class QPushButton;
class DocumentsDB;

class LibraryWidget : public QWidget
{
    Q_OBJECT
public:
    LibraryWidget(QWidget *parent = 0);
    ~LibraryWidget();

    void refreshTable();

private:
    QVBoxLayout*        m_mainLayout;
    QPushButton*        m_refresh;
    QTableWidget*       m_tableWidget;
    DocumentsDB*        m_db;

    void populateTable();

    void createWidgets();
    void createLayouts();
    void createActions();

    void removeFileWithID(int id);

public slots:
    void s_refresh();
};

#endif // LIBRARYWIDGET_H
