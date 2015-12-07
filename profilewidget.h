#ifndef PROFILEWIDGET_H
#define PROFILEWIDGET_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "registereduser.h"

class DocumentsDB;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QLineEdit;
class QComboBox;
class QTableWidget;
class ProfileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProfileWidget(RegisteredUser* user, QWidget *parent = 0);
    ~ProfileWidget();

    void update_History(RegisteredUser* user);

public slots:
    void hideHistory();
    void showHistory();
    void showGift();
    void hideGift();

private:
    void createActions();

    QHBoxLayout* giftLayout;

    QComboBox* m_userList;

    QLineEdit* m_sendCredits;

    QTableWidget*	m_historyText;

    QPushButton*    m_giftButton;
    QPushButton*    m_hideHistory;
    QPushButton*    m_showHistory;
    QPushButton*    m_submitGift;
};

#endif // PROFILEWIDGET_H
