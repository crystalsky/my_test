#//////////////////////////////////////////////////////////
#设置依赖库前缀名称（CMAKE上显示的名称）
SET(THIS_LIB_DEPEND_NAME QTUI)
#设置库名称(库的名称（不含lib）)
SET(THIS_LIB_HEAD_NAME QtUI)
#设置要查找的头文件名
SET(THIS_LIB_HEADER_FILE_NAME "QtUI_Export.h")
#//////////////////////////////////////////////////////////

include(macro_find_dependency)
FIND_DEPENDENCY_EX(
    ${THIS_LIB_DEPEND_NAME} 
    ${THIS_LIB_HEADER_FILE_NAME} 
    ${THIS_LIB_HEAD_NAME} 
    PATHS ${${THIS_LIB_DEPEND_NAME}_ROOT}
        ${${THIS_LIB_DEPEND_NAME}_DIR}
        ${${THIS_LIB_DEPEND_NAME}_ROOT_PATH}
        $ENV{${THIS_LIB_DEPEND_NAME}_ROOT}
        $ENV{${THIS_LIB_DEPEND_NAME}_DIR}
        $ENV{${THIS_LIB_DEPEND_NAME}_ROOT_PATH}
)

#验证变量合法
include(macro_find_package_handle_standard_args)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(
    ${THIS_LIB_DEPEND_NAME} 
    REQUIRED_VARS ${THIS_LIB_DEPEND_NAME}_INCLUDE_DIR 
    ${THIS_LIB_DEPEND_NAME}_LIBRARY 
    ${THIS_LIB_DEPEND_NAME}_LIBRARY_DEBUG
)

IF(NOT ${THIS_LIB_DEPEND_NAME}_FOUND)
MESSAGE(FATAL_ERROR "--${THIS_LIB_DEPEND_NAME} not found")
ENDIF(NOT ${THIS_LIB_DEPEND_NAME}_FOUND)












