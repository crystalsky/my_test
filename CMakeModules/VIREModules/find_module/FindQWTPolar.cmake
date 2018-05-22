
SET(QWTPOLAR_NAME QWTPOLAR)
#SET(QWTPOLAR_DIR $ENV{QWTPOLAR_DIR})

FIND_PATH(QWTPOLAR_INCLUDE_DIR qwt_polar.h
PATHS
    ${QWTPOLAR_DIR}/include
	${QWTPOLAR_DIR}/include/QWTPOLAR
)

###### libraries ######

FIND_LIBRARY(QWTPOLAR_LIBRARY
  NAMES ${QWTPOLAR_NAME}
  PATHS
  "${QWTPOLAR_DIR}/lib"
)

FIND_LIBRARY(QWTPOLAR_LIBRARY_DEBUG
  NAMES ${QWTPOLAR_NAME}d
  PATHS
  "${QWTPOLAR_DIR}/lib"
)
	  
SET(QWTPOLAR_FOUND "NO")
IF(QWTPOLAR_LIBRARY AND QWTPOLAR_INCLUDE_DIR)
    SET(QWTPOLAR_FOUND "YES")
ENDIF(QWTPOLAR_LIBRARY AND QWTPOLAR_INCLUDE_DIR)


MESSAGE("******Finish FOUND ********")