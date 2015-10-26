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

    QString         m_filename;
    QPushButton*    m_clearButton;
    QPushButton*    m_browseButton;
    QLineEdit*      m_fileLabel;

private slots:
    void s_clear();
    void s_browse();
};

#endif // UPLOADWIDGET_H
