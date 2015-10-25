#include "mainwindow.h"
#include "ui_mainwindow.h"  
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::MainWindow (QString program)
    : directory(".")
{
    createActions();
    createMenus  ();
    createWidgets();
    setCentralWidget(mainSplit);
    setMinimumSize(400, 300);
    resize(800, 600);
}

void MainWindow::createWidgets()
{

    mainSplit  = new QSplitter(this);
    tabWidget = new QTabWidget;

    tabWidget->addTab(new tableWindow(), tr("Table of Contents"));
    tabWidget->addTab(new uploadWindow(), tr("Upload a book"));

    mainSplit->addWidget(tabWidget);

/*
 * I don't know how to position them
 *
 *
    //Add login button


    loginButton = new QPushButton(this);
    loginButton->setText("Login");
    connect(loginButton, SIGNAL(clicked()), this, SLOT(onLoginPushed()));

    registerButton = new QPushButton(this);
    registerButton->setText("Register");
    connect(registerButton, SIGNAL(clicked()), this, SLOT(onRegisterPushed()));

*/
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(loadAction);
    fileMenu->addAction(quitAction);
}

void MainWindow::createActions()
{
    loadAction = new QAction("&Load Files", this);
    loadAction->setShortcut(tr("Ctrl+L"));
    connect(loadAction, SIGNAL(triggered()), this, SLOT(s_load()));
    quitAction = new QAction("&Quit", this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::onLoginPushed(){
    LoginWidget *l = new LoginWidget(this);
    l->show();
}

void MainWindow::onRegisterPushed(){
    RegisterWidget *l = new RegisterWidget(this);
    l->show();
}

//void MainWindow::s_load()
//{
//    directory = path;
//    traverseDirs(directory);
//    initLists();
//}

//void MainWindow::initLists()
//{
//    // copy data to table widget
//    QTableWidgetItem *item[COLS];
//    for(int i=0; i<listBooks.size(); i++)
//    {
//        table->insertRow(i);

//        for(int j=0; j<COLS; j++)
//        {
//            item[j] = new QTableWidgetItem;
//            item[j]->setText(listBooks[i][j]);
//            item[j]->setTextAlignment(Qt::AlignCenter);
//            table->setItem(i, j, item[j]);
//        }
//    }
//}

//void MainWindow::traverseDirs(QString path)
//{
//    QStringList list;

//    // init listDirs with subdirectories of path
//    QDir dir(path);
//    dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
//    QFileInfoList listDirs = dir.entryInfoList();

//    // init listFiles with all *.mp3 files in path
//    QDir files(path);
//    files.setFilter(QDir::Files);
//    files.setNameFilters(QStringList("*.txt"));
//    QFileInfoList listFiles = files.entryInfoList();

//    for(int i=0; i < listFiles.size(); i++)
//    {
//        // init list with default values: ""
//        for(int j=0; j<=COLS; j++)
//            list.insert(j,"");
//        listBooks << list;
//    }
//    // recursively descend through all subdirectories
//    for(int i=0; i<listDirs.size(); i++)
//    {
//        QFileInfo fileInfo = listDirs.at(i);
//        traverseDirs( fileInfo.filePath() );
//    }
//    return;
//}

MainWindow::~MainWindow()
{
    delete ui;
}
