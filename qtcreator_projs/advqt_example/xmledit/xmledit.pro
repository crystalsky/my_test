CONFIG	    += console debug
HEADERS	    += ../aqp/aqp.hpp
SOURCES	    += ../aqp/aqp.cpp
RESOURCES   += ../aqp/aqp.qrc
INCLUDEPATH += ../aqp
HEADERS	    += xmlhighlighter.hpp
SOURCES     += xmlhighlighter.cpp
HEADERS	    += xmledit.hpp
SOURCES     += xmledit.cpp
SOURCES     += main.cpp
QT += gui widgets xml



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
