#=============================================================
# 为工程设置最低的Cmake版本需求
CMAKE_MINIMUM_REQUIRED(VERSION 2.4.0 FATAL_ERROR)

# CMAKE_POLICY命令来设置版本的兼容性，以避免一些不必要的警告信息。
IF( COMMAND CMAKE_POLICY )
  # Works around warnings libraries linked against that don't
  # have absolute paths 
  CMAKE_POLICY( SET CMP0003 NEW )
  # Works around warnings about escaped quotes in ADD_DEFINITIONS
  # statements.
  CMAKE_POLICY(SET CMP0005 OLD)

  CMAKE_POLICY( SET CMP0010 OLD )
  CMAKE_POLICY( SET CMP0020 OLD )
  CMAKE_POLICY( SET CMP0043 OLD )
  CMAKE_POLICY( SET CMP0054 OLD )
  #CMAKE_POLICY( SET CMP0054 OLD)
ENDIF( COMMAND CMAKE_POLICY )

#=================User Defined Project======================
OPTION(Build_General_Project  "Default Project Builder...." OFF)
OPTION(Build_ICE_Project  "Default ICE Project...." OFF)
OPTION(Build_CMakeTest_Project  "Build_CMakeTest_Project...." OFF)
OPTION(Build_Boost_Project  "Build_Boost_Project...." OFF)

IF(Build_General_Project)
    SET(_ProjectName _MyProject)
ELSEIF(Build_ICE_Project)
    OPTION(BUILDICE_TYPE_SERVER "Default ICE Server Project...." ON)
    IF(BUILDICE_TYPE_SERVER)
        SET(_ProjectName _ICE_Servers)
    ELSE()
        SET(_ProjectName _ICE_Clients)
    ENDIF()
ELSEIF(Build_CMakeTest_Project)
    SET(_ProjectName _CMakeTest)
ELSEIF(Build_Boost_Project)
    SET(_ProjectName _BoostTest)
ENDIF()

IF(NOT _ProjectName)
  MESSAGE(FATAL_ERROR "No Project Name Set....")
ENDIF()

PROJECT (${_ProjectName})
#=============================================================

#设置工程的头文件目录
SET (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
SET (PROJECT_BIN_DIR     ${PROJECT_SOURCE_DIR}/bin )
SET (PROJECT_LIB_DIR     ${PROJECT_SOURCE_DIR}/lib )
SET (PROJECT_SRC_DIR     ${PROJECT_SOURCE_DIR}/src )

#=============================================================
# set path to additional CMake modules
SET(_CUR_MODULES_DIR ${CMAKE_CURRENT_LIST_DIR}/CMakeModules)
IF(EXISTS ${_CUR_MODULES_DIR})
    SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${_CUR_MODULES_DIR})
    IF(EXISTS ${_CUR_MODULES_DIR}/_VIREModules.cmake)
        include(_VIREModules)
    ENDIF()
ENDIF()

#=============================================================
#qt_support
QT_SUPPORT()

#=============================================================
#当下两个宏可以为其它开源项目使用（比较公用的模块）
CONFIRM_THIRD_PART_ROOT()
#CONFIRM_THIRD_PART_ROOT(PATH ${_thirdpart_root})
#CONFIRM_THIRD_PART_ROOT(PATH ${CMAKE_SOURCE_DIR}/ThirdParty)

INCLUDE(ThirdPartSet)
THIRD_PART_SET()
#THIRD_PART_SET(${PROJECT_SOURCE_DIR}/ThirdParty)

IF(Build_General_Project)
    find_package(OSG 3.2.1 EXACT CONFIG)
    find_package(UtilityKit CONFIG 2.3.9 EXACT)
    find_package(QtXmlSerialize CONFIG 1.0.4 EXACT)
    find_package(QtUtility CONFIG)
    find_package(glog CONFIG)
    find_package(jsoncpp CONFIG)
    find_package(tinyxml CONFIG)
    find_package(freeglut CONFIG)
    find_package(xerces-c CONFIG)
    find_package(QtUI CONFIG)
    find_package(GLFW CONFIG)
    find_package(GLEW CONFIG)
    find_package(GLAD CONFIG)
    find_package(GLTOOLS CONFIG)
ELSEIF(Build_ICE_Project)
    find_package(UtilityKit 2.350 EXACT CONFIG)
    find_package(QtUtility CONFIG)
    find_package(glog CONFIG)
    find_package(tinyxml CONFIG)
    find_package(jsoncpp CONFIG)
    find_package(Ice CONFIG)
ELSEIF(Build_Boost_Project)
    find_package(UtilityKit CONFIG 2.350 QUIET)
ELSE()

ENDIF()

Find_Boost(BOOST_COMPONENTS #这里可以加入Boost的依赖库名，找到Boost库
    thread
    date_time
    system
    chrono
    filesystem
    serialization
    program_options
	timer
)
#=============================================================
SET (DEFAULT_INCLUDE_SUBDIR ${PROJECT_SOURCE_DIR}/include)

#=============================================================
# process subdirs
ADD_SUBDIRECTORY(src)
#=============================================================
# Uninstall targe 卸载  
