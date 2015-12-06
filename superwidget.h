#ifndef SUPERWIDGET_H
#define SUPERWIDGET_H

#include <QWidget>

class QVBoxLayout;
class QTableWidget;

class SuperWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SuperWidget(QWidget *parent = 0);
private:
    QVBoxLayout* m_mainLayout;
    QTableWidget* m_pending;

signals:

public slots:
};

#endif // SUPERWIDGET_H
