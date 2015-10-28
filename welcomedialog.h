#ifndef WELCOMEDIALOG_H
#define WELCOMEDIALOG_H

#include <QDialog>

class QVBoxLayout;
class LoginWidget;
class RegisterWidget;
class LoginDB;

class WelcomeDialog : public QDialog
{
    Q_OBJECT
public:
    WelcomeDialog(QString* username, int* userType);

private:
    QString*        m_username;     /* Pointer to variable holding username. */
    int*            m_userType;
    QVBoxLayout*    m_mainLayout;

    LoginDB*        m_loginDB;

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
