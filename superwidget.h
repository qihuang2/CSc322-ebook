#ifndef SUPERWIDGET_H
#define SUPERWIDGET_H

#include <QWidget>
#include "superuser.h"
#include "documentsdb.h"
#include "mainwindow.h"

class QVBoxLayout;
class QTableWidget;
class QPushButton;
class QSpinBox;
class QString;
class SuperWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SuperWidget(SuperUser* user = 0, QWidget *parent = 0);

    void populateTable();
    void clearTable();
private:
    SuperUser*      m_user;
    QVBoxLayout*    m_mainLayout;
    QTableWidget*   m_pending;

    QString m_title;
    QString m_username;
    QString m_credits;
    QString m_uid;

    void createWidgets();
    void createLayouts();
    void createActions();

    void accept(int row);
    void decline(int row);
    void counter(int row);

    int m_id;
    int m_giveCredit;

signals:

public slots:
    void s_buttonClicked(int row, int col);
};

#endif // SUPERWIDGET_H
