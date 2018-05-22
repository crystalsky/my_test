#//////////////////////////////////////////////////////////
#设置依赖库前缀名称（CMAKE上显示的名称）
SET(LIB_DEPEND_NAME QTXMLOBJECT)
#设置库名称(库的名称（不含lib）)
SET(LIB_BASE_NAME QtXMLObject)
#设置要查找的头文件名
SET(LIB_HEADER_FILE_NAME "QtXMLObject_Export.h")
#//////////////////////////////////////////////////////////
SET(${LIB_DEPEND_NAME}_SERACH_PATHS ${${LIB_DEPEND_NAME}_ROOT}
    ${${LIB_DEPEND_NAME}_DIR}
    ${${LIB_DEPEND_NAME}_ROOT_PATH}
    $ENV{${LIB_DEPEND_NAME}_ROOT}
    $ENV{${LIB_DEPEND_NAME}_DIR}
    $ENV{${LIB_DEPEND_NAME}_ROOT_PATH})
#//////////////////////////////////////////////////////////
FIND_DEPEND_INCLUDE_DIR(
  ${LIB_DEPEND_NAME} 
  ${LIB_HEADER_FILE_NAME}
  PATHS 
  ${${LIB_DEPEND_NAME}_SERACH_PATHS}
)

FIND_DEPEND_LIBRARY(${LIB_DEPEND_NAME} 
	${LIB_BASE_NAME} 
	VERSIONED_LIB
  PATHS 
  	${${LIB_DEPEND_NAME}_SERACH_PATHS}
)
#//////////////////////////////////////////////////////////
#验证变量合法
include(macro_find_package_handle_standard_args)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(
	${LIB_DEPEND_NAME} 
	REQUIRED_VARS ${LIB_DEPEND_NAME}_INCLUDE_DIR 
	${LIB_DEPEND_NAME}_LIBRARY 
	${LIB_DEPEND_NAME}_LIBRARY_DEBUG
)

IF(NOT ${LIB_DEPEND_NAME}_FOUND)
MESSAGE(FATAL_ERROR "--${LIB_DEPEND_NAME} not found")
ENDIF(NOT ${LIB_DEPEND_NAME}_FOUND)











