#ifndef UPLOADWIDGET_H
#define UPLOADWIDGET_H

#include <QWidget>

class QHBoxLayout;
class QPushButton;
class QLineEdit;

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

    QHBoxLayout*    m_mainLayout;
    QString         m_filename;     /* Holds path to file, otherwise NULL. */
    QPushButton*    m_clearButton;  /* Clears current path. */
    QPushButton*    m_browseButton; /* Allows user to browse for a file. */
    QLineEdit*      m_fileLabel;    /* Displays file path. */

private slots:
    void s_clear();
    void s_browse();
};

#endif // UPLOADWIDGET_H
