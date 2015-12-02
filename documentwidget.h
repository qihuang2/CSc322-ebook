#ifndef DOCUMENTWIDGET_H
#define DOCUMENTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>

class DocumentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DocumentWidget(QWidget *parent = 0);

signals:

public slots:

private:
    QTextEdit *txt;
    QVBoxLayout *m_mainLayout;
    void createLayouts();

    void closeFile();
    void readFile();
};

#endif // DOCUMENTWIDGET_H
