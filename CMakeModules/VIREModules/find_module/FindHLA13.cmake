#//////////////////////////////////////////////////////////
#设置依赖库前缀名称（CMAKE上显示的名称）
SET(THIS_LIB_DEPEND_NAME HLA13)
#设置库名称(库的名称（不含lib）)
# SET(THIS_LIB_HEAD_NAME VRNHLAInterface)
#设置要查找的头文件名
# SET(THIS_LIB_HEADER_FILE_NAME "VRN_HLA_Interface.h")
#//////////////////////////////////////////////////////////

# include(macro_find_dependency)
# FIND_DEPENDENCY_EX(
# 	${THIS_LIB_DEPEND_NAME} 
# 	${THIS_LIB_HEADER_FILE_NAME} 
# 	${THIS_LIB_HEAD_NAME} 
# 	PATHS ${${THIS_LIB_DEPEND_NAME}_ROOT}
# 		${${THIS_LIB_DEPEND_NAME}_DIR}
# 		${${THIS_LIB_DEPEND_NAME}_ROOT_PATH}
# 		$ENV{${THIS_LIB_DEPEND_NAME}_ROOT}
# 		$ENV{${THIS_LIB_DEPEND_NAME}_DIR}
# 		$ENV{${THIS_LIB_DEPEND_NAME}_ROOT_PATH}
# )

find_path(${THIS_LIB_DEPEND_NAME}_INCLUDE_DIR
   NAMES
      fedtime.hh
   PATH_SUFFIXES 
      include/HLA13
      include
      inc
   HINTS
      $ENV{RTI_HOME}
   NO_DEFAULT_PATH
)
MARK_AS_ADVANCED(${THIS_LIB_DEPEND_NAME}_INCLUDE_DIR)

# if (GCC_VERSION)
#   IF (APPLE)
#     SET(PATHLIST 
#         macintel_g++-${GCC_MAJOR}.${GCC_MINOR}
#         macintel_g++-unknown
#         macintel64_g++-${GCC_MAJOR}.${GCC_MINOR}
#         macintel64_g++-unknown
#         darwin_g++-${GCC_MAJOR}.${GCC_MINOR}
#         gcc${GCC_MAJOR}${GCC_MINOR}
#     )
#   ELSE (APPLE)
#     IF (UNIX)
#        SET(PATHLIST    
#           linux_g++-${GCC_MAJOR}.${GCC_MINOR}
#           gcc${GCC_MAJOR}${GCC_MINOR}
#        )
#     ENDIF ()
#   ENDIF ()
# endif()

find_library(${THIS_LIB_DEPEND_NAME}_RTING_LIBRARY
   NAMES
      libRTI-NG
   PATH_SUFFIXES
      vc100
   HINTS
      $ENV{RTI_HOME}/lib
)
MARK_AS_ADVANCED(${THIS_LIB_DEPEND_NAME}_RTING_LIBRARY)

find_library(${THIS_LIB_DEPEND_NAME}_FEDTIME_LIBRARY
   NAMES
      libfedtime
   PATH_SUFFIXES
      vc100/newtime
   HINTS
      $ENV{RTI_HOME}/lib
)
MARK_AS_ADVANCED(${THIS_LIB_DEPEND_NAME}_FEDTIME_LIBRARY)


#验证变量合法
include(macro_find_package_handle_standard_args)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(
	${THIS_LIB_DEPEND_NAME} 
	DEFAULT_MSG
	${THIS_LIB_DEPEND_NAME}_RTING_LIBRARY 
	${THIS_LIB_DEPEND_NAME}_INCLUDE_DIR
	${THIS_LIB_DEPEND_NAME}_FEDTIME_LIBRARY
)

IF(NOT ${THIS_LIB_DEPEND_NAME}_FOUND)
MESSAGE(FATAL_ERROR "--${THIS_LIB_DEPEND_NAME} not found")
ENDIF(NOT ${THIS_LIB_DEPEND_NAME}_FOUND)












