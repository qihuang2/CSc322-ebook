#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include "logindb.h"

class RegisterWidget : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterWidget(QWidget *parent = 0);
    ~RegisterWidget();

private slots:
    void onRegister();
    void onCancel();
private:
    bool isValidPassword(QString password);
    bool passwordsMatch(QString first, QString second);
    
    LoginDB *LOGIN_DB;

    void reject();

    QLabel* userLabel;
    QLabel* passLabel;
    QLabel* confirmLabel;
    QLineEdit* userLineEdit;
    QLineEdit* passLineEdit;
    QLineEdit* confirmLineEdit;
    QPushButton* registerButton;
    QPushButton* cancelButton;
};

#endif // REGISTERWIDGET_H
