#ifndef DOCUMENTWIDGET_H
#define DOCUMENTWIDGET_H

#include <QCoreApplication>
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
#include <QLineEdit>
#include "baseuser.h"
#include <QPlainTextEdit>

class MainWindow;
class QTabWidget;
class DocumentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DocumentWidget(QWidget *parent = 0, MainWindow* mw = 0, BaseUser *m_baseuser=0,QTabWidget*tab=0);

    void readFile(QString);
    void updateCredits();
    void ResumeTimer();
signals:

public slots:
    void s_counter();
    void closeFile();
    void showReview();
    void hideReview();
    void submitReview();
    void getSliderValueandQuit();
    void clearReport();
    void showReport();
    void hideReport();
    void submitReport();
    void s_search();
    void clearReview();
private:
    void createLayouts();
    void createActions();

    void writeBook();

    MainWindow* m_parent;

    QTextEdit *m_reportText;
    QTextEdit *m_reviewText;
    QTextEdit *m_txt;
    QLineEdit *m_searchLine;

    QVBoxLayout *m_mainLayout;
    QVBoxLayout *m_reviewLayout;
    QHBoxLayout *m_buttonLayout;
    QHBoxLayout *m_creditLayout;
    QHBoxLayout *m_reviewButtonLayout;
    QHBoxLayout *m_ratingLayout;
    QHBoxLayout *m_reportLayout;
    QHBoxLayout *m_searchLayout;

    QLabel*	m_time;
    QLabel* m_credits;
    QLabel* m_rating;
    QLabel* m_searchLabel;

    QPushButton* m_closeButton;
    QPushButton* m_submitReview;
    QPushButton* m_reviewButton;
    QPushButton* m_reportButton;
    QPushButton *m_hideReview;
    QPushButton *m_clearReview;
    QPushButton *m_hideReport;
    QPushButton *m_submitReport;
    QPushButton *m_clearReport;

    QTimer*	m_timer;

    BaseUser* m_baseUser;

    QSlider *m_slider;

    QSpinBox *m_box;

    QTabWidget* m_tab;

    int				m_timevalue;
    int				m_currentCredits;
    bool isFirstTime;

};

#endif // DOCUMENTWIDGET_H
