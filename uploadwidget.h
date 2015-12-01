#ifndef UPLOADWIDGET_H
#define UPLOADWIDGET_H

#include <QWidget>

class DocumentsDB;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QLineEdit;
class QComboBox;

class UploadWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UploadWidget(QWidget *parent = 0);
    ~UploadWidget();

private:
    void createWidgets();
    void createLayouts();
    void createActions();

    DocumentsDB*    m_db;
    QVBoxLayout*    m_mainLayout;
    QLineEdit*      m_titleField;
    QLineEdit*      m_authorField;
    QComboBox*      m_genreField;
    QHBoxLayout*    m_uploadLayout;
    QPushButton*    m_clearButton;  /* Clears current path. */
    QPushButton*    m_browseButton; /* Allows user to browse for a file. */
    QPushButton*    m_uploadButton; /* To complete the upload. */
    QLineEdit*      m_fileLabel;    /* Displays file path. */

private slots:
    void s_clear();
    void s_browse();
    void s_upload();
};

#endif // UPLOADWIDGET_H
