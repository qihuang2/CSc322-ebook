#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QDialog>
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QLineEdit;
class QPushButton;
class QMessageBox;
class LoginDB;

class RegisterWidget : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterWidget(LoginDB* db, QString* username, int* userType, QWidget* parent = 0);
    ~RegisterWidget();

private slots:
    void s_onRegister();
private:
    bool isValidPassword(QString password); //passwords can't have the characters ' and "
    bool passwordsMatch(QString first, QString second);  //Ask users to confirm password
    bool isValidUsername(QString username);         //Usernames can only be letters and numbers

    void createWidgets();
    void createLayouts();
    void createActions();
    
    LoginDB* m_loginDB;
    QString* m_username;
    int* m_userType;  // registered = 1 , super = 2

    QLabel* m_userLabel;
    QLabel* m_passLabel;
    QLabel* m_confirmLabel;
    QLineEdit* m_userLineEdit;
    QLineEdit* m_passLineEdit;
    QLineEdit* m_confirmLineEdit;
    QPushButton* m_registerButton;
    QPushButton* m_cancelButton;
};

#endif // REGISTERWIDGET_H
