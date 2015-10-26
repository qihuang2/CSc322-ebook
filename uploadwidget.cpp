#include "uploadwidget.h"
#include <QString>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QDebug>

UploadWidget::UploadWidget(QWidget *parent) : QWidget(parent)
{
    m_filename = QString();
    createWidgets();
    createLayouts();
    createActions();
    setLayout(m_mainLayout);
}

void UploadWidget::s_clear() {
    m_filename = QString();
    m_fileLabel->setText(m_filename);
}

void UploadWidget::s_browse() {
    m_filename = (QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(),
                                               tr("Text Files (*.txt *.pdf *.doc *.docx)")));
    m_fileLabel->setText(m_filename);
}

void UploadWidget::createWidgets() {
    m_clearButton = new QPushButton(tr("Clear"));
    m_browseButton = new QPushButton(tr("Browse"));
    m_fileLabel = new QLineEdit(m_filename);
    m_fileLabel->setReadOnly(true);
}

void UploadWidget::createLayouts() {
    m_mainLayout = new QHBoxLayout();
    m_mainLayout->addWidget(m_clearButton);
    m_mainLayout->addWidget(m_browseButton);
    m_mainLayout->addWidget(m_fileLabel);
}

void UploadWidget::createActions() {
    connect(m_clearButton, SIGNAL(clicked()),
            this, SLOT(s_clear()));
    connect(m_browseButton, SIGNAL(clicked()),
            this, SLOT(s_browse()));
}

UploadWidget::~UploadWidget() {}

