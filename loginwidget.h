#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QDialog>
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QLineEdit;
class QPushButton;
class QMessageBox;
class QString;
class LoginDB;

class LoginWidget : public QDialog
{
    Q_OBJECT
public:
    explicit LoginWidget(LoginDB* db, QString* username, int* userType,QWidget* parent = 0);
    ~LoginWidget();

private slots:
    void s_onLogin();

private:
    LoginDB* m_loginDB;
    QString* m_username;
    int* m_userType;
    QLabel*         m_userLabel;
    QLabel*         m_passLabel;
    QLineEdit*      m_userLineEdit;
    QLineEdit*      m_passLineEdit;
    QPushButton*    m_loginButton;
    QPushButton*    m_cancelButton;

    void createWidgets();
    void createActions();
    void createLayouts();

    //check if it's a valid password and username
    bool isValidPassword(QString password);
    bool isValidUsername(QString username);
};

#endif // LOGINWIDGET_H
