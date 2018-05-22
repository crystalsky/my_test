#
# Try to find GLFW library and include path.
# Once done this will define
#
# GLFW_FOUND
# GLFW_INCLUDE_DIR
# GLFW_LIBRARY
# 

include(FindPkgMacros)

# get home path
#getenv_path(GLFW_HOME)

IF (WIN32)
    FIND_PATH( GLFW_INCLUDE_DIR GL/glfw3.h
        PATHS
		"${GLFW_DIR}/include"
		DOC "The directory where GL/GLFW.h resides")
	FIND_LIBRARY( GLFW_LIBRARY
		NAMES GLFW GLFW GLFW32 glfw3 
		PATHS
		"${GLFW_DIR}/lib"
		DOC "The GLFW library")
ELSE (WIN32)
	FIND_PATH( GLFW_INCLUDE_DIR GL/GLFW.h
		/usr/include
		/usr/local/include
		/sw/include
		/opt/local/include
		DOC "The directory where GL/GLFW.h resides")
	FIND_LIBRARY( GLFW_LIBRARY
		NAMES GLFW GLFW
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		DOC "The GLFW library")
ENDIF (WIN32)


include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLFW 
	REQUIRED_VARS 
	GLFW_LIBRARY 
	GLFW_INCLUDE_DIR
)

if(GLFW_FOUND)
	set(GLFW_LIBRARIES ${GLFW_LIBRARY_DEBUG} ${GLFW_LIBRARY})
	
	include(util.common_make_import_target)
	COMMON_MAKE_IMPORT_TARGET(GLFW 
		${GLFW_INCLUDE_DIR}
		${GLFW_LIBRARY}
		${GLFW_LIBRARY}
	)
endif()

mark_as_advanced(
  GLFW_INCLUDE_DIR
  GLFW_LIBRARY
)
