#include "superwidget.h"
#include <QVBoxLayout>
#include <QTableWidget>

SuperWidget::SuperWidget(QWidget *parent) : QWidget(parent)
{
    m_mainLayout = new QVBoxLayout();
    m_pending = new QTableWidget();

    m_mainLayout->addWidget(m_pending);
}

