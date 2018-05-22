
#//////////////////////////////////////////////////////////
#设置依赖库前缀名称（CMAKE上显示的名称）
SET(LIB_DEPEND_NAME ICE)
#//////////////////////////////////////////////////////////
SET(${LIB_DEPEND_NAME}_SERACH_PATHS ${${LIB_DEPEND_NAME}_ROOT}
    ${${LIB_DEPEND_NAME}_DIR}
    ${${LIB_DEPEND_NAME}_ROOT_PATH}
    $ENV{${LIB_DEPEND_NAME}_ROOT}
    $ENV{${LIB_DEPEND_NAME}_DIR}
    $ENV{${LIB_DEPEND_NAME}_ROOT_PATH})
#//////////////////////////////////////////////////////////
include(util.common_make_import_target)
#MESSAGE("ICE_FIND_COMPONENTS = ${ICE_FIND_COMPONENTS}")

# MACRO(_MAKE_IMPORT_TARGET DEPNAME SUBDEPNAME)
#   string(TOUPPER ${DEPNAME} _uppered_name)

#   FIND_PACKAGE_HANDLE_STANDARD_ARGS(${_uppered_name}
#             FOUND_VAR ${_uppered_name}_FOUND 	
#             REQUIRED_VARS ${_uppered_name}_INCLUDE_DIR 
#             ${_uppered_name}_LIBRARY 
#             ${_uppered_name}_LIBRARY_DEBUG
#         )

#   IF(NOT ${_uppered_name}_FOUND)
#       MESSAGE(FATAL_ERROR "--${_uppered_name} not found")
#   ENDIF(NOT ${_uppered_name}_FOUND)

#   if(${_uppered_name}_FOUND)
#       set(${_uppered_name}_LIBRARIES ${${_uppered_name}_LIBRARY_DEBUG} ${${_uppered_name}_LIBRARY})
#       COMMON_MAKE_IMPORT_TARGET_BASE(${_uppered_name} ${SUBDEPNAME}
#           ${ICE_${_uppered_name}_INCLUDE_DIR}
#           ${${_uppered_name}_LIBRARY_DEBUG}
#           ${${_uppered_name}_LIBRARY}
#       )

#       mark_as_advanced(
#         ${_uppered_name}_INCLUDE_DIR
#         ${_uppered_name}_LIBRARY_DEBUG
#         ${_uppered_name}_LIBRARY
#       )
#   endif()
# ENDMACRO()

#================================================================
FIND_DEPEND_INCLUDE_DIR(
  ${LIB_DEPEND_NAME} 
  Ice/Ice.h 
  PATHS 
  ${${LIB_DEPEND_NAME}_SERACH_PATHS}
)

FIND_DEPEND_LIBRARY(ICE ice VERSIONED_LIB
  PATHS 
  ${${LIB_DEPEND_NAME}_SERACH_PATHS}
)

COMMON_MAKE_IMPORT_TARGET_BASE(ICE ICE
    ${ICE_INCLUDE_DIR}
    ${ICE_LIBRARY_DEBUG}
    ${ICE_LIBRARY}
)
#================================================================
FIND_DEPEND_LIBRARY(ICEUTIL iceutil VERSIONED_LIB 
  PATHS 
  ${${LIB_DEPEND_NAME}_SERACH_PATHS}
)

COMMON_MAKE_IMPORT_TARGET_BASE(ICE ICEUTIL
    ${ICE_INCLUDE_DIR}
    ${ICEUTIL_LIBRARY_DEBUG}
    ${ICEUTIL_LIBRARY}
)
#================================================================

FIND_DEPEND_LIBRARY(ICEXML icexml VERSIONED_LIB 
  PATHS 
  ${${LIB_DEPEND_NAME}_SERACH_PATHS}
)

COMMON_MAKE_IMPORT_TARGET_BASE(ICE ICEXML
  ${ICE_INCLUDE_DIR}
  ${ICEXML_LIBRARY_DEBUG}
  ${ICEXML_LIBRARY}
)
#================================================================
FIND_DEPEND_LIBRARY(ICESSL icessl VERSIONED_LIB 
  PATHS 
  ${${LIB_DEPEND_NAME}_SERACH_PATHS}
)

COMMON_MAKE_IMPORT_TARGET_BASE(ICE ICESSL
  ${${LIB_DEPEND_NAME}_INCLUDE_DIR}
  ${${LIB_DEPEND_NAME}_LIBRARY_DEBUG}
  ${${LIB_DEPEND_NAME}_LIBRARY}
)
#================================================================
FIND_DEPEND_LIBRARY(ICEGRID icegrid VERSIONED_LIB 
  PATHS 
  ${${LIB_DEPEND_NAME}_SERACH_PATHS}
)

COMMON_MAKE_IMPORT_TARGET_BASE(ICE ICEGRID
  ${ICE_INCLUDE_DIR}
  ${ICEGRID_LIBRARY_DEBUG}
  ${ICEGRID_LIBRARY}
)
#================================================================
FIND_DEPEND_LIBRARY(ICESTORM icestorm VERSIONED_LIB 
  PATHS 
  ${${LIB_DEPEND_NAME}_SERACH_PATHS}
)

FIND_DEPEND_LIBRARY(ICESTORMSERVICE icestormservice VERSIONED_LIB 
  PATHS 
  ${${LIB_DEPEND_NAME}_SERACH_PATHS}
)


#================================================================
FIND_DEPEND_LIBRARY(ICEDB icedb VERSIONED_LIB 
  PATHS 
  ${${LIB_DEPEND_NAME}_SERACH_PATHS}
)

COMMON_MAKE_IMPORT_TARGET_BASE(ICE ICEDB
  ${ICE_INCLUDE_DIR}
  ${ICEDB_LIBRARY_DEBUG}
  ${ICEDB_LIBRARY}
)

FIND_DEPEND_LIBRARY(ICEBOX icebox VERSIONED_LIB 
  PATHS 
  ${${LIB_DEPEND_NAME}_SERACH_PATHS}
)

FIND_DEPEND_LIBRARY(ICEPATCH2 icepatch2 VERSIONED_LIB 
  PATHS 
  ${${LIB_DEPEND_NAME}_SERACH_PATHS}
)

#打包
IF(CMAKE_BUILD_TYPE MATCHES Debug)
    FILE(GLOB ZCHX_ICE_DLL_DEBUG "${ICE_PATH}/bin/debug/*.dll")
    INSTALL(FILES ${ZCHX_ICE_DLL_DEBUG} DESTINATION bin)
    
ELSE(CMAKE_BUILD_TYPE MATCHES Debug)

    FILE(GLOB ZCHX_ICE_DLL_RELEASE "${ICE_PATH}/bin/release/*.dll")
    INSTALL(FILES ${ZCHX_ICE_DLL_RELEASE} DESTINATION bin)
    
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)
