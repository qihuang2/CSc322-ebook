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

    QString m_title;
    QString m_username;
    QString m_credits;

    void createWidgets();
    void createLayouts();
    void createActions();

    void populateTable();
    void clearTable();

    void accept(int row);
    void decline(int row);
    void counter(int row);

signals:

public slots:
    void s_buttonClicked(int row, int col);
};

#endif // SUPERWIDGET_H
