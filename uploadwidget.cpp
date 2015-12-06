#include "uploadwidget.h"
#include <QLabel>
#include <QString>
#include <QBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QDebug>
#include "constants.h"
#include "documentsdb.h"
#include "mainwindow.h"

UploadWidget::UploadWidget(QWidget *parent) : QWidget(parent)
{
    m_db = new DocumentsDB();

    createWidgets();
    createLayouts();
    createActions();
    setLayout(m_mainLayout);
}

void UploadWidget::s_clear() {
    m_fileLabel->setText(QString());
}

void UploadWidget::s_browse() {
    m_fileLabel->setText((QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(),
                                                       tr("Text Files (*.txt)"))));
}

void UploadWidget::createWidgets() {
    m_titleField = new QLineEdit();
    m_authorField = new QLineEdit();
    m_genreField = new QComboBox();

    m_clearButton = new QPushButton(tr("Clear"));
    m_browseButton = new QPushButton(tr("Browse"));
    m_fileLabel = new QLineEdit();
    m_fileLabel->setReadOnly(true);

    m_uploadButton = new QPushButton(tr("Upload"));
    m_uploadButton->setFixedSize(QSize(100,50));
}

void UploadWidget::createLayouts() {
    m_mainLayout = new QVBoxLayout();

    QHBoxLayout* titleLayout = new QHBoxLayout();
    QLabel* titleLabel = new QLabel(tr("Title\t\t"));
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(m_titleField);

    QHBoxLayout* authorLayout = new QHBoxLayout();
    QLabel* authorLabel = new QLabel(tr("Author\t\t"));
    authorLayout->addWidget(authorLabel);
    authorLayout->addWidget(m_authorField);

    QHBoxLayout* genreLayout = new QHBoxLayout();
    QLabel* genreLabel = new QLabel(tr("Genre\t\t"));
    genreLayout->addWidget(genreLabel);
    genreLayout->addWidget(m_genreField);

    m_mainLayout->addLayout(titleLayout);
    m_mainLayout->addLayout(authorLayout);
    m_mainLayout->addLayout(genreLayout);

    m_uploadLayout = new QHBoxLayout();
    m_uploadLayout->addWidget(m_clearButton);
    m_uploadLayout->addWidget(m_browseButton);
    m_uploadLayout->addWidget(m_fileLabel);

    m_mainLayout->addLayout(m_uploadLayout);
    m_mainLayout->addWidget(m_uploadButton);
}

void UploadWidget::createActions() {
    connect(m_clearButton, SIGNAL(clicked()),
            this, SLOT(s_clear()));
    connect(m_browseButton, SIGNAL(clicked()),
            this, SLOT(s_browse()));
    connect(m_uploadButton, SIGNAL(clicked()),
            this, SLOT(s_upload()));
}

void UploadWidget::s_upload() {
    // make sure all fields are filled in
    if(m_titleField->text().trimmed() != "" &&
            m_authorField->text().trimmed() != "" &&
            m_fileLabel->text().trimmed() != "") {
        // make a copy of the file
        QString newPath(docDir + "/" + QString::number(m_db->getLastInsertRowUID() + 1) + ".txt");
        QFile::copy(m_fileLabel->text(), newPath);
        // add to database
        // no genre or summaries for now

        m_db->addDocument(m_titleField->text(), m_authorField->text(), 0, "summary", QString::number(55));

        m_titleField->clear();
        m_authorField->clear();
        m_fileLabel->clear();
    }else {
        // notify user to fill in all fields
        qDebug() << "All fields must be filled in.";
    }
}

UploadWidget::~UploadWidget() {}
