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
}

//Layout for the Document Tab
void DocumentWidget::createLayouts()
{
    QWidget* widget = new QWidget();
    m_mainLayout = new QVBoxLayout(widget);
    m_mainLayout->addWidget(m_time);
    m_mainLayout->addWidget(m_credits);
    txt = new QTextEdit(widget); //Create a Text Box Widget
    m_mainLayout->addWidget(txt); //Place the Text Box Widget into the main layout
    setLayout(m_mainLayout);
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
    qDebug() << "Reading try.txt";
    open = true; //indicate there a file currently open
    QFile file("/Users/youshenghua/Desktop/1.txt");
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
        txt->append(line);
    }
    file.close(); //close the file
}

//close the (current) file
void DocumentWidget::closeFile()
{
    qDebug() << "Closing the current file";
    txt->clear();
    open = false;
}
