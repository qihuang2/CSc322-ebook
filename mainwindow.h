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
    MainWindow(bool loginStatus);
    ~MainWindow();

private:
    QWidget*        m_centralWidget;
    // Main vertical layout
    QVBoxLayout*    m_mainLayout;
    // Displays login status
    QLabel*         m_loginLabel;
    // Central widget to hold Library and Upload tabs
    QTabWidget*     m_tabWidget;
    bool m_loggedIn;

    QPushButton*    m_exitButton;

    void createWidgets();
    void createLayouts();
    void createActions();
};

#endif // MAINWINDOW_H
