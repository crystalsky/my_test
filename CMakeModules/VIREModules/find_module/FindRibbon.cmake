#//////////////////////////////////////////////////////////
#����������ǰ׺���ƣ�CMAKE����ʾ�����ƣ�
SET(THIS_LIB_DEPEND_NAME RIBBON)
#���ÿ�����(������ƣ�����lib��)
SET(THIS_LIB_HEAD_NAME ribbon)
#����Ҫ���ҵ�ͷ�ļ���
SET(THIS_LIB_HEADER_FILE_NAME "ribbon/QtitanRibbon.h")
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

#��֤�����Ϸ�
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








