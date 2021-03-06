
set(THIS_LIB_DEPEND_NAME GDAL)

GET_DEPENDS_DIR(${THIS_LIB_DEPEND_NAME} 
  ${THIS_LIB_DEPEND_NAME}_SEARCH_FOLDERS
)

include(util.common_find_path)
COMMON_FIND_PATH_NORMAL(${THIS_LIB_DEPEND_NAME}
  "gdal/gdal.h"
  PATHS
    ${${THIS_LIB_DEPEND_NAME}_SEARCH_FOLDERS}
)

include(util.common_find_library)
COMMON_FIND_LIBARAY_NORMAL(
  ${THIS_LIB_DEPEND_NAME}_LIBRARY
  ${THIS_LIB_DEPEND_NAME}
  gdal_i
  VERSIONED_LIB
  DEBUG_MSG
)

COMMON_FIND_LIBARAY_NORMAL(
  ${THIS_LIB_DEPEND_NAME}_LIBRARY_DEBUG
  ${THIS_LIB_DEPEND_NAME}
  gdal_id
  VERSIONED_LIB
)

if(NOT ${THIS_LIB_DEPEND_NAME}_LIBRARY_DEBUG AND ${THIS_LIB_DEPEND_NAME}_LIBRARY)
  set(${THIS_LIB_DEPEND_NAME}_LIBRARY_DEBUG ${${THIS_LIB_DEPEND_NAME}_LIBRARY})
endif()

#验证变量合法
include(macro_find_package_handle_standard_args)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(
	${THIS_LIB_DEPEND_NAME} 
	DEFAULT_MSG
	${THIS_LIB_DEPEND_NAME}_LIBRARY 
	${THIS_LIB_DEPEND_NAME}_INCLUDE_DIR 
	${THIS_LIB_DEPEND_NAME}_LIBRARY_DEBUG
)

IF (${THIS_LIB_DEPEND_NAME}_FOUND)
   IF (NOT ${THIS_LIB_DEPEND_NAME}_FIND_QUIETLY)
      MESSAGE(STATUS "Found ${THIS_LIB_DEPEND_NAME}: ${${THIS_LIB_DEPEND_NAME}_LIBRARY_RELEASE}")
   ENDIF (NOT ${THIS_LIB_DEPEND_NAME}_FIND_QUIETLY)
ELSE (${THIS_LIB_DEPEND_NAME}_FOUND)
   IF (${THIS_LIB_DEPEND_NAME}_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find ${THIS_LIB_DEPEND_NAME}")
   ENDIF (${THIS_LIB_DEPEND_NAME}_FIND_REQUIRED)
ENDIF (${THIS_LIB_DEPEND_NAME}_FOUND)

if(${THIS_LIB_DEPEND_NAME}_FOUND)
	set(${THIS_LIB_DEPEND_NAME}_LIBRARIES ${${THIS_LIB_DEPEND_NAME}_LIBRARY_DEBUG} ${${THIS_LIB_DEPEND_NAME}_LIBRARY})
	
	include(util.common_make_import_target)
	COMMON_MAKE_IMPORT_TARGET(${THIS_LIB_DEPEND_NAME} 
		${${THIS_LIB_DEPEND_NAME}_INCLUDE_DIR}
		${${THIS_LIB_DEPEND_NAME}_LIBRARY_DEBUG}
		${${THIS_LIB_DEPEND_NAME}_LIBRARY}
	)

	mark_as_advanced(
		${THIS_LIB_DEPEND_NAME}_INCLUDE_DIR
		${THIS_LIB_DEPEND_NAME}_LIBRARY
		${THIS_LIB_DEPEND_NAME}_LIBRARY_DEBUG
	)
endif()










