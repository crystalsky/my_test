# Locate ode
# This module defines
# ODE_LIBRARY
# ODE_FOUND, if false, do not try to link to ode 
# ODE_INCLUDE_DIR, where to find the headers
#
# $ODE_DIR is an environment variable that would
# correspond to the ./configure --prefix=$ODE_DIR
#
# Created by David Guthrie.  Based on code by Robert Osfield 
set(THIS_LIB_DEPEND_NAME ODE)

IF (MSVC11)
	IF (CMAKE_CL_64)
		SET(${THIS_LIB_DEPEND_NAME}_ARCH "vc110/x64")
	ELSE (CMAKE_CL_64)
		SET(${THIS_LIB_DEPEND_NAME}_ARCH "vc110")
	ENDIF (CMAKE_CL_64)
ENDIF (MSVC11)

IF (MSVC71)
	SET(${THIS_LIB_DEPEND_NAME}_ARCH "vc7")
ENDIF (MSVC71)

IF (MSVC60)
	SET(${THIS_LIB_DEPEND_NAME}_ARCH "vc6")
ENDIF (MSVC60)

IF (UNIX)
	SET(${THIS_LIB_DEPEND_NAME}_ARCH "linux")
ENDIF (UNIX)


FIND_PATH(${THIS_LIB_DEPEND_NAME}_INCLUDE_DIR ode/ode.h
    ${${THIS_LIB_DEPEND_NAME}_DIR}/include
    $ENV{${THIS_LIB_DEPEND_NAME}_DIR}/include
    $ENV{${THIS_LIB_DEPEND_NAME}_DIR}
    $ENV{DELTA3D_EXT_DIR}/include
    $ENV{DELTA_ROOT}/ext/inc
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/include
    /usr/include
    /usr/include/cal3d
    /sw/include # Fink
    /opt/local/include # DarwinPorts
    /opt/csw/include # Blastwave
    /opt/include
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OSG_ROOT]/include
    /usr/freeware/include
)


MACRO(FIND_ODE_LIBRARY MYLIBRARY MYLIBRARYNAME)

FIND_LIBRARY(${MYLIBRARY}
    NAMES ${MYLIBRARYNAME}
    PATHS
    ${${THIS_LIB_DEPEND_NAME}_DIR}/lib
    $ENV{${THIS_LIB_DEPEND_NAME}_DIR}/lib
    $ENV{${THIS_LIB_DEPEND_NAME}_DIR}
    ${DELTA3D_EXT_DIR}/lib
    $ENV{DELTA_ROOT}/ext/lib
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/lib
    /usr/lib
    /sw/lib
    /opt/local/lib
    /opt/csw/lib
    /opt/lib
PATH_SUFFIXES
    ${${THIS_LIB_DEPEND_NAME}_ARCH}
)
ENDMACRO()

SET(RELEASE_LIST ode ode_single)
FIND_ODE_LIBRARY(${THIS_LIB_DEPEND_NAME}_LIBRARY "${RELEASE_LIST}")

SET(DEBUG_LIST oded ode_singled)
FIND_ODE_LIBRARY(${THIS_LIB_DEPEND_NAME}_LIBRARY_DEBUG "${DEBUG_LIST}")

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

