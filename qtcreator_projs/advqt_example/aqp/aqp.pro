#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T09:11:02
#
#-------------------------------------------------

QT += core gui widgets xml

TARGET = aqp
CONFIG   += console debug
#CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    alt_key.cpp \
    aqp.cpp \
    kuhn_munkres.cpp

RESOURCES += \
    aqp.qrc

HEADERS += \
    alt_key.hpp \
    aqp.hpp \
    kuhn_munkres.hpp
