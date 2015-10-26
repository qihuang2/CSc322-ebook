#-------------------------------------------------
#
# Project created by QtCreator 2015-10-25T14:21:58
#
#-------------------------------------------------

QT       += core gui
QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ebookgui2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    librarywidget.cpp \
    logindb.cpp \
    loginwidget.cpp \
    registerwidget.cpp \
    uploadwidget.cpp \
    welcomedialog.cpp

HEADERS  += mainwindow.h \
    librarywidget.h \
    logindb.h \
    loginwidget.h \
    registerwidget.h \
    uploadwidget.h \
    welcomedialog.h

FORMS    +=

DISTFILES += \
    ebook.pro.user.70d6957
