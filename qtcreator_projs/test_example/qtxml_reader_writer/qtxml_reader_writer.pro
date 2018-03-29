#-------------------------------------------------
#
# Project created by QtCreator 2016-04-15T14:17:12
#
#-------------------------------------------------

QT       += core gui widgets xml

TARGET = qtxml_reader_writer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    WirelessInfoReader.cpp \
    WirednetInfoReader.cpp

HEADERS += \
    WirelessInfoReader.h \
    WirednetInfoReader.h

CONFIG(debug, debug|release){
    TARGET=$$join(TARGET,,,d)
    contains(TEMPLATE, "lib"){
        DESTDIR=../../lib
        DLLDESTDIR=../../bin
    }else{
        DESTDIR=../../bin
    }
    OBJECTS_DIR=./debug/obj
    MOC_DIR=./debug/moc
}
else
{
    contains(TEMPLATE, "lib"){
        DESTDIR=../../lib
        DLLDESTDIR=../../bin
    }else{
        DESTDIR=../../bin
    }
    OBJECTS_DIR=./release/obj
    MOC_DIR=./release/moc
}


message(The project will be installed in $$DESTDIR)

message(Qt version: $$[QT_VERSION])
message(Qt is installed in $$[QT_INSTALL_PREFIX])
message(Qt resources can be found in the following locations:)
message(Documentation: $$[QT_INSTALL_DOCS])
message(Header files: $$[QT_INSTALL_HEADERS])
message(Libraries: $$[QT_INSTALL_LIBS])
message(Binary files (executables): $$[QT_INSTALL_BINS])
message(Plugins: $$[QT_INSTALL_PLUGINS])
message(Data files: $$[QT_INSTALL_DATA])
message(Translation files: $$[QT_INSTALL_TRANSLATIONS])
message(Settings: $$[QT_INSTALL_CONFIGURATION])
message(Examples: $$[QT_INSTALL_EXAMPLES])
