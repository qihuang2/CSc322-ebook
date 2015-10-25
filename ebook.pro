#-------------------------------------------------
#
# Project created by QtCreator 2015-10-09T11:19:00
#
#-------------------------------------------------

QT       += core gui sql
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ebook
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tablewindow.cpp \
    uploadwindow.cpp \
    logindb.cpp \
    loginwidget.cpp \
    registerwidget.cpp

HEADERS  += mainwindow.h \
    logindb.h \
    loginwidget.h \
    registerwidget.h

FORMS    += mainwindow.ui

DISTFILES +=

