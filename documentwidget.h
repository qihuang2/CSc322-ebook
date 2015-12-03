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
#include <QSlider>
#include <QSpinBox>
#include <QScrollBar>
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
    void getSliderValueandQuit();
    void clearReport();
    void showReport();
    void hideReport();
    void submitReport();

private:
    void createLayouts();
    void createActions();

    void readFile(QString);
    void writeReview();
    void writeReport();

    QTextEdit *m_txt;
    QTextEdit *m_reviewText;
    QTextEdit *m_reportText;

    QVBoxLayout *m_mainLayout;
    QVBoxLayout *m_reviewLayout;
    QHBoxLayout *m_buttonLayout;
    QHBoxLayout *m_creditLayout;
    QHBoxLayout *m_reviewButtonLayout;
    QHBoxLayout *m_ratingLayout;
    QHBoxLayout *m_reportLayout;

    QLabel*	m_time;
    QLabel* m_credits;
    QLabel* m_rating;

    QPushButton* m_closeButton;
    QPushButton* m_submitReview;
    QPushButton* m_clearReview;
    QPushButton* m_reviewButton;
    QPushButton* m_reportButton;
    QPushButton *m_hideReview;
    QPushButton *m_hideReport;
    QPushButton *m_submitReport;
    QPushButton *m_clearReport;

    QTimer*			m_timer;

    BaseUser*		m_baseUser;

    QSlider *m_slider;

    QSpinBox *m_box;

    int				m_timevalue;
    int				m_currentCredits;

};

#endif // DOCUMENTWIDGET_H
