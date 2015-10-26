#ifndef WELCOMEDIALOG_H
#define WELCOMEDIALOG_H

#include <QDialog>

class QVBoxLayout;
class LoginWidget;
class RegisterWidget;

class WelcomeDialog : public QDialog
{
    Q_OBJECT
public:
    WelcomeDialog(bool* userLoggedIn);

private:
    // A pointer to a bool which will be set to true if the user has logged in
    // Will be used to construct MainWindow from within main.cpp
    bool*           m_loginSuccessful;
    QVBoxLayout*    m_mainLayout;

    // widgets
    LoginWidget*    m_loginWidget;
    RegisterWidget* m_registerWidget;

    // buttons
    QPushButton*    m_login;
    QPushButton*    m_register;
    QPushButton*    m_visit;
    QPushButton*    m_exit;


    // Create and configure widgets
    void createWidgets();
    // Add widgets to layout
    void createLayouts();
    // Connect widget actions to slots
    void createActions();

private slots:
    void s_login();
    void s_register();
    void s_visit();
    void s_exit();
};

#endif // WELCOMEDIALOG_H
