#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QWidget;
class QLabel;
class QVBoxLayout;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString loginUsername);
    ~MainWindow();

private:
    QString         m_username;         /* Flag indicating whether or not user is logged in. */
    QWidget*        m_centralWidget;    /* Main widget. */
    QVBoxLayout*    m_mainLayout;       /* Main vertical layout. */
    QLabel*         m_loginLabel;       /* Displays login status. */
    QTabWidget*     m_tabWidget;        /* Central widget to hold Library and Upload tabs. */
    QPushButton*    m_exitButton;

    void createWidgets();
    void createLayouts();
    void createActions();
};

#endif // MAINWINDOW_H
