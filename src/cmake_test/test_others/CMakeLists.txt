###########################################################################
SET(LIB_NAME cmake_test_lib)

#===================================================
BEGIN_LIB(${LIB_NAME})

#===================================================
# 定义项目版本
VERSIONED_LIB(${LIB_NAME} 1 0 0 0)

#===================================================
#导出头文件、插件生成
ADD_DEFINITIONS(-D${LIB_NAME}_LIB -D${LIB_NAME}_LIBRARY)

#===================================================
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)

#===================================================
# 查找依赖库

#===================================================
#OK1
#MAKE_CLASS_FILES1(${LIB_NAME} 
	#EXPORT 
	#HEADER_DIR_PATH "${PROJECT_SOURCE_DIR}/include/${LIB_NAME}" 
	#A B C)
#OK2
#MAKE_CLASS_FILES2(${LIB_NAME} 
	#EXPORT 
	#HEADER_DIR_PATH "${PROJECT_SOURCE_DIR}/include/${LIB_NAME}" 
	#A2 B2 C2)
#===================================================
#OK1
#MAKE_CLASS_FILES1(${LIB_NAME} D E F)
#OK2
#MAKE_CLASS_FILES2(${LIB_NAME} D2 E2 F2)
#===================================================
#OK1
#MAKE_CLASS_FILES1(${LIB_NAME} 
	#EXPORT 
	#Q_CLASS 
	#HEADER_DIR_PATH "${PROJECT_SOURCE_DIR}/include/${LIB_NAME}" 
	#AQ BQ CQ)
#OK2
#MAKE_CLASS_FILES2(${LIB_NAME} 
	#EXPORT 
	#Q_CLASS 
	#HEADER_DIR_PATH "${PROJECT_SOURCE_DIR}/include/${LIB_NAME}" 
	#AQ2 BQ2 CQ2)
#===================================================
#OK1
#MAKE_CLASS_FILES1(${LIB_NAME} 
	#Q_CLASS DQ EQ FQ)
#OK2
#MAKE_CLASS_FILES2(${LIB_NAME} 
	#Q_CLASS DQ2 EQ2 FQ2)
#===================================================
#OK1
#MAKE_CLASS_FILES1(${LIB_NAME} 
#	EXPORT 
#	Q_CLASS 
#	PARENT QWidget 
#	HEADER_DIR_PATH "${PROJECT_SOURCE_DIR}/include/${LIB_NAME}" 
#	AWidget BWidget CWidget)
##OK2
#MAKE_CLASS_FILES2(${LIB_NAME} 
#	EXPORT 
#	Q_CLASS 
#	PARENT QWidget 
#	HEADER_DIR_PATH "${PROJECT_SOURCE_DIR}/include/${LIB_NAME}" 
#	AWidget2 BWidget2 CWidget2)
##===================================================
##OK1
#MAKE_CLASS_FILES1(${LIB_NAME} 
#	Q_CLASS 
#	PARENT QWidget 
#	AWidgetInner BWidgetInner CWidgetInner)
##OK2
#MAKE_CLASS_FILES2(${LIB_NAME} 
#	Q_CLASS 
#	PARENT QWidget 
#	AWidgetInner2 BWidgetInner2 CWidgetInner2)
##===================================================
##OK1
#MAKE_CLASS_FILES1(${LIB_NAME} 
#	EXPORT 
#	Q_CLASS 
#	PARENT QDialog 
#	HEADER_DIR_PATH "${PROJECT_SOURCE_DIR}/include/${LIB_NAME}" 
#	ADialog BDialog CDialog)
##OK2
#MAKE_CLASS_FILES2(${LIB_NAME} 
#	EXPORT 
#	Q_CLASS 
#	PARENT QDialog 
#	HEADER_DIR_PATH "${PROJECT_SOURCE_DIR}/include/${LIB_NAME}" 
#	ADialog2 BDialog2 CDialog2)
##===================================================
##OK1
#MAKE_CLASS_FILES1(${LIB_NAME} 
#	Q_CLASS 
#	PARENT QDialog 
#	ADialogInner BDialogInner CDialogInner)
##OK2
#MAKE_CLASS_FILES2(${LIB_NAME} 
#	Q_CLASS 
#	PARENT QDialog 
#	ADialogInner2 BDialogInner2 CDialogInner2)
##===================================================
##OK1
#MAKE_CLASS_FILES1(${LIB_NAME} 
#	EXPORT 
#	Q_CLASS 
#	PARENT QDialog 
#	HEADER_DIR_PATH "${PROJECT_SOURCE_DIR}/include/${LIB_NAME}" 
#	SUB_DIR_NAME "Sub_A" 
#	Sub_A_Dialog1)
##OK2
#MAKE_CLASS_FILES2(${LIB_NAME} 
#	EXPORT 
#	Q_CLASS 
#	PARENT QDialog 
#	HEADER_DIR_PATH "${PROJECT_SOURCE_DIR}/include/${LIB_NAME}" 
#	SUB_DIR_NAME "Sub_A" 
#	Sub_A_Dialog12)
##===================================================
##OK1
#MAKE_CLASS_FILES1(${LIB_NAME} 
#	Q_CLASS 
#	PARENT QDialog 
#	SUB_DIR_NAME "Sub_B" 
#	Sub_A_DialogInner_1)
##OK2
#MAKE_CLASS_FILES2(${LIB_NAME} 
#	Q_CLASS 
#	PARENT QDialog 
#	SUB_DIR_NAME "Sub_B" 
#	Sub_A_DialogInner_12)
#===================================================
#===================================================
#设置UI资源
FILE(GLOB ${LIB_NAME}_QT_UIS "*.ui")

# 设置图片资源
FILE(GLOB ${LIB_NAME}_QT_RCS "*.qrc")

# 设置h代码
FILE(GLOB ${LIB_NAME}_HEADERS "*.h" "${PROJECT_SOURCE_DIR}/include/${LIB_NAME}/*.h")

# 设置cpp代码
FILE(GLOB ${LIB_NAME}_SRCS "*.cpp")

#===================================================
#查找子目录文件
TARGET_SERACH_SUB_DIRS_FILES(${LIB_NAME} 
	HEADER_DIR_PATH "${PROJECT_SOURCE_DIR}/include/${LIB_NAME}"
	SUB_DIRS Sub_A)
	
TARGET_SERACH_SUB_DIRS_FILES(${LIB_NAME} 
	SUB_DIRS Sub_B)	
#VIRE_TARGET_SERACH_SUB_DIRS_FILES(${LIB_NAME} 
#	Sub_A 
#	PlatProperty 
#	PropertyWidget 
#	PathLineEditor
#	DeviceModelView
#)

#===================================================
#Qt处理UI和QRC文件
VIRE_TARGET_PROCESS_QT_RESOURCES_UIS(${LIB_NAME})

#===================================================
INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}/include/${LIB_NAME}
)

#===================================================
SET(_LIB_HEADER 
	${${LIB_NAME}_UI_HDRS}
	${${LIB_NAME}_QT_UIS}
	${${LIB_NAME}_HEADERS}
)

SET(_LIB_CPP 		
	${VERSIONED_LIB_RC} 
	${${LIB_NAME}_SRCS}
	${${LIB_NAME}_RC_SRCS}
	${${LIB_NAME}_QT_RCS}
)

ADD_LIBRARY(${LIB_NAME} SHARED
	${_LIB_HEADER}
	${_LIB_CPP}
)

#===================================================	
 #增加Link依赖包

LINK_WITH_VARIABLES(${LIB_NAME} 
	
)

#ADD_DEPENDENCIES(${LIB_NAME} Earth2DPlugin)

TARGET_LINK_LIBRARIES(${LIB_NAME}
	
)

IF ( Qt5Widgets_FOUND )
    qt5_use_modules( ${LIB_NAME} Gui Widgets quick OpenGL Xml)
	LINK_INTERNAL(${LIB_NAME})
ELSE(Qt5Widgets_FOUND)   
	TARGET_LINK_LIBRARIES(${LIB_NAME}
	${QT_LIBRARIES} 
	${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTOPENGL_LIBRARY}
	${QT_QTXML_LIBRARY}
)
ENDIF( Qt5Widgets_FOUND )

#===================================================
#文件目录分组
VIRE_TARGET_SOURCE_GROUP(${LIB_NAME})

#===================================================
# 设置项目标签.
VIRE_SET_TARGET_PROPERTIES_LABEL_FOLDER(${LIB_NAME} "CMake_Test")

#===================================================
#输出到上级目录，取消debug, release 目录
VIRE_SET_TARGET_PROPERTIES_OUTPUT_NORMAL(${LIB_NAME})

#===================================================
#安装
INSTALL(CODE "MESSAGE(\"Installing utils ${LIB_NAME}  ...\")")

##########################################################################################################


MACRO(OPTION_TEST_NAME name on_off)
	OPTION(_TEST_CMAKE_${name} "Test CMake Function: ${name}" ${on_off})
ENDMACRO()




#=======================================
FUNCTION(test_function ar1 ar2)
	SET(${ar1} "abc" PARENT_SCOPE)
	SET(${ar2} "def" PARENT_SCOPE)
ENDFUNCTION(test_function)

test_function(bb aa)
MESSAGE("test_function: ${bb} ${aa}")
#=======================================
OPTION_TEST_NAME(cmake_file OFF)
if(_TEST_CMAKE_cmake_file)
	file(TIMESTAMP ./main.cpp TT)
	MESSAGE("File TIMESTAMP: ${TT}")
	STRING(TIMESTAMP "%Y-%m-%dT%H:%M:%S" FS)
	MESSAGE("File TIMESTAMP: ${FS}")
endif()

#=======================================
macro(test_cmake_parse_arguments name)
	set(options MSVC_VERSION)
	set(oneValueArgs PLATFORM BIT)
	set(multiValueArgs)
	cmake_parse_arguments(${name} 
	"${options}" 
	"${oneValueArgs}" 
	"${multiValueArgs}" ${ARGN} )

	
	#MESSAGE(STATUS "After cmake_parse_arguments:")
	#MESSAGE(STATUS " ${name}_MSVC_VERSION:${${name}_MSVC_VERSION}")
	#MESSAGE(STATUS " ${name}_PLATFORM:${${name}_PLATFORM}")
	#MESSAGE(STATUS " ${name}_BIT:${${name}_BIT}")
	#MESSAGE(STATUS " ${name}_UNPARSED_ARGUMENTS:${${name}_UNPARSED_ARGUMENTS}")
endmacro()

OPTION_TEST_NAME(cmake_parse_arguments OFF)
if(_TEST_CMAKE_cmake_parse_arguments)
	test_cmake_parse_arguments(_My_Find PLATFORM WIN32 MSVC_VERSION BIT x86 )
endif()

OPTION_TEST_NAME(target_property OFF)
if(_TEST_CMAKE_target_property)
	if (NOT TARGET My::Target)
	 add_library(My::Target SHARED IMPORTED)
	 set_property(TARGET My::Target PROPERTY
      YY_1 ${QT_INCLUDES})
	get_property(SS TARGET My::Target PROPERTY	YY_1)
	MESSAGE("SS===${SS}")
	#_check_file_exists("ABC")
	endif()
endif()

OPTION_TEST_NAME(other ON)
if(_TEST_CMAKE_other)
	MESSAGE("=======================List============================")
macro(_check_file_exists file)
    if(NOT EXISTS "${file}" )
        message(FATAL_ERROR "The imported target \"Qt5::Core\" references the file
   \"${file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
    endif()
endmacro()
MESSAGE("=======================List============================")

MESSAGE("=======================List============================")

 message(STATUS "The imported target  references the file
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
but not all the files it references.")

MESSAGE("=======================List============================")
set(mylistval )
list(APPEND mylistval "1")
list(APPEND mylistval "2")
list(APPEND mylistval "1")
list(APPEND mylistval "1")

MESSAGE("mylistval:${mylistval}")

list(LENGTH mylistval listlen)
MESSAGE("LENGTH:${listlen}")

list(REMOVE_DUPLICATES mylistval)

MESSAGE("mylistval:${mylistval}")

list(LENGTH mylistval listlen)
MESSAGE("LENGTH:${listlen}")



MESSAGE("========================================================")


set(my_if_val_1 1)

if(my_if_val_1)
MESSAGE(STATUS "my_if_val_1 == ${my_if_val_1}")
endif()

if(my_if_val_1 STREQUAL "1")
MESSAGE(STATUS "my_if_val_1 == ${my_if_val_1}")
endif()


if(NOT ${my_if_val_2})
MESSAGE(STATUS "my_if_val_2 is Empty")
endif()

if(my_if_val_2 STREQUAL "")
MESSAGE(STATUS "my_if_val_2 == ${my_if_val_2}")
endif()


set(TEST_FILE "log.txt")
add_custom_command(OUTPUT  ${TEST_FILE}
  COMMAND echo "Generating log.txt file..."
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_FILE} ${TEST_FILE}
  COMMENT  "This is a test"
 )
add_custom_target(Test1 ALL DEPENDS ${TEST_FILE})


add_custom_command(TARGET Test1
  PRE_BUILD 
  COMMAND echo "executing a fake command"
  COMMENT "This command will be executed before building target Test1"
 )




#CMake系统变量打印
MESSAGE("CMAKE_CURRENT_LIST_FILE:${CMAKE_CURRENT_LIST_FILE}")
MESSAGE("CMAKE_CURRENT_LIST_DIR:${CMAKE_CURRENT_LIST_DIR}")
MESSAGE("CMAKE_MODULE_PATH:${CMAKE_MODULE_PATH}")
MESSAGE("PROJECT_SOURCE_DIR:${PROJECT_SOURCE_DIR}")
MESSAGE("PROJECT_BINARY_DIR:${PROJECT_BINARY_DIR}")
MESSAGE("CMAKE_SIZEOF_VOID_P :${CMAKE_SIZEOF_VOID_P}")
#####################################################################
SET(cmk_1_ON ON CACHE BOOL "bool Var")
SET(cmk_2_OFF OFF CACHE BOOL "bool Var")

IF(cmk_1_ON)
MESSAGE( STATUS "VAR_1_ON:${cmk_1_ON}" )
ENDIF(cmk_1_ON)

FILE(GLOB THIS_CPP_FILE "*.cpp")
MESSAGE( STATUS "THIS_CPP_FILE:${THIS_CPP_FILE}" )

SET(cmk_MY_FILE "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp" CACHE PATH "")
MESSAGE( STATUS "MY_FILE:${cmk_MY_FILE}" )

SET(TEST_3RDPARTY_DIR "${PARENT_DIR}/3rdparty")
#MESSAGE( STATUS "TEST_3RDPARTY_DIR:${TEST_3RDPARTY_DIR}" )
SET(ACTUAL_3RDPARTY_DIR "${TEST_3RDPARTY_DIR}" CACHE PATH "Location of 3rdparty dependencies")
SET(ACTUAL_3DPARTY_DIR "${ACTUAL_3RDPARTY_DIR}")

#####################################################################


#####################################################################
#GET_FILENAME_COMPONENT
GET_FILENAME_COMPONENT(GET_FILENAME_COMPONENT_VAL ${cmk_MY_FILE}  NAME)
MESSAGE( STATUS "GET_FILENAME_COMPONENT_VAL: Name ${GET_FILENAME_COMPONENT_VAL}" )

GET_FILENAME_COMPONENT(GET_FILENAME_COMPONENT_VAL ${cmk_MY_FILE}  PATH)
MESSAGE( STATUS "GET_FILENAME_COMPONENT_VAL: Name ${GET_FILENAME_COMPONENT_VAL}" )

GET_FILENAME_COMPONENT(GET_FILENAME_COMPONENT_VAL ${cmk_MY_FILE}   EXT)
MESSAGE( STATUS "GET_FILENAME_COMPONENT_VAL: EXT ${GET_FILENAME_COMPONENT_VAL}" )

GET_FILENAME_COMPONENT(GET_FILENAME_COMPONENT_VAL ${cmk_MY_FILE}   NAME_WE)
MESSAGE( STATUS "GET_FILENAME_COMPONENT_VAL: NAME_WE ${GET_FILENAME_COMPONENT_VAL}" )
GET_FILENAME_COMPONENT(GET_FILENAME_COMPONENT_VAL ${cmk_MY_FILE}   ABSOLUTE)
MESSAGE( STATUS "GET_FILENAME_COMPONENT_VAL: ABSOLUTE ${GET_FILENAME_COMPONENT_VAL}" )

GET_FILENAME_COMPONENT(GET_FILENAME_COMPONENT_VAL ${cmk_MY_FILE}    REALPATH)
MESSAGE( STATUS "GET_FILENAME_COMPONENT_VAL:  REALPATH ${GET_FILENAME_COMPONENT_VAL}" )
#####################################################################

GET_FILENAME_COMPONENT(PARENT_DIR ${PROJECT_SOURCE_DIR}  PATH)


##########################
SET(OSG_3RDPARTY_DIR "H:/SDKs/3rdParty" )
#include(${CMAKE_MODULE_PATH}/macrofunc/macro_find_dependency.cmake)
#FIND_DEPENDENCY(GDAL gdal.h "gdal;gdal16" ${OSG_3RDPARTY_DIR} "d" "_i")



if (CMAKE_VERSION VERSION_LESS 2.8.3)
    message(FATAL_ERROR "Qt 5 requires at least CMake version 2.8.3")
endif()

get_filename_component(_qt5Core_install_prefix "$ENV{QTDIR}" ABSOLUTE)
MESSAGE( STATUS "_qt5Core_install_prefix: ABSOLUTE ${_qt5Core_install_prefix}" )
# For backwards compatibility only. Use Qt5Core_VERSION instead.

set(Qt5Core_VERSION_STRING 5.3.1)

set(Qt5Core_LIBRARIES Qt5::Core)

macro(_qt5_Core_check_file_exists file)
    if(NOT EXISTS "${file}" )
        message(FATAL_ERROR "The imported target \"Qt5::Core\" references the file
   \"${file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
    endif()
endmacro()

endif()

#================================================================================
SET(MY -I/home/user/application_x/include)
STRING(REGEX MATCH "[^ ]*" APPLICATION_X ${MY})
MESSAGE(STATUS ${APPLICATION_X})
MESSAGE(STATUS "STRING REGEX REPLACE...........")
STRING(REGEX REPLACE "-I([^ ]*)" "\\1"  APPLICATION_X ${MY})
MESSAGE(STATUS ${APPLICATION_X})

#================================================================================
SET(VRFRMAEWORK_VRBASE_1_LIBRARY "F:/Mysteriously.txt")
SET(VRFRMAEWORK_VRBASE_2_LIBRARY "F:/Mysteriously.txt")
SET(VRFRMAEWORK_VRBASE_3_LIBRARY "F:/Mysteriously.txt")
SET(VRFRMAEWORK_VRBASE_1_LIBRARY_DEBUG "F:/Mysteriously.txt")
SET(VRFRMAEWORK_VRBASE_2_LIBRARY_DEBUG "F:/Mysteriously.txt")
SET(VRFRMAEWORK_VRBASE_3_LIBRARY_DEBUG "F:/Mysteriously.txt")
set(VRFRMAEWORK_VRBASE_INCLUDE_DIR "C:/111")

SET(VRFRMAEWORK_VRCORE_4_LIBRARY "F:/Mysteriously.txt")
SET(VRFRMAEWORK_VRCORE_5_LIBRARY "F:/Mysteriously.txt")
SET(VRFRMAEWORK_VRCORE_6_LIBRARY "F:/Mysteriously.txt")
set(VRFRMAEWORK_VRCORE_INCLUDE_DIR "C:/222")

MACRO(_use_modoule target_name modoule_type)
	SET(list_moudoules ${ARGN})
	list(LENGTH list_moudoules _lstLen)
	IF(_lstLen)
		message(STATUS "      ${target_name} Include Dir: ${VRFRMAEWORK_${modoule_type}_INCLUDE_DIR}")
		#INCLUDE_DIRECTORIES(${VRFRMAEWORK_${modoule_type}_INCLUDE_DIR})
	ENDIF()

	foreach(m_name ${list_moudoules})
		set(lib_release})
		set(lib_debug ${})
		
		IF(VRFRMAEWORK_${modoule_type}_${m_name}_LIBRARY AND 
			VRFRMAEWORK_${modoule_type}_${m_name}_LIBRARY_DEBUG)
			message(STATUS "      ${modoule_type} Has ${m_name} Debug And Release OK!")
			#TARGET_LINK_LIBRARIES(${target_name} 
				#optimized "${ ${VRFRMAEWORK_${modoule_type}_${m_name}_LIBRARY}" 
				#debug "${VRFRMAEWORK_${modoule_type}_${m_name}_LIBRARY_DEBUG}"
			#)
		ELSEIF(VRFRMAEWORK_${modoule_type}_${m_name}_LIBRARY AND 
			NOT VRFRMAEWORK_${modoule_type}_${m_name}_LIBRARY_DEBUG)
			message(STATUS "      ${modoule_type} No Debug Lib ${m_name},Use Release Lib!")
			#TARGET_LINK_LIBRARIES(${target_name} 
				#optimized "${VRFRMAEWORK_${modoule_type}_${m_name}_LIBRARY}" 
				#debug "${VRFRMAEWORK_${modoule_type}_${m_name}_LIBRARY_DEBUG}"
			#)
		ELSE()
			message(FATAL_ERROR "      ${modoule_type} No Libs ${m_name} To Use!")	
		ENDIF()
	endforeach()
ENDMACRO()

MACRO(UseModouls target_name)
	MESSAGE(STATUS "  ==>${target_name} Use VRFramework Modouls Begin....")

	SET(options VERSIONED_LIB)
    SET(oneValueArgs)
    SET(multiValueArgs VRBASE VRCORE VRTOOLS)
    
    cmake_parse_arguments(USE 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})
    
    IF(USE_VRBASE)
    	message(STATUS "    ${target_name} Use VRBASE Modouls: ${USE_VRBASE}...")
    	_use_modoule(${target_name} VRBASE ${USE_VRBASE})
    ENDIF()

    IF(USE_VRCORE)
    	message(STATUS "    ${target_name} Use VRCORE Modouls: ${USE_VRCORE}...")
    	_use_modoule(${target_name} VRCORE ${USE_VRCORE})
    ENDIF()

    IF(USE_VRTOOLS)
    	message(STATUS "    ${target_name} Use VRTOOLS Modouls: ${USE_VRTOOLS}...")
    	_use_modoule(${target_name} VRTOOLS ${USE_VRTOOLS})
    ENDIF()
    MESSAGE(STATUS "  ==>${target_name} Use VRFramework Modouls <Finish!></Finish!>")
ENDMACRO()

UseModouls(MYTARGET
	VRBASE 1 2 3
	VRCORE 4 5 6
)
#=======================================================
SET(_path "I:\\\\work_luli\\\\_my_test\\\\CMakeModules")
MAKE_CORRECT_PATH(_path1 ${_path})
MESSAGE(STATUS "MAKE_CORRECT_PATH: ${_path1}")




#======================================================
  # Extract Boost_VERSION and Boost_LIB_VERSION from version.hpp
  set(___Boost_VERSION 0)
  set(___Boost_LIB_VERSION "")
  file(STRINGS "${CMAKE_CURRENT_LIST_DIR}/version.hpp" _boost_VERSION_HPP_CONTENTS REGEX "#define BOOST_(LIB_)?VERSION ")
  message(STATUS _boost_VERSION_HPP_CONTENTS=${_boost_VERSION_HPP_CONTENTS})
  set(____Boost_VERSION_REGEX "([0-9]+)")
  set(____Boost_LIB_VERSION_REGEX "\"([0-9_]+)\"")
  foreach(v VERSION LIB_VERSION)
    if("${_boost_VERSION_HPP_CONTENTS}" MATCHES "#define BOOST_${v} ${____Boost_${v}_REGEX}")
      set(___Boost_${v} "${CMAKE_MATCH_1}")
    endif()
  endforeach()
  unset(_boost_VERSION_HPP_CONTENTS)

  math(EXPR ___Boost_MAJOR_VERSION "${___Boost_VERSION} / 100000")
  math(EXPR ___Boost_MINOR_VERSION "${___Boost_VERSION} / 100 % 1000")
  math(EXPR ___Boost_SUBMINOR_VERSION "${___Boost_VERSION} % 100")


#======================================================
  #string(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
  SET(str_str "#define LibararyName_LIBRARY_STATIC 123")

if(${str_str} MATCHES "(#define)([ ]+)(LibararyName)")
  SET(REPLACE VDS)
  string(REGEX REPLACE "(#define)([ ]+)(LibararyName)"
            "\\1\\2EXPR" _mystring
            ${str_str})

   MESSAGE(STATUS "REGEX REPLACE_1: ${_mystring}")
 endif()


 #======================================================
 COMMON_SET_DEPENDS_DIR(FF "D:/" DEBUG_MSG)