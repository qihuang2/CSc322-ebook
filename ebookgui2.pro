#-------------------------------------------------
#
# Project created by QtCreator 2015-10-25T14:21:58
#
#-------------------------------------------------

QT       += core gui
QT       += core gui sql

CONFIG += rtti

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ebookgui2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    librarywidget.cpp \
    loginwidget.cpp \
    registerwidget.cpp \
    uploadwidget.cpp \
    welcomedialog.cpp \
    maindb.cpp \
    logindb.cpp \
    userinfodb.cpp \
    baseuser.cpp \
    registereduser.cpp \
    documentwidget.cpp \
    documentsdb.cpp \
    constants.cpp \
    profilewidget.cpp \
    historydb.cpp \
    superuser.cpp

HEADERS  += mainwindow.h \
    librarywidget.h \
    loginwidget.h \
    registerwidget.h \
    uploadwidget.h \
    welcomedialog.h \
    maindb.h \
    logindb.h \
    userinfodb.h \
    baseuser.h \
    registereduser.h \
    documentwidget.h \
    documentsdb.h \
    constants.h \
    profilewidget.h \
    historydb.h \
    superuser.h

FORMS    +=

DISTFILES += \
    ebook.pro.user.70d6957
