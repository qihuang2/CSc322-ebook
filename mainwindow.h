#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QFileInfo>
#include <QListWidget>
#include <QLineEdit>
#include <QString>
#include <QTableWidget>
#include <QDir>
#include <QSplitter>
#include "loginwidget.h"
#include "registerwidget.h"

class QDialogButtonBox;
class QFileInfo;
class QTabWidget;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    //! Constructor.
    MainWindow(QString);
    explicit MainWindow(QWidget *parent = 0);

    void createActions();
    void createMenus();
    void createWidgets();
//    void traverseDirs(QString);
//    void initLists();

    QSplitter	*mainSplit;
    QSplitter   *rightSplit;

    QAction		*loadAction;
    QAction		*quitAction;

    QMenu		*fileMenu;

    QString directory;

    QList<QStringList> listBooks;

    QTabWidget *tabWidget;

    QPushButton *loginButton;
    QPushButton *registerButton;

    ~MainWindow();

public slots:
//    void s_load();
    void onLoginPushed();
    void onRegisterPushed();

private:
    Ui::MainWindow *ui;
};

class tableWindow : public QWidget {
    Q_OBJECT

public:
    explicit tableWindow(QWidget *parent = 0);
    QTableWidget *table;
    QSplitter *mainTable;
};

class uploadWindow : public QWidget {
    Q_OBJECT

public:
    explicit uploadWindow(QWidget *parent = 0);
    QSplitter *mainUpload;
};

#endif // MAINWINDOW_H
