#include "registereduser.h"
#include "uploadwidget.h"
#include <QLabel>
#include <QString>
#include <QBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QDebug>
#include <QPlainTextEdit>
#include <QSpinBox>
#include "constants.h"
#include "documentsdb.h"
#include "mainwindow.h"

UploadWidget::UploadWidget(RegisteredUser* user, QWidget *parent) : QWidget(parent)
{
    m_db = new DocumentsDB();
    m_user = user;

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
    m_creditsField = new QSpinBox();
    m_genreField = new QComboBox();
    m_summaryField = new QPlainTextEdit();

    m_clearButton = new QPushButton(tr("Clear"));
    m_browseButton = new QPushButton(tr("Browse"));
    m_fileLabel = new QLineEdit();
    m_fileLabel->setReadOnly(true);

    m_uploadButton = new QPushButton(tr("Upload"));
    m_uploadButton->setFixedSize(QSize(100,50));

    for(int i = _SELECT_; i <= YOUNGADULT; ++i) {
        m_genreField->addItem(genres[i]);
    }
}

void UploadWidget::createLayouts() {
    m_mainLayout = new QVBoxLayout();

    QHBoxLayout* titleLayout = new QHBoxLayout();
    QLabel* titleLabel = new QLabel(tr("Title\t\t"));
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(m_titleField);

    QHBoxLayout* authorLayout = new QHBoxLayout();
    QLabel* authorLabel = new QLabel(tr("Credits Requested\t\t"));
    authorLayout->addWidget(authorLabel);
    authorLayout->addWidget(m_creditsField);

    QHBoxLayout* genreLayout = new QHBoxLayout();
    QLabel* genreLabel = new QLabel(tr("Genre\t\t"));
    genreLayout->addWidget(genreLabel);
    genreLayout->addWidget(m_genreField);

    QHBoxLayout* summLayout = new QHBoxLayout();
    QLabel* summLabel = new QLabel(tr("Summary\t\t"));
    summLayout->addWidget(summLabel);
    summLayout->addWidget(m_summaryField);

    m_mainLayout->addLayout(titleLayout);
    m_mainLayout->addLayout(authorLayout);
    m_mainLayout->addLayout(genreLayout);
    m_mainLayout->addLayout(summLayout);

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
    if(fieldsFilledIn()) {
        m_db->addDocument(m_titleField->text(), m_user->getUsername(), m_genreField->currentIndex(), m_summaryField->toPlainText(), QString::number(m_creditsField->value()));

        // make copy
        int nextUID = m_db->getLastInsertRowUID();
        qDebug() << "NEW UID: " << nextUID;
        QString newPath(docDir + "/" + QString::number(nextUID) + ".txt");
        QFile::copy(m_fileLabel->text(), newPath);

        QMessageBox::information(this, tr("Uploaded!"),
            "Your document has been sent to the Super-User to seek approval!");

        clearFields();
    }else {
        QMessageBox::information(this, tr("Failed!"),
            "Please make sure all fields are filled in.");
    }
}

bool UploadWidget::fieldsFilledIn() {
    return m_titleField->text().trimmed() != "" &&
            m_fileLabel->text().trimmed() != "" &&
            m_summaryField->toPlainText() != "" &&
            m_genreField->currentIndex() != _SELECT_;
}

void UploadWidget::clearFields() {
    m_titleField->clear();
    m_creditsField->setValue(0);
    m_fileLabel->clear();
    m_summaryField->setPlainText("");
    m_genreField->setCurrentIndex(_SELECT_);
}

UploadWidget::~UploadWidget() {}
