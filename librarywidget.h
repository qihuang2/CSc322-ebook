#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QModelIndex>
#include "historydb.h"
class MainWindow;
class QTableWidget;
class QVBoxLayout;
class QPushButton;
class DocumentsDB;

class LibraryWidget : public QWidget
{
    Q_OBJECT
public:
    LibraryWidget(QString loginUserName,MainWindow* mw, QWidget *parent = 0);
    ~LibraryWidget();

    void refreshTable();

private:
    MainWindow*         m_parent;
    QVBoxLayout*        m_mainLayout;
    QHBoxLayout*        m_tablewithpreviewLayout;
    QHBoxLayout*        m_titleLayout;
    QHBoxLayout*        m_authorLayout;
    QHBoxLayout*        m_genreLayout;
    QVBoxLayout*        m_previewLayout;
    QHBoxLayout*        m_previewbuttonLayout;
    QHBoxLayout*        m_ratingLayout;
    QVBoxLayout*        m_recommendLayout;
    QHBoxLayout*        m_searchLayout;

    QPushButton*        m_refresh;
    QPushButton*        m_hidePreview;
    QPushButton*        m_openBook;
    QPushButton*        m_hideRecommend;
    QPushButton*        m_showRecommend;
    QPushButton*        m_startSearch;

    QTableWidget*       m_tableWidget;
    QTableWidget*       m_previewWidget;
    QTableWidget*       m_recommendWidget;
    QTableWidget*       m_commentWidget;

    QLabel*             m_title;
    QLabel*             m_author;
    QLabel*             m_genre;
    QLabel*             m_rating;
    QLabel*             m_booktitle;
    QLabel*             m_bookauthor;
    QLabel*             m_bookgenre;
    QLabel*             m_bookrating;
    QLabel*             m_recommend;

    DocumentsDB*        m_db;

    QString             Title;
    QString             Author;
    QString             Genre;
    QString             Rating;
    QString				m_loginName;
    QString             path;

    QLineEdit*           m_search;

    QComboBox*           m_searchBy;

    void createWidgets();
    void createLayouts();
    void createActions();

    void createRecommend();

    void removeFileWithID(int id);

    void populateSearch();

    QString stringToEnumValue(QString subject);

public slots:
    void s_refresh();
    void showPreview();
    void hidePreview();
    void selectCell();
    void s_addHistory();
    void hideRecommendations();
    void showRecommendations();
    void selectRecommendation();
    QString getPath();
    int getRow();
    void startSearch();
};

#endif // LIBRARYWIDGET_H
