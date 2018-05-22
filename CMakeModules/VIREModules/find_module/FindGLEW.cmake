#
# Try to find GLEW library and include path.
# Once done this will define
#
# GLEW_FOUND
# GLEW_INCLUDE_DIR
# GLEW_LIBRARY
# 

include(FindPkgMacros)

IF (WIN32)
    FIND_PATH( GLEW_INCLUDE_DIR GL/glew.h
        PATHS
		"${GLEW_DIR}/include"
		DOC "The directory where GL/GLEW.h resides")
	FIND_LIBRARY( GLEW_LIBRARY
		NAMES glew32
		PATHS
		"${GLEW_DIR}/lib"
		DOC "The GLEW library")

	FIND_LIBRARY( GLEW_LIBRARY_DEBUG
		NAMES glew32d
		PATHS
		"${GLEW_DIR}/lib"
		DOC "The GLEW library")
	
	FIND_LIBRARY( GLEW_LIBRARY_STATIC
		NAMES libglew32
		PATHS
		"${GLEW_DIR}/lib"
		DOC "The GLEW library")
	FIND_LIBRARY( GLEW_LIBRARY_STATIC_DEBUG
		NAMES libglew32d
		PATHS
		"${GLEW_DIR}/lib"
		DOC "The GLEW library")

	
ELSE (WIN32)
	FIND_PATH( GLEW_INCLUDE_DIR GL/GLEW.h
		/usr/include
		/usr/local/include
		/sw/include
		/opt/local/include
		DOC "The directory where GL/GLEW.h resides")
	FIND_LIBRARY( GLEW_LIBRARY
		NAMES GLEW GLEW
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		DOC "The GLEW library")
ENDIF (WIN32)


include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLEW 
	REQUIRED_VARS 
	GLEW_LIBRARY 
	GLEW_INCLUDE_DIR
	GLEW_LIBRARY_STATIC
)

if(GLEW_FOUND)
	set(GLEW_LIBRARIES ${GLEW_LIBRARY})
	
	include(util.common_make_import_target)
	COMMON_MAKE_IMPORT_TARGET_BASE(GLEW GLEW
		${GLEW_INCLUDE_DIR}
		${GLEW_LIBRARY_DEBUG}
		${GLEW_LIBRARY}
	)

	COMMON_MAKE_IMPORT_TARGET_BASE(GLEW GLEW_STATIC
		${GLEW_INCLUDE_DIR}
		${GLEW_LIBRARY_STATIC_DEBUG}
		${GLEW_LIBRARY_STATIC}
	)
endif()

mark_as_advanced(
  GLEW_INCLUDE_DIR
  GLEW_LIBRARY_DEBUG
  GLEW_LIBRARY
  GLEW_LIBRARY_STATIC
  GLEW_LIBRARY_STATIC_DEBUG
)
