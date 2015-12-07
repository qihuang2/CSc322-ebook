#ifndef PROFILEWIDGET_H
#define PROFILEWIDGET_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "registereduser.h"
#include "mainwindow.h"
class DocumentsDB;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QLineEdit;
class QComboBox;
class QTableWidget;
class MainWindow;
class ProfileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProfileWidget(RegisteredUser* user, MainWindow* mw, QWidget *parent = 0);
    ~ProfileWidget();

    void update_History(RegisteredUser* user);

public slots:
    void hideHistory();
    void showHistory();
    void showGift();
    void hideGift();

private:
    void createActions();

    RegisteredUser* m_user;
    MainWindow* m_parent;

    QHBoxLayout* giftLayout;

    QComboBox* m_userList;

    QLineEdit* m_sendCredits;

    QTableWidget*	m_historyText;

    QPushButton*    m_giftButton;
    QPushButton*    m_hideHistory;
    QPushButton*    m_showHistory;
    QPushButton*    m_submitGift;

    QLabel*         m_creditLabel;
};

#endif // PROFILEWIDGET_H
