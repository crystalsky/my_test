#CMake通用全局变量设置
MACRO(CMAKE_CONFIG)
    MESSAGE(STATUS "===CMAKE_CONFIG Initinize The VIRE CMake Variables...")
    SET(OUTPUT_BINDIR ${PROJECT_SOURCE_DIR}/bin)
    MAKE_DIRECTORY(${OUTPUT_BINDIR})

    SET(OUTPUT_LIBDIR ${PROJECT_SOURCE_DIR}/lib)
    MAKE_DIRECTORY(${OUTPUT_LIBDIR})

    SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_LIBDIR})
    SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BINDIR})
    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_BINDIR})

    SET(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows" )
    SET(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
    SET(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")

    #==================================================================
    # 设置变量可以以目录显示工程
    SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
    #==================================================================
    # 让CMake生成能在构建时显示彩色状态信息的Makefile。
    SET(CMAKE_COLOR_MAKEFILE ON)
    #==================================================================
    # 是否实现相对路径
    SET(CMAKE_USE_RELATIVE_PATHS false )
ENDMACRO()

MACRO(USE_VIRE_MODULES modulePath)
    MESSAGE(STATUS "===USE_VIRE_MODULES Initinize The VIRE CMake Modules...")
    IF(EXISTS ${modulePath})
        SET(VIRE_MODULES_DIR ${modulePath})
    ELSEIF(EXISTS ${CMAKE_ROOT}/VIREModules)
        SET(VIRE_MODULES_DIR ${CMAKE_ROOT}/VIREModules)
    ELSE()
        MESSAGE(FATAL_ERROR "Not Find VIREModules In The CMake Path...., \n You Must Check The CMake Dir Where need the VIREModules....")
    ENDIF() 

    SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${VIRE_MODULES_DIR})
    
    #import include, don't remove it
    #if remove, cmake will be failed
    #...many...many...error
    include(_this_module_path_dirs)

    INCLUDE(VIREUtilityMacros)
    INCLUDE(UtilityMacros)
    INCLUDE(DefineCompilerFlags) 
    INCLUDE(FindPkgMacros)

    #自动确认三方库目录
    INCLUDE(macro_confirm_third_part_root)

    #处理Build 目标的类型
    INCLUDE(macro_build_type_config)
    BUILD_TYPE_CONFIG()
ENDMACRO()

#===================Begin At Here===================
#1.CMAKE_CONFIG
CMAKE_CONFIG()

#2.USE_VIRE_MODULES
USE_VIRE_MODULES(${CMAKE_CURRENT_LIST_DIR}/VIREModules)

#3.其他设置
IF (WIN32)
	IF (MSVC)
		# Turn on defines for non standard maths stuff
		ADD_DEFINITIONS(-D_USE_MATH_DEFINES)

		# Turn off deprecation warnings
		ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
		ADD_DEFINITIONS(-D_CRT_NONSTDC_NO_WARNINGS)
	ENDIF(MSVC)
ENDIF()