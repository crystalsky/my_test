
SET(QWT_NAME QWT)
#SET(QWT_DIR $ENV{QWT_DIR})

FIND_PATH(QWT_INCLUDE_DIR qwt.h
PATHS
    ${QWT_DIR}/include
	${QWT_DIR}/include/QWT
)

###### libraries ######

FIND_LIBRARY(QWT_LIBRARY
  NAMES ${QWT_NAME}
  PATHS
  "${QWT_DIR}/lib"
)

FIND_LIBRARY(QWT_LIBRARY_DEBUG
  NAMES ${QWT_NAME}d
  PATHS
  "${QWT_DIR}/lib"
)
	  
SET(QWT_FOUND "NO")
IF(QWT_LIBRARY AND QWT_INCLUDE_DIR)
    SET(QWT_FOUND "YES")

    include(util.common_make_import_target)
    COMMON_MAKE_IMPORT_TARGET_BASE(QWT QWT
      ${QWT_INCLUDE_DIR}
      ${QWT_LIBRARY_DEBUG}
      ${QWT_LIBRARY}
    )
ENDIF(QWT_LIBRARY AND QWT_INCLUDE_DIR)


MESSAGE("******Finish FOUND ********")