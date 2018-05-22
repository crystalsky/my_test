#===============================================
#���ظ���������
if(UTILITYMACRO_INCLUDED)
    return()
endif()
set(UTILITYMACRO_INCLUDED TRUE)
#===============================================
#import include, don't remove it
#if remove, cmake will be failed
#...many...many...error
#include(_this_module_path_dirs)
#=================Include Utils==================
include(CMakePrintHelpers)
include(_util_include)
include(_macro_vire_include)
include(_macro_utilities_include)
#===============================================
MACRO(LINK_INTERNAL TRGTNAME)
    IF(${CMAKE_MAJOR_VERSION} EQUAL 2 AND ${CMAKE_MINOR_VERSION} GREATER 4)
        TARGET_LINK_LIBRARIES(${TRGTNAME} ${ARGN})
    ELSE(${CMAKE_MAJOR_VERSION} EQUAL 2 AND ${CMAKE_MINOR_VERSION} GREATER 4)
        FOREACH(LINKLIB ${ARGN})
            IF(MSVC AND OSG_MSVC_VERSIONED_DLL)
                #when using versioned names, the .dll name differ from .lib name, there is a problem with that:
                #CMake 2.4.7, at least seem to use PREFIX instead of IMPORT_PREFIX  for computing linkage info to use into projects,
                # so we full path name to specify linkage, this prevent automatic inferencing of dependencies, so we add explicit depemdencies
                #to library targets used
                TARGET_LINK_LIBRARIES(${TRGTNAME} optimized "${OUTPUT_LIBDIR}/${LINKLIB}${CMAKE_RELEASE_POSTFIX}.lib" debug "${OUTPUT_LIBDIR}/${LINKLIB}${CMAKE_DEBUG_POSTFIX}.lib")
                ADD_DEPENDENCIES(${TRGTNAME} ${LINKLIB})
            ELSE(MSVC AND OSG_MSVC_VERSIONED_DLL)
                TARGET_LINK_LIBRARIES(${TRGTNAME} optimized "${LINKLIB}${CMAKE_RELEASE_POSTFIX}" debug "${LINKLIB}${CMAKE_DEBUG_POSTFIX}")
            ENDIF(MSVC AND OSG_MSVC_VERSIONED_DLL)
        ENDFOREACH(LINKLIB)
    ENDIF(${CMAKE_MAJOR_VERSION} EQUAL 2 AND ${CMAKE_MINOR_VERSION} GREATER 4)
ENDMACRO(LINK_INTERNAL TRGTNAME)

MACRO(LINK_EXTERNAL TRGTNAME)
    FOREACH(LINKLIB ${ARGN})
        TARGET_LINK_LIBRARIES(${TRGTNAME} "${LINKLIB}" )
    ENDFOREACH(LINKLIB)
ENDMACRO(LINK_EXTERNAL TRGTNAME)


macro(MacroEmptyExternalProject proj dependencies)
 
  ExternalProject_Add(${proj}
    DOWNLOAD_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    DEPENDS
      ${dependencies}
   )
endmacro()

MACRO(READ_GCC_VERSION)
	if (CMAKE_COMPILER_IS_GNUCC)
		execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion
					OUTPUT_VARIABLE GCC_VERSION)
		string(REGEX MATCHALL "[0-9]+" GCC_VERSION_COMPONENTS ${GCC_VERSION})
		list(GET GCC_VERSION_COMPONENTS 0 GCC_MAJOR)
		list(GET GCC_VERSION_COMPONENTS 1 GCC_MINOR)
	endif()
ENDMACRO(READ_GCC_VERSION)


 MACRO(GET_HEADERS_EXTENSIONLESS DIR GLOB_PATTERN OUTPUT)
            FILE(GLOB TMP "${DIR}/${GLOB_PATTERN}" )
      #FOREACH(F ${TMP})
            #    MESSAGE(STATUS "header-->${F}<--")
      #ENDFOREACH(F ${TMP})
        FILTER_OUT("${DIR}/CVS" "${TMP}" TMP)
        FILTER_OUT("${DIR}/cvs" "${TMP}" ${OUTPUT})
        FILTER_OUT("${DIR}/.svn" "${TMP}" ${OUTPUT})
ENDMACRO(GET_HEADERS_EXTENSIONLESS DIR GLOB_PATTERN OUTPUT)
   
MACRO(TARGET_LOCATIONS_SET_FILE FILE)
 SET(ACCUM_FILE_TARGETS ${FILE})
 FILE(WRITE ${ACCUM_FILE_TARGETS} "")
ENDMACRO(TARGET_LOCATIONS_SET_FILE FILE)

MACRO(TARGET_LOCATIONS_ACCUM TARGET_NAME)
 IF(ACCUM_FILE_TARGETS)
  IF(EXISTS ${ACCUM_FILE_TARGETS})
    GET_TARGET_PROPERTY(_FILE_LOCATION ${TARGET_NAME} LOCATION)
    FILE(APPEND ${ACCUM_FILE_TARGETS} "${_FILE_LOCATION};")
    #SET(_TARGETS_LIST ${_TARGETS_LIST} "${_FILE_LOCATION}" CACHE INTERNAL "lista dll")
    #MESSAGE("adding target -->${TARGET_NAME}<-- file -->${_FILE_LOCATION}<-- to list -->${_TARGETS_LIST}<--")
    #SET(ACCUM_FILE_TARGETS ${ACCUM_FILE_TARGETS} ${_FILE_LOCATION})
  ENDIF(EXISTS ${ACCUM_FILE_TARGETS})
 ENDIF(ACCUM_FILE_TARGETS)
ENDMACRO(TARGET_LOCATIONS_ACCUM TARGET_NAME)

MACRO(TARGET_LOCATIONS_GET_LIST _VAR)
 IF(ACCUM_FILE_TARGETS)
  IF(EXISTS ${ACCUM_FILE_TARGETS})
      FILE(READ ${ACCUM_FILE_TARGETS} ${_VAR})    
  ENDIF(EXISTS ${ACCUM_FILE_TARGETS})
 ENDIF(ACCUM_FILE_TARGETS)
ENDMACRO(TARGET_LOCATIONS_GET_LIST _VAR)


# Try to ascertain the version...
MACRO(FIND_OSG_VERSION)
    IF(OSG_INCLUDE_DIR)

        SET(_osg_Version_file "${OSG_INCLUDE_DIR}/osg/Version")
        IF("${OSG_INCLUDE_DIR}" MATCHES "\\.framework$" AND NOT EXISTS "${_osg_Version_file}")
            SET(_osg_Version_file "${OSG_INCLUDE_DIR}/Headers/Version")
        ENDIF()

        IF(EXISTS "${_osg_Version_file}")
          FILE(READ "${_osg_Version_file}" _osg_Version_contents)
        ELSE()
          SET(_osg_Version_contents "unknown")
        ENDIF()

        STRING(REGEX MATCH ".*#define OSG_VERSION_MAJOR[ \t]+[0-9]+.*"
            _osg_old_defines "${_osg_Version_contents}")
        STRING(REGEX MATCH ".*#define OPENSCENEGRAPH_MAJOR_VERSION[ \t]+[0-9]+.*"
            _osg_new_defines "${_osg_Version_contents}")
        IF(_osg_old_defines)
            STRING(REGEX REPLACE ".*#define OSG_VERSION_MAJOR[ \t]+([0-9]+).*"
                "\\1" _osg_VERSION_MAJOR ${_osg_Version_contents})
            STRING(REGEX REPLACE ".*#define OSG_VERSION_MINOR[ \t]+([0-9]+).*"
                "\\1" _osg_VERSION_MINOR ${_osg_Version_contents})
            STRING(REGEX REPLACE ".*#define OSG_VERSION_PATCH[ \t]+([0-9]+).*"
                "\\1" _osg_VERSION_PATCH ${_osg_Version_contents})
        ELSEIF(_osg_new_defines)
            STRING(REGEX REPLACE ".*#define OPENSCENEGRAPH_MAJOR_VERSION[ \t]+([0-9]+).*"
                "\\1" _osg_VERSION_MAJOR ${_osg_Version_contents})
            STRING(REGEX REPLACE ".*#define OPENSCENEGRAPH_MINOR_VERSION[ \t]+([0-9]+).*"
                "\\1" _osg_VERSION_MINOR ${_osg_Version_contents})
            STRING(REGEX REPLACE ".*#define OPENSCENEGRAPH_PATCH_VERSION[ \t]+([0-9]+).*"
                "\\1" _osg_VERSION_PATCH ${_osg_Version_contents})
        ELSE()
            MESSAGE("[ FindOpenSceneGraph.cmake:${CMAKE_CURRENT_LIST_LINE} ] "
                "Failed to parse version number, please report this as a bug")
        ENDIF()

        SET(OSG_VERSION_MAJOR ${_osg_VERSION_MAJOR})
        SET(OSG_VERSION_MINOR ${_osg_VERSION_MINOR})
        SET(OSG_VERSION_PATCH ${_osg_VERSION_PATCH})

        SET(OPENSCENEGRAPH_VERSION "${_osg_VERSION_MAJOR}.${_osg_VERSION_MINOR}.${_osg_VERSION_PATCH}"
                                    CACHE INTERNAL "The version of OSG which was detected")                
    ENDIF()
ENDMACRO(FIND_OSG_VERSION)

#############################################################

