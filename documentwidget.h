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
#include <QTimer>
#include <QLabel>
#include "baseuser.h"
class DocumentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DocumentWidget(QWidget *parent = 0,BaseUser *m_baseuser=0);

signals:

public slots:
    void s_counter();
private:
    QTextEdit *txt;
    QVBoxLayout *m_mainLayout;
    void createLayouts();

    void closeFile();
    void readFile();

    QLabel*			m_time;
    QLabel*			m_credits;
    int				m_timevalue;
    QTimer*			m_timer;
    int				m_currentCredits;
    BaseUser*		m_baseUser;
};

#endif // DOCUMENTWIDGET_H
