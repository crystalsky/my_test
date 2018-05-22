#
# Try to find GLTOOLS library and include path.
# Once done this will define
#
# GLTOOLS_FOUND
# GLTOOLS_INCLUDE_DIR
# GLTOOLS_LIBRARY
# 

include(FindPkgMacros)

IF (WIN32)
    FIND_PATH( GLTOOLS_INCLUDE_DIR GLTools.h
        PATHS
		"${GLTOOLS_DIR}/include"
		DOC "The directory where GL/GLTOOLS.h resides")
	FIND_LIBRARY( GLTOOLS_LIBRARY
		NAMES GLTools
		PATHS
		"${GLTOOLS_DIR}/lib"
		DOC "The GLTOOLS library")
	FIND_LIBRARY( GLTOOLS_LIBRARY_DEBUG
		NAMES GLToolsd
		PATHS
		"${GLTOOLS_DIR}/lib"
		DOC "The GLTOOLS library")

ELSE (WIN32)
	FIND_PATH( GLTOOLS_INCLUDE_DIR GL/GLTOOLS.h
		/usr/include
		/usr/local/include
		/sw/include
		/opt/local/include
		DOC "The directory where GL/GLTOOLS.h resides")
	FIND_LIBRARY( GLTOOLS_LIBRARY
		NAMES GLTOOLS GLTOOLS
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		DOC "The GLTOOLS library")
ENDIF (WIN32)


include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLTOOLS 
	REQUIRED_VARS 
	GLTOOLS_LIBRARY 
	GLTOOLS_LIBRARY_DEBUG
	GLTOOLS_INCLUDE_DIR
)

if(GLTOOLS_FOUND)
	set(GLTOOLS_LIBRARIES ${GLTOOLS_LIBRARY})
	
	include(util.common_make_import_target)
	COMMON_MAKE_IMPORT_TARGET(GLTOOLS 
		${GLTOOLS_INCLUDE_DIR}
		${GLTOOLS_LIBRARY_DEBUG}
		${GLTOOLS_LIBRARY}
	)

	mark_as_advanced(
		GLTOOLS_INCLUDE_DIR
		GLTOOLS_LIBRARY
		GLTOOLS_LIBRARY_DEBUG
	)
endif()


