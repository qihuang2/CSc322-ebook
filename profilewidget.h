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

public slots:
    void update_History();

private:
    QTableWidget*	m_historyText;
    QPushButton*    m_giftButton;
};

#endif // PROFILEWIDGET_H
