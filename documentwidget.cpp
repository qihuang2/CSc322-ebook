#include "documentwidget.h"
#include "mainwindow.h"
#include "registereduser.h"

bool open = false; //Variable to keep track if a document is open
              //false if no document open, true if document is open

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
        readFile();
        m_timevalue=0;
        m_timer=new QTimer(this);
        connect(m_timer,SIGNAL(timeout()),this,SLOT(s_counter()));
        m_timer->start(1000);

    }
    writeReview();
}

//Layout for the Document Tab
void DocumentWidget::createLayouts()
{
    QWidget* widget = new QWidget();
    m_txt = new QTextEdit(widget); //Create a Text Box Widget
    m_reviewText = new QTextEdit(widget);

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
    //Set the Layout
    m_buttonLayout = new QHBoxLayout();
    m_creditLayout = new QHBoxLayout();
    m_reviewLayout = new QVBoxLayout();
    m_reviewButtonLayout = new QHBoxLayout();

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
    m_reviewButtonLayout->addWidget(m_clearReview);
    m_reviewButtonLayout->addWidget(m_hideReview);
    m_reviewButtonLayout->addWidget(m_submitReview);
    m_mainLayout->addLayout(m_reviewLayout);//Place the review layout into main layout
    m_mainLayout->addLayout(m_reviewButtonLayout);
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
void DocumentWidget::readFile()
{
    m_txt->setReadOnly(true);//text box is read only
    open = true; //indicate there a file currently open

    QFile file("/home/vfung000/Desktop/try.txt"); //open file
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
}

//close the (current) file
void DocumentWidget::closeFile()
{
    m_txt->clear();
    open = false;
}

void DocumentWidget::writeReview()
{
    QString initialLine = "Hello, write your review here!";
    m_reviewText->append(initialLine);
}

void DocumentWidget::clearReview()
{
    m_reviewText->clear();
}

void DocumentWidget::showReview()
{
    m_reviewText->show();
    m_clearReview->show();
    m_submitReview->show();
    m_hideReview->show();
}

void DocumentWidget::hideReview()
{
    m_reviewText->hide();
    m_clearReview->hide();
    m_submitReview->hide();
    m_hideReview->hide();
}
