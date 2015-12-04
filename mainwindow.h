#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "documentwidget.h"
#include "librarywidget.h"
class QWidget;
class QLabel;
class QVBoxLayout;
class QPushButton;
class BaseUser;
class DocumentsDB;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString loginUsername, int userType);
    ~MainWindow();

private:
    BaseUser*       m_user;             //Keeps track of user info
    DocumentsDB*    m_docDB;            //DB for uploaded documents
    QWidget*        m_centralWidget;    /* Main widget. */
    QVBoxLayout*    m_mainLayout;       /* Main vertical layout. */
    QLabel*         m_loginLabel;       /* Displays login status. */
    QTabWidget*     m_tabWidget;        /* Central widget to hold Library and Upload tabs. */
    QPushButton*    m_exitButton;
    DocumentWidget* doc;
    LibraryWidget* lib;

    void createWidgets();
    void createLayouts();
    void createActions();

private slots:
    void s_refreshTable(int current);
    void s_openBook();
};

#endif // MAINWINDOW_H
