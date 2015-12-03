#include "documentwidget.h"
#include "mainwindow.h"
#include "registereduser.h"
#include "documentsdb.h"

bool open = false; //Variable to keep track if a document is open
              //false if no document open, true if document is open
QString path = "/Users/youshenghua/Desktop/1.txt";

DocumentWidget::DocumentWidget(QWidget *parent,BaseUser *bu) : QWidget(parent)
{
    //set up Timer
    m_baseUser=bu;
    m_time=new QLabel("Time:0:00");
    m_credits=new QLabel("Credits:0");
    createLayouts(); //Create layout within Document Tab
    createActions();
    if (open == true)
    {
        closeFile();
    }
    if (open == false)
    {
        readFile(path);
        m_timevalue=0;
        m_timer=new QTimer(this);
        connect(m_timer,SIGNAL(timeout()),this,SLOT(s_counter()));
        m_timer->start(1000);
    }
    writeReview();
    writeReport();
}

//Layout for the Document Tab
void DocumentWidget::createLayouts()
{
    QWidget* widget = new QWidget();

    m_txt = new QTextEdit(widget); //Create a Text Box Widget
    m_reviewText = new QTextEdit(widget); //Create a Review Box Widget
    m_reportText = new QTextEdit(widget); //Create a Report Box Widget

    //Create Labels
    m_rating = new QLabel("Rate this book:");

    //Create the buttons
    m_reviewButton = new QPushButton("Review Document");
    m_reviewButton->setMaximumSize(QSize(150,50));
    m_reportButton = new QPushButton("Report Document");
    m_reportButton->setMaximumSize(QSize(150, 50));
    m_closeButton = new QPushButton("Close Document");
    m_closeButton->setMaximumSize(QSize(150, 50));
    m_clearReview = new QPushButton("Clear Review");
    m_clearReview->setMaximumSize(QSize(150, 50));
    m_submitReview = new QPushButton("Submit Review");
    m_submitReview->setMaximumSize(QSize(150, 50));
    m_hideReview = new QPushButton("Hide Review Box");
    m_hideReview->setMaximumSize(QSize(150, 50));
    m_hideReport = new QPushButton("Hide Report Box");
    m_hideReport->setMaximumSize(QSize(150, 50));
    m_submitReport = new QPushButton("Submit Report");
    m_submitReport->setMaximumSize(QSize(150, 50));
    m_clearReport = new QPushButton("Clear Report");
    m_clearReport->setMaximumSize(QSize(150, 50));

    //Create the Slider with initial values
    m_slider = new QSlider(Qt::Horizontal);
    m_slider->setRange(0, 5);
    m_slider->setValue(4);

    //Create the Spin box
    m_box = new QSpinBox;
    m_box->setRange(0, 5);

    //Set the Layout
    m_buttonLayout = new QHBoxLayout();
    m_creditLayout = new QHBoxLayout();
    m_reviewLayout = new QVBoxLayout();
    m_reviewButtonLayout = new QHBoxLayout();
    m_ratingLayout = new QHBoxLayout();
    m_reportLayout = new QHBoxLayout();

    m_mainLayout = new QVBoxLayout(widget);
    m_creditLayout->addWidget(m_time);
    m_creditLayout->addWidget(m_credits);
    m_mainLayout->addLayout(m_creditLayout);//Place the credit layout into main layout
    m_mainLayout->addWidget(m_txt); //Place the Text Box Widget into the main layout
    m_buttonLayout->addWidget(m_reviewButton);
    m_buttonLayout->addWidget(m_reportButton);
    m_buttonLayout->addWidget(m_closeButton);
    m_mainLayout->addLayout(m_buttonLayout);//Place the buttons layout into the main layout
    m_reviewLayout->addWidget(m_reviewText);
    m_ratingLayout->addWidget(m_slider);
    m_ratingLayout->addWidget(m_box);
    m_reviewButtonLayout->addWidget(m_clearReview);
    m_reviewButtonLayout->addWidget(m_hideReview);
    m_reviewButtonLayout->addWidget(m_submitReview);
    m_mainLayout->addLayout(m_reviewLayout);//Place the review layout into main layout
    m_mainLayout->addWidget(m_rating);
    m_mainLayout->addLayout(m_ratingLayout);//Place the rating layout into main layout
    m_mainLayout->addLayout(m_reviewButtonLayout);//Place the review button layout into main layout
    m_mainLayout->addWidget(m_reportText);
    m_reportLayout->addWidget(m_clearReport);
    m_reportLayout->addWidget(m_hideReport);
    m_reportLayout->addWidget(m_submitReport);
    m_mainLayout->addLayout(m_reportLayout);//Place the Report Layout into main layout

    //Hide the Report and Review Sections initially
    m_hideReport->hide();
    m_reportText->hide();
    m_clearReport->hide();
    m_submitReport->hide();
    m_rating->hide();
    m_box->hide();
    m_slider->hide();
    m_reviewText->hide();
    m_clearReview->hide();
    m_submitReview->hide();
    m_hideReview->hide();
    setLayout(m_mainLayout);
}

//Actions for the buttons
void DocumentWidget::createActions()
{
    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(closeFile()));
    connect(m_reviewButton, SIGNAL(clicked()), this, SLOT(showReview()));
    connect(m_clearReview, SIGNAL(clicked()), this, SLOT(clearReview()));
    connect(m_hideReview, SIGNAL(clicked()), this, SLOT(hideReview()));
    connect(m_submitReview, SIGNAL(clicked()), this, SLOT(submitReview()));
    connect(m_slider, SIGNAL(valueChanged(int)), m_box, SLOT(setValue(int)));
    connect(m_box, SIGNAL(valueChanged(int)), m_slider, SLOT(setValue(int)));
    connect(m_slider, SIGNAL(sliderReleased()), SLOT(getSliderValueandQuit));
    connect(m_reportButton, SIGNAL(clicked()), this, SLOT(showReport()));
    connect(m_clearReport, SIGNAL(clicked()), this, SLOT(clearReport()));
    connect(m_hideReport, SIGNAL(clicked()), this, SLOT(hideReport()));
    connect(m_submitReport, SIGNAL(clicked()), this, SLOT(submitReport()));
}

// Counter Function
void DocumentWidget::s_counter()
{

   RegisteredUser* t = static_cast<RegisteredUser*>(m_baseUser);
   QString T;
   m_timevalue++;
   int minute=m_timevalue/60;

   //calculate current credit in every minute
   m_currentCredits=t->getNumOfCredits()-minute;
   m_credits->setText("Credits:"+QString::number(m_currentCredits));
   int leftSecond=m_timevalue%60;

   if(leftSecond<10)
   {
       T=QString::number(minute)+":0"+QString::number(leftSecond);
       m_time->setText("Time:"+T);
   }
   else
   {
       T=QString::number(minute)+":"+QString::number(leftSecond);
       m_time->setText("Time:"+T);
   }

}


//read the file
void DocumentWidget::readFile(QString path)
{
    m_txt->setReadOnly(true);//text box is read only
    open = true; //indicate there a file currently open

    QFile file(path); //open file
    QString line;

    //handle error
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file); //read into file
    while(!in.atEnd())
    {
        line = in.readLine();
        m_txt->append(line);
    }
    file.close(); //close the file
    m_txt->moveCursor(QTextCursor::Start);//move the cursor to the top of the document
    m_txt->ensureCursorVisible();
}

//close the (current) file
void DocumentWidget::closeFile()
{
    m_txt->clear();
    open = false;
    RegisteredUser* t = static_cast<RegisteredUser*>(m_baseUser);
    t->changeCreditsBy(m_currentCredits-t->getNumOfCredits());
    m_timer->stop();
}

//Initial box for review
void DocumentWidget::writeReview()
{
    QString initialLine = "Hello, write your review here!";
    m_reviewText->append(initialLine);
}

//Clear the current stuff written in Review
void DocumentWidget::clearReview()
{
    m_reviewText->clear();
}

//Show the Review Box
void DocumentWidget::showReview()
{
    m_rating->show();
    m_box->show();
    m_slider->show();
    m_reviewText->show();
    m_clearReview->show();
    m_submitReview->show();
    m_hideReview->show();
}

//Hide the Review Box
void DocumentWidget::hideReview()
{
    m_rating->hide();
    m_box->hide();
    m_slider->hide();
    m_reviewText->hide();
    m_clearReview->hide();
    m_submitReview->hide();
    m_hideReview->hide();
}

//Getting the review
void DocumentWidget::submitReview()
{
    //U_ID to get rating
    DocumentsDB *d =new DocumentsDB();
    d->addRatingToDocWithUID(4,m_slider->value());
    QString review; //Review will hold whatever is currently being held in the Review Text Box
    review = m_reviewText->toPlainText();
    qDebug() << "The review for " << path << " is " << review << " and is rated " << m_slider->value();
    m_reviewText->clear();
    writeReview();

}

//Get slider value
void DocumentWidget::getSliderValueandQuit()
{
    if (m_slider->value() == m_slider->maximum())
        close();
}

//Show the Report Box
void DocumentWidget::showReport()
{
    m_reportText->show();
    m_clearReport->show();
    m_hideReport->show();
    m_submitReport->show();
}

//Hide the Report Box
void DocumentWidget::hideReport()
{
    m_reportText->hide();
    m_clearReport->hide();
    m_hideReport->hide();
    m_submitReport->hide();
}

//Submit the Report
void DocumentWidget::submitReport()
{
    QString report;
    report = m_reportText->toPlainText();
    qDebug() << "The review for " << path << " is " << report;
    m_reportText->clear();
    writeReport();
}

//Initial line in the Report Box
void DocumentWidget::writeReport()
{
    QString initialLine = "Hello, write your report here!";
    m_reportText->append(initialLine);
}

void DocumentWidget::clearReport()
{
    m_reportText->clear();

}
