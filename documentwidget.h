#ifndef DOCUMENTWIDGET_H
#define DOCUMENTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include "baseuser.h"
class DocumentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DocumentWidget(QWidget *parent = 0,BaseUser *m_baseuser=0);

signals:

public slots:
    void s_counter();
    void closeFile();
    void clearReview();
    void showReview();
    void hideReview();
    void submitReview();

private:
    void createLayouts();
    void createActions();

    void readFile(QString);
    void writeReview();

    QTextEdit *m_txt;
    QTextEdit *m_reviewText;
    QVBoxLayout *m_mainLayout;
    QVBoxLayout *m_reviewLayout;
    QHBoxLayout *m_buttonLayout;
    QHBoxLayout *m_creditLayout;
    QHBoxLayout *m_reviewButtonLayout;

    QLabel*			m_time;
    QLabel*			m_credits;

    QPushButton* m_closeButton;
    QPushButton* m_submitReview;
    QPushButton* m_clearReview;
    QPushButton* m_reviewButton;
    QPushButton* m_reportButton;
    QPushButton *m_hideReview;

    int				m_timevalue;
    QTimer*			m_timer;
    int				m_currentCredits;
    BaseUser*		m_baseUser;
};

#endif // DOCUMENTWIDGET_H
