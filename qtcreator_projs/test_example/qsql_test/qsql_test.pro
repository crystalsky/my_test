#-------------------------------------------------
#
# Project created by QtCreator 2016-04-18T18:16:52
#
#-------------------------------------------------

QT       += core gui sql concurrent

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qsql_test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    DBManager.cpp

HEADERS  += mainwindow.h \
    DBManager.h

FORMS    += mainwindow.ui
