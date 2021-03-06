
SET(QWTPLOT3D_NAME QWTPLOT3D)

FIND_PATH(QWTPLOT3D_INCLUDE_DIR qwt3d_autoptr.h
PATHS
    ${QWTPLOT3D_DIR}/include
	${QWTPLOT3D_DIR}/include/QWTPLOT3D
)

###### libraries ######

FIND_LIBRARY(QWTPLOT3D_LIBRARY
  NAMES ${QWTPLOT3D_NAME}
  PATHS
  "${QWTPLOT3D_DIR}/lib"
)

FIND_LIBRARY(QWTPLOT3D_LIBRARY_DEBUG
  NAMES ${QWTPLOT3D_NAME}d
  PATHS
  "${QWTPLOT3D_DIR}/lib"
)
	  
SET(QWTPLOT3D_FOUND "NO")
IF(QWTPLOT3D_LIBRARY AND QWTPLOT3D_INCLUDE_DIR)
    SET(QWTPLOT3D_FOUND "YES")
ENDIF(QWTPLOT3D_LIBRARY AND QWTPLOT3D_INCLUDE_DIR)


MESSAGE("******Finish FOUND ********")