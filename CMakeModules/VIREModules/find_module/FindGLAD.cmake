#
# Try to find GLAD library and include path.
# Once done this will define
#
# GLAD_FOUND
# GLAD_INCLUDE_DIR
# GLAD_LIBRARY
# 

include(FindPkgMacros)

# get home path
#getenv_path(GLAD_HOME)

IF (WIN32)
    FIND_PATH( GLAD_INCLUDE_DIR glad/GLAD.h
        PATHS
		"${GLAD_DIR}/include"
		DOC "The directory where GL/GLAD.h resides")
	FIND_LIBRARY( GLAD_LIBRARY
		NAMES glad
		PATHS
		$ENV{PROGRAMFILES}/GLAD/lib
		${PROJECT_SOURCE_DIR}/src/nvgl/GLAD/bin
		${PROJECT_SOURCE_DIR}/src/nvgl/GLAD/lib
		"${ENV_GLAD_HOME}/lib"
		"${GLAD_DIR}/lib"
		DOC "The GLAD library")
	FIND_LIBRARY( GLAD_LIBRARY_DEBUG
		NAMES gladd
		PATHS
		$ENV{PROGRAMFILES}/GLAD/lib
		${PROJECT_SOURCE_DIR}/src/nvgl/GLAD/bin
		${PROJECT_SOURCE_DIR}/src/nvgl/GLAD/lib
		"${ENV_GLAD_HOME}/lib"
		"${GLAD_DIR}/lib"
		DOC "The GLAD library")
ELSE (WIN32)
	FIND_PATH( GLAD_INCLUDE_DIR GL/GLAD.h
		/usr/include
		/usr/local/include
		/sw/include
		/opt/local/include
		DOC "The directory where GL/GLAD.h resides")
	FIND_LIBRARY( GLAD_LIBRARY
		NAMES GLAD GLAD
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		DOC "The GLAD library")
ENDIF (WIN32)


include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLAD 
	REQUIRED_VARS 
	GLAD_LIBRARY 
	GLAD_LIBRARY_DEBUG
	GLAD_INCLUDE_DIR
)

if (GLAD_FOUND)
 
  set( GLAD_LIBRARIES
    ${GLAD_LIBRARY}
    )

  set(GLAD_LIBRARIES ${GLAD_LIBRARY_DEBUG} ${GLAD_LIBRARY})
	
	include(util.common_make_import_target)
	COMMON_MAKE_IMPORT_TARGET(GLAD 
		${GLAD_INCLUDE_DIR}
		${GLAD_LIBRARY_DEBUG}
		${GLAD_LIBRARY}
	)
endif()

mark_as_advanced(
  GLAD_INCLUDE_DIR
  GLAD_LIBRARY
  GLAD_LIBRARY_DEBUG
)
