#include "qtablepushbutton.h"
#include "superwidget.h"
#include <QDebug>
#include <QAction>

QTablePushButton::QTablePushButton(const QString &text, int row, int col, SuperWidget *parentWidget, QWidget *parent) : QPushButton(text, parent)
{
    m_row = row;
    m_col = col;

   connect(this, SIGNAL(clicked()),
           this, SLOT(s_interSlot()));
}

void QTablePushButton::s_interSlot() {
    emit sendLoc(m_row, m_col);
}
