# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#.rst:
# FindRTI
# -------
#
# Try to find M&S HLA RTI libraries
#
# This module finds if any HLA RTI is installed and locates the standard
# RTI include files and libraries.
#
# RTI is a simulation infrastructure standardized by IEEE and SISO.  It
# has a well defined C++ API that assures that simulation applications
# are independent on a particular RTI implementation.
#
# ::
#
#   http://en.wikipedia.org/wiki/Run-Time_Infrastructure_(simulation)
#
#
#
# This code sets the following variables:
#
# ::
#
#   RTI_INCLUDE_DIR = the directory where RTI includes file are found
#   RTI_LIBRARIES = The libraries to link against to use RTI
#   RTI_DEFINITIONS = -DRTI_USES_STD_FSTREAM
#   RTI_FOUND = Set to FALSE if any HLA RTI was not found
#
#
#
# Report problems to <certi-devel@nongnu.org>
set(THIS_LIB_DEPEND_NAME RTI)

GET_DEPENDS_DIR(${THIS_LIB_DEPEND_NAME} ${THIS_LIB_DEPEND_NAME}_SEARCH_FOLDERS)
#MESSAGE(FATAL_ERROR "FOLDERS:${${THIS_LIB_DEPEND_NAME}_SEARCH_FOLDERS}")

include(util.common_find_path)
COMMON_FIND_PATH_NORMAL(${THIS_LIB_DEPEND_NAME}
  RTI.hh
PATHS
    ${${THIS_LIB_DEPEND_NAME}_SEARCH_FOLDERS}
PATH_SUFFIXES 
    include
    include/HLA13
)

#MESSAGE(FATAL_ERROR ${${THIS_LIB_DEPEND_NAME}_SEARCH_FOLDERS})
SET(_search_release_rti_list      libRTI-NG)
SET(_search_debug_rti_list        libRTI-NGd)
SET(_search_release_fedtime_list  fedtime)
SET(_search_debug_fedtime_list    fedtimed)

IF(NOT CMAKE_CL_64)
  SET(dir_suffixes lib/vc100)
ELSE()
  SET(dir_suffixes lib/vc100_64)
ENDIF()

#MESSAGE(FATAL_ERROR "${dir_suffixes}")
find_library(${THIS_LIB_DEPEND_NAME}_LIBRARY
  NAMES ${_search_release_rti_list}
  PATHS ${${THIS_LIB_DEPEND_NAME}_SEARCH_FOLDERS}/${dir_suffixes}
)

find_library(${THIS_LIB_DEPEND_NAME}_LIBRARY_DEBUG
  NAMES ${_search_debug_rti_list}
  PATHS ${${THIS_LIB_DEPEND_NAME}_SEARCH_FOLDERS}
  PATH_SUFFIXES ${dir_suffixes}
)

find_library(${THIS_LIB_DEPEND_NAME}_FEDTIME_LIBRARY
  NAMES ${_search_release_fedtime_list}
  PATHS ${${THIS_LIB_DEPEND_NAME}_SEARCH_FOLDERS}
  PATH_SUFFIXES ${dir_suffixes}/newtime
)

find_library(${THIS_LIB_DEPEND_NAME}_FEDTIME_LIBRARY_DEBUG
  NAMES ${_search_debug_fedtime_list}
  PATHS ${${THIS_LIB_DEPEND_NAME}_SEARCH_FOLDERS}
  PATH_SUFFIXES ${dir_suffixes}/newtime
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
      MESSAGE(STATUS "Found ${THIS_LIB_DEPEND_NAME}: ${${THIS_LIB_DEPEND_NAME}_LIBRARY}")
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

  COMMON_MAKE_IMPORT_TARGET_BASE(${THIS_LIB_DEPEND_NAME}
    ${THIS_LIB_DEPEND_NAME}_FEDTIME
    ${${THIS_LIB_DEPEND_NAME}_INCLUDE_DIR}
    ${${THIS_LIB_DEPEND_NAME}_FEDTIME_LIBRARY}
    ${${THIS_LIB_DEPEND_NAME}_FEDTIME_LIBRARY_DEBUG}
  )

	mark_as_advanced(
		${THIS_LIB_DEPEND_NAME}_INCLUDE_DIR
		${THIS_LIB_DEPEND_NAME}_LIBRARY
    ${THIS_LIB_DEPEND_NAME}_LIBRARY_DEBUG
    ${THIS_LIB_DEPEND_NAME}_FEDTIME_LIBRARY
    ${THIS_LIB_DEPEND_NAME}_FEDTIME_LIBRARY_DEBUG
  )
  
endif()