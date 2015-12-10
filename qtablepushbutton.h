#ifndef QTABLEPUSHBUTTON_H
#define QTABLEPUSHBUTTON_H

#include <QPushButton>

class SuperWidget;

class QTablePushButton : public QPushButton
{
    Q_OBJECT

public:
    QTablePushButton(const QString & text, int row, int col, SuperWidget* parentWidget, QWidget * parent = 0);

private:
    int m_row;
    int m_col;

signals:
    void sendLoc(int row, int col);

private slots:
    void s_interSlot();
};

#endif // QTABLEPUSHBUTTON_H
