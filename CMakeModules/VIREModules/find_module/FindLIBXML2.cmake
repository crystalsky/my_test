###############################################################################
# CMake module to search for LIBXML2 library
#The files in this package do not require any special installation
#steps. Extract the contents of the archive whereever you wish and
#make sure that your tools which use libxml2 can find it.
# 
###############################################################################
SET(LIBXML2_HOME $ENV{THIRDPARTY_PATH}/libxml2)

MACRO( FIND_LIBXML2_INCLUDE THIS_LIBXML2_INCLUDE_DIR THIS_LIBXML2_INCLUDE_FILE )

FIND_PATH( ${THIS_LIBXML2_INCLUDE_DIR} ${THIS_LIBXML2_INCLUDE_FILE}
    PATHS
        ${LIBXML2_HOME}
    PATH_SUFFIXES
        /include/
)

ENDMACRO( FIND_LIBXML2_INCLUDE THIS_LIBXML2_INCLUDE_DIR THIS_LIBXML2_INCLUDE_FILE )

FIND_LIBXML2_INCLUDE( LIBXML2_INCLUDE_DIR libxml/list.h)
IF(WIN32)

  IF (MSVC)
    FIND_LIBRARY(LIBXML2_LIBRARY NAMES libxml2.lib
    PATHS    
    "${LIBXML2_HOME}/lib/release/"
      NO_DEFAULT_PATH
      )


  ENDIF (MSVC)


ENDIF(WIN32)


IF (LIBXML2_INCLUDE_DIR AND LIBXML2_LIBRARY)
   SET(LIBXML2_FOUND TRUE)
ENDIF (LIBXML2_INCLUDE_DIR AND LIBXML2_LIBRARY)

IF (LIBXML2_FOUND)

   IF (NOT LIBXML2_FIND_QUIETLY)
      MESSAGE(STATUS "Found LIBXML2: ${LIBXML2_LIBRARY}")
   ENDIF (NOT LIBXML2_FIND_QUIETLY)
    
  SET(LIBXML2_LIBRARIES ${LIBXML2_LIBRARY})
ELSE (LIBXML2_FOUND)

   MESSAGE(LIBXML2_INCLUDE_DIR=${LIBXML2_INCLUDE_DIR})
   MESSAGE(LIBXML2_LIBRARY=${LIBXML2_LIBRARY})
   MESSAGE(FATAL_ERROR "Could not find LIBXML2")

ENDIF (LIBXML2_FOUND)

