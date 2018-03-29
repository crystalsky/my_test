# 为工程设置最低的Cmake版本需求
CMAKE_MINIMUM_REQUIRED(VERSION 2.4.0 FATAL_ERROR)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
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

#=================================================
OPTION(Build_General_Project  "Default Project Builder...." OFF)
OPTION(Build_ICE_Project  "Default ICE Project...." OFF)
OPTION(Build_CMakeTest_Project  "Build_CMakeTest_Project...." OFF)

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
ENDIF()

IF(NOT _ProjectName)
  MESSAGE(FATAL_ERROR "No Project Name Set....")
ENDIF()

PROJECT (${_ProjectName})
#=================================================

#设置工程的头文件目录
SET (PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
SET (PROJECT_BIN_DIR     ${PROJECT_SOURCE_DIR}/bin )
SET (PROJECT_LIB_DIR     ${PROJECT_SOURCE_DIR}/lib )
SET (PROJECT_SRC_DIR     ${PROJECT_SOURCE_DIR}/src )

# 让CMake生成能在构建时显示彩色状态信息的Makefile。
SET(CMAKE_COLOR_MAKEFILE ON)

# 是否实现相对路径
SET(CMAKE_USE_RELATIVE_PATHS false )

# set path to additional CMake modules
SET(VIRE_CMAKE_MODULES_DIR ${CMAKE_ROOT}/VIREModules)
IF(NOT EXISTS ${VIRE_CMAKE_MODULES_DIR})
  MESSAGE(FATAL_ERROR "Not Find VIREModules In The CMake Path...., \n You Must Check The CMake Dir Where need the VIREModules....")
ENDIF()
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${VIRE_CMAKE_MODULES_DIR})
# Create bin and lib directories if required

IF("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
   FILE(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin ${CMAKE_BINARY_DIR}/lib)
ENDIF("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")


# set default cmake build type to (None Debug Release RelWithDebInfo MinSizeRel)
SET( CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Choose the type of build, options are: None Debug Release MinSizeRel." FORCE )

#=============================================================
# Installation stuff
SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows" )
SET(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")

# Here we apparantly do some funky stuff with making the bin/ and lib/
# folders which is probably needed to work around a very old CMake bug?

#SET(OUTPUT_BINDIR ${PROJECT_BINARY_DIR}/bin/${CMAKE_SYSTEM_NAME})
SET(OUTPUT_BINDIR ${PROJECT_SOURCE_DIR}/bin)
MAKE_DIRECTORY(${OUTPUT_BINDIR})
IF(MSVC AND NOT MSVC_IDE)
    MAKE_DIRECTORY(${OUTPUT_BINDIR}/${OSG_PLUGINS})
ENDIF(MSVC AND NOT MSVC_IDE)

SET(OUTPUT_LIBDIR ${PROJECT_SOURCE_DIR}/lib)
MAKE_DIRECTORY(${OUTPUT_LIBDIR})
IF(NOT MSVC OR MSVC_IDE)
    MAKE_DIRECTORY(${OUTPUT_LIBDIR}/${OSG_PLUGINS})
ENDIF(NOT MSVC OR MSVC_IDE)

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_LIBDIR})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BINDIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_BINDIR})


IF (WIN32)
	IF (MSVC)
		# Turn on defines for non standard maths stuff
		ADD_DEFINITIONS(-D_USE_MATH_DEFINES)

		# Turn off deprecation warnings
		ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
		ADD_DEFINITIONS(-D_CRT_NONSTDC_NO_WARNINGS)
	ENDIF(MSVC)
	 # This option is to enable the /DYNAMICBASE switch
	 # It is used to workaround a bug in Windows 7 when linking in release, which results in corrupt
	 # binaries. See this page for details: http://www.wintellect.com/CS/blogs/jrobbins/archive/2009/01/24/the-case-of-the-corrupt-pe-binaries.aspx
	 OPTION(WIN32_USE_DYNAMICBASE "Set to ON to build osgOcean with the /DYNAMICBASE option to work around a bug when linking release executables on Windows 7." OFF)
	 MARK_AS_ADVANCED(WIN32_USE_DYNAMICBASE)
	 IF(WIN32_USE_DYNAMICBASE)
		SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DYNAMICBASE")
	 ENDIF(WIN32_USE_DYNAMICBASE)
ENDIF()

#=============================================================
INCLUDE(VIREUtilityMacros)
INCLUDE(UtilityMacros)
INCLUDE(DefineCompilerFlags) 
INCLUDE(FindPkgMacros)

#=============================================================
#qt_support
qt_support()

#=========================ThirdPart========================
COMMON_GET_ENV(_thirdpart_root THIRDPART_ROOT)
if(NOT EXISTS ${_thirdpart_root})
  MESSAGE(FATAL_ERROR "No Find ThridPart Dir In Env....")
endif()

set(CMAKE_PREFIX_PATH 
    ${CMAKE_PREFIX_PATH} 
    "${_thirdpart_root}"
    "${PROJECT_SOURCE_DIR}/ThirdParty"
)

#当下两个宏可以为其它开源项目使用（比较公用的模块）
INCLUDE(macro_confirm_third_part_root)
CONFIRM_THIRD_PART_ROOT(PATH ${_thirdpart_root})
#CONFIRM_THIRD_PART_ROOT(PATH ${CMAKE_SOURCE_DIR}/ThirdParty)

INCLUDE(ThirdPartSet)
THIRD_PART_SET(${PROJECT_SOURCE_DIR}/ThirdParty)
#====================================
INCLUDE(macro_third_part_prepare)
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
  ELSEIF(Build_CMakeTest_Project)
    
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
SET (DEFAULT_SUBDIR     	${PROJECT_SOURCE_DIR}) 
SET (DEFAULT_BIN_SUBDIR     ${PROJECT_SOURCE_DIR}/bin) 
SET (DEFAULT_INCLUDE_SUBDIR ${PROJECT_SOURCE_DIR}/include)
SET (DEFAULT_LIB_SUBDIR     ${PROJECT_SOURCE_DIR}/lib)
SET (DEFAULT_SRC_SUBDIR     ${PROJECT_SOURCE_DIR}/src)

#=============================================================
# process subdirs
ADD_SUBDIRECTORY(src)
#=============================================================
# Uninstall targe 卸载  
