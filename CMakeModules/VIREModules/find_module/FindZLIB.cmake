###############################################################################
# CMake module to search for ZLIB library
# zlib ???? gzip (GNU zip) ?????????
# 
###############################################################################
#//////////////////////////////////////////////////////////
#设置依赖库前缀名称（CMAKE上显示的名称）
SET(THIS_LIB_DEPEND_NAME ZLIB)
#设置库名称(库的名称（不含lib）)
SET(THIS_LIB_HEAD_NAME zlib)
#设置要查找的头文件名
SET(THIS_LIB_HEADER_FILE_NAME "zlib.h")
#//////////////////////////////////////////////////////////

include(${CMAKE_CURRENT_LIST_DIR}/macrofunc/macro_find_dependency.cmake)
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
include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(
    ${THIS_LIB_DEPEND_NAME} 
    REQUIRED_VARS ${THIS_LIB_DEPEND_NAME}_INCLUDE_DIR 
    ${THIS_LIB_DEPEND_NAME}_LIBRARY 
    ${THIS_LIB_DEPEND_NAME}_LIBRARY_DEBUG
)

IF(NOT ${THIS_LIB_DEPEND_NAME}_FOUND)
MESSAGE(FATAL_ERROR "--${THIS_LIB_DEPEND_NAME} not found")
ENDIF(NOT ${THIS_LIB_DEPEND_NAME}_FOUND)





