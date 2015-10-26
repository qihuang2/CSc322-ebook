#include "mainwindow.h"
#include "librarywidget.h"
#include "uploadwidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

MainWindow::MainWindow(bool loginStatus)
{
    // will recieve `loggedIn` through contructor parameters when I figure out how
    m_loggedIn = loginStatus;

    createWidgets();
    createLayouts();
    createActions();

    setCentralWidget(m_centralWidget);
    setMinimumSize(600, 400);
    setWindowTitle("图书馆");
}

void MainWindow::createWidgets() {
    m_tabWidget = new QTabWidget();

    // create the widgets to be added to the tabs
    LibraryWidget* lib = new LibraryWidget(m_tabWidget);
    UploadWidget* up = new UploadWidget(m_tabWidget);

    m_tabWidget->addTab(lib, "Library");
    m_tabWidget->addTab(up, "Upload");

    m_loginLabel = new QLabel();
    m_loginLabel->setText(m_loggedIn ? "Logged in as USR" : "Visiting User");

    m_exitButton = new QPushButton("Exit");
    m_exitButton->setMaximumSize(QSize(100, 50));

    m_centralWidget = new QWidget();
}

void MainWindow::createLayouts() {
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->addWidget(m_loginLabel);
    m_mainLayout->addWidget(m_tabWidget);
    m_mainLayout->addWidget(m_exitButton);

    m_centralWidget->setLayout(m_mainLayout);
}

void MainWindow::createActions() {
    connect(m_exitButton, SIGNAL(clicked()),
            this, SLOT(close()));
}

MainWindow::~MainWindow() {}
