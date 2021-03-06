
SET(OSG_NAME osgOcean)
SET(OSGOCEAN_DIR $ENV{THIRDPARTY_PATH}/${OSG_NAME}/1.0.1)
SET(OSGOCEAN_BIN_PATH ${OSGOCEAN_DIR}/bin)
MACRO( FIND_OSGOCEAN_INCLUDE THIS_OSGOCEAN_INCLUDE_DIR THIS_OSGOCEAN_INCLUDE_FILE )

FIND_PATH( ${THIS_OSGOCEAN_INCLUDE_DIR} ${THIS_OSGOCEAN_INCLUDE_FILE}
    PATHS
        ${OSGOCEAN_DIR}
    PATH_SUFFIXES
        /include/
)

ENDMACRO( FIND_OSGOCEAN_INCLUDE THIS_OSGOCEAN_INCLUDE_DIR THIS_OSGOCEAN_INCLUDE_FILE )

FIND_OSGOCEAN_INCLUDE( OSGOCEAN_INCLUDE_DIR osgOcean/OceanScene)

###### libraries ######

MACRO( FIND_OSGOCEAN_LIBRARY MYLIBRARY MYLIBRARYNAME )

FIND_LIBRARY(${MYLIBRARY}
    NAMES
        ${MYLIBRARYNAME}
    PATHS
        ${OSGOCEAN_DIR}
    PATH_SUFFIXES
        /lib/
     )

ENDMACRO(FIND_OSGOCEAN_LIBRARY LIBRARY LIBRARYNAME)


FIND_OSGOCEAN_LIBRARY( OSGOCEAN_LIBRARY OSGOCEAN )
FIND_OSGOCEAN_LIBRARY( OSGOCEAN_LIBRARY_DEBUG OSGOCEANd )

SET( OSGOCEAN_FOUND "NO" )
IF( OSGOCEAN_LIBRARY AND OSGOCEAN_INCLUDE_DIR )
    SET( OSGOCEAN_FOUND "YES" )
    SET( OSGOCEAN_INCLUDE_DIRS ${OSGOCEAN_INCLUDE_DIR} )
    GET_FILENAME_COMPONENT( OSGOCEAN_LIBRARIES_DIR ${OSGOCEAN_LIBRARY} PATH )
ENDIF( OSGOCEAN_LIBRARY AND OSGOCEAN_INCLUDE_DIR )


FILE(GLOB ${APPLICATION_NAME}_DLL "${OSGOCEAN_BIN_PATH}/*.dll")
INSTALL(FILES ${${APPLICATION_NAME}_DLL} DESTINATION bin)