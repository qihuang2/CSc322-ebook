#ifndef PROFILEWIDGET_H
#define PROFILEWIDGET_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "baseuser.h"
class DocumentsDB;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QLineEdit;
class QComboBox;
class ProfileWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProfileWidget(QWidget *parent = 0,BaseUser *m_baseuser=0);
    ~ProfileWidget();
private:

};

#endif // PROFILEWIDGET_H
