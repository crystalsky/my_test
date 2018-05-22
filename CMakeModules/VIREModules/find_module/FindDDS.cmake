# Locate dds
# This module defines
# DDS_LIBRARY
# DDS_FOUND, if false, do not try to link to dds 
# DDS_INCLUDE_DIR, where to find the headers
#
# $DDS_DIR is an environment variable that would
# correspond to the ./configure --prefix=$DDS_DIR
#
# Created by David Guthrie.  Based on cdds by Robert Osfield 
MESSAGE(STATUS "searching DDSt         cvdsadfasd")
MESSAGE(STATUS "searching DDSt         cvdsadfasd")
MESSAGE(STATUS "searching DDSt         cvdsadfasd")
FIND_PATH(DDS_INCLUDE_DIR ddst.h
    ${DDS_DIR}/include
    $ENV{DDS_DIR}/include
    $ENV{DDS_DIR}/inc
    ${DELTA3D_EXT_DIR}/inc
    $ENV{DELTA_ROOT}/ext/inc
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/include
    /usr/include
    /usr/include/cal3d
    /sw/include # Fink
    /opt/local/include # DarwinPorts
    /opt/csw/include # Blastwave
    /opt/include
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OSG_ROOT]/include
    /usr/freeware/include
)


MACRO(FIND_DDS_LIBRARY MYLIBRARY MYLIBRARYNAME)
MESSAGE(STATUS "searching ${DEPNAME} -->${INCLUDEFILE}<-->${LIBRARY}<-->${SEARCHPATHLIST}<--")

FIND_LIBRARY(${MYLIBRARY}
    NAMES ${MYLIBRARYNAME}
    PATHS
    ${DDS_DIR}/lib
    $ENV{DDS_DIR}/lib
    $ENV{DDS_DIR}
    ${DELTA3D_EXT_DIR}/lib
    $ENV{DELTA_ROOT}/ext/lib
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/lib
    /usr/lib
    /sw/lib
    /opt/local/lib
    /opt/csw/lib
    /opt/lib
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OSG_ROOT]/lib
    /usr/freeware/lib64
)

ENDMACRO(FIND_DDS_LIBRARY MYLIBRARY MYLIBRARYNAME)

SET(RELEASE_LIST DDST)
FIND_DDS_LIBRARY(DDS_LIBRARY "${RELEASE_LIST}")

SET(DEBUG_LIST DDSTd)
FIND_DDS_LIBRARY(DDS_LIBRARY_DEBUG "${DEBUG_LIST}")

SET(DDS_FOUND "NO")
IF(DDS_LIBRARY AND DDS_INCLUDE_DIR)
    SET(DDS_FOUND "YES")
ENDIF(DDS_LIBRARY AND DDS_INCLUDE_DIR)


