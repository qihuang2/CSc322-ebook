#include "documentwidget.h"

bool open = false; //Variable to keep track if a document is open
              //false if no document open, true if document is open
DocumentWidget::DocumentWidget(QWidget *parent) : QWidget(parent)
{
    createLayouts(); //Create layout within Document Tab
    if (open == true)
        closeFile();
    if (open == false)
        readFile();
}

//Layout for the Document Tab
void DocumentWidget::createLayouts()
{
    QWidget* widget = new QWidget();
    m_mainLayout = new QVBoxLayout(widget);
    txt = new QTextEdit(widget); //Create a Text Box Widget
    m_mainLayout->addWidget(txt); //Place the Text Box Widget into the main layout
    setLayout(m_mainLayout);
}

//read the file
void DocumentWidget::readFile()
{
    qDebug() << "Reading try.txt";
    open = true; //indicate there a file currently open
    QFile file("/home/vfung000/Desktop/try.txt");
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
