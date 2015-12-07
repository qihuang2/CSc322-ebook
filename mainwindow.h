#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "documentwidget.h"
#include "librarywidget.h"
#include "historydb.h"
#include <QTextEdit>
#include <QTableWidget>
#include <QHeaderView>
#include "profilewidget.h"
#include "uploadwidget.h"

class QWidget;
class SuperWidget;
class QLabel;
class QVBoxLayout;
class QPushButton;
class BaseUser;
class DocumentsDB;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(BaseUser* user);
    ~MainWindow();

private:
    BaseUser*       m_user;             //Keeps track of user info
    DocumentsDB*    m_docDB;            //DB for uploaded documents
    QWidget*        m_centralWidget;    /* Main widget. */
    QVBoxLayout*    m_mainLayout;       /* Main vertical layout. */
    QLabel*         m_loginLabel;       /* Displays login status. */
    QTabWidget*     m_tabWidget;        /* Central widget to hold Library and Upload tabs. */

    QPushButton*    m_exitButton;

    QLabel* m_username;
    QLabel* m_usercredits;

    QString m_name;
    QString m_credit;

    void createWidgets();
    void createLayouts();
    void createActions();

private slots:
    void s_refreshTable(int current);
    void s_openBook();
    void s_updateHistory();
    void s_updateCredit();
};

#endif // MAINWINDOW_H
