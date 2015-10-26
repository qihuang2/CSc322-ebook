#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include "logindb.h"

class LoginWidget : public QDialog
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();

private slots:
    void onLogin();
    void onCancel();
private:
    bool isValidPassword(QString password);

    LoginDB *LOGIN_DB;

    void reject();

    QLabel*         userLabel;
    QLabel*         passLabel;
    QLineEdit*      userLineEdit;
    QLineEdit*      passLineEdit;
    QPushButton*    loginButton;
    QPushButton*    cancelButton;
};

#endif // LOGINWIDGET_H
