#//////////////////////////////////////////////////////////
#设置依赖库前缀名称（CMAKE上显示的名称）
SET(THIS_LIB_DEPEND_NAME XX)
#设置库名称(库的名称（不含lib）)
SET(THIS_LIB_HEAD_NAME XX)
#设置要查找的头文件名
SET(THIS_LIB_HEADER_FILE_NAME "XX")
#//////////////////////////////////////////////////////////
SET(THIS_LIB_SERACH_PATH 
${${THIS_LIB_DEPEND_NAME}_ROOT}
${${THIS_LIB_DEPEND_NAME}_DIR}
${${THIS_LIB_DEPEND_NAME}_ROOT_PATH}
$ENV{${THIS_LIB_DEPEND_NAME}_ROOT}
$ENV{${THIS_LIB_DEPEND_NAME}_DIR}
$ENV{${THIS_LIB_DEPEND_NAME}_ROOT_PATH})

include(${CMAKE_CURRENT_LIST_DIR}/macrofunc/macro_find_dependency.cmake)
FIND_DEPENDENCY(
${THIS_LIB_DEPEND_NAME} 
${THIS_LIB_HEADER_FILE_NAME} 
${THIS_LIB_HEAD_NAME} 
${THIS_LIB_SERACH_PATH} 
"D" 
"")

IF(NOT ${THIS_LIB_DEPEND_NAME}_FOUND)
MESSAGE(FATAL_ERROR "--${THIS_LIB_DEPEND_NAME} not found")
ENDIF(NOT ${THIS_LIB_DEPEND_NAME}_FOUND)