#ifndef UPLOADWIDGET_H
#define UPLOADWIDGET_H

#include <QWidget>

class RegisteredUser;
class DocumentsDB;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QLineEdit;
class QComboBox;
class QSpinBox;
class QPlainTextEdit;

class UploadWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UploadWidget(RegisteredUser* user, QWidget *parent = 0);
    ~UploadWidget();

    typedef enum {
        _SELECT_,
        BIO,
        FANTASY,
        HISTORY,
        HORROR,
        KIDS,
        MANGA,
        MYSTERY,
        MYTH,
        ROMANCE,
        SCIFI,
        YOUNGADULT
    } Genre;

private:
    void createWidgets();
    void createLayouts();
    void createActions();

    bool fieldsFilledIn();
    void clearFields();

    RegisteredUser* m_user;
    DocumentsDB*    m_db;
    QVBoxLayout*    m_mainLayout;
    QLineEdit*      m_titleField;
    QSpinBox*       m_creditsField;
    QComboBox*      m_genreField;
    QPlainTextEdit* m_summaryField;
    QString         m_listGenres[YOUNGADULT+1];
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
