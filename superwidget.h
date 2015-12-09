#ifndef SUPERWIDGET_H
#define SUPERWIDGET_H

#include <QWidget>
#include "superuser.h"
#include "documentsdb.h"
#include "registereduser.h"
class QVBoxLayout;
class QTableWidget;
class QPushButton;
class QSpinBox;
class QString;
class SuperWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SuperWidget(SuperUser* user, QWidget *parent = 0);
private:
    SuperUser*      m_user;
    QVBoxLayout*    m_mainLayout;
    QTableWidget*   m_pending;

    QPushButton*    m_accept;
    QPushButton*    m_decline;
    QPushButton*    m_counter;
    QSpinBox*       m_counterValue;

    QString m_title;
    QString m_username;
    QString m_credits;
    void createWidgets();
    void createLayouts();
    void createActions();

    void populateTable();

signals:

public slots:
    void s_accept();
    void s_decline();
    void s_counter();
};

#endif // SUPERWIDGET_H
