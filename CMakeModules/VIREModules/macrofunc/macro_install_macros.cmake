include(macro_install_macros_private)

MACRO(INSTALL_CONFIG config_name)
	SET(options )
	SET(oneValueArgs PATH)
	SET(multiValueArgs)

	cmake_parse_arguments(_INSTALL_CONFIG 
			"${options}" 
			"${oneValueArgs}" 
			"${multiValueArgs}" 
			${ARGN}
	)

	IF(_x${config_name} STREQUAL "_x")
		MESSAGE(FATAL_ERROR "You Must Set Install Config Name....")
	ENDIF()
	SET(_${config_name}_Root "$ENV{${config_name}_ROOT}")

	UNSET(${config_name}_Install_Dir)	
	#use self param directory in this section...
	IF(EXISTS ${_INSTALL_CONFIG_PATH})
		SET(${config_name}_Install_Dir ${_INSTALL_CONFIG_PATH} CACHE PATH "Where to install...")
	ELSE()
		SET(${config_name}_Install_Dir ${PROJECT_SOURCE_DIR}/${config_name} CACHE PATH "Where to install...")
	ENDIF()

	IF(NOT ${config_name}_Install_Dir AND _${config_name}_Root)
	  MESSAGE(STATUS "Use ${config_name}_ROOT Environment To Install Dir...")
	  SET(${config_name}_Install_Dir ${_${config_name}_Root})
	ENDIF()

	UNSET(CMAKE_INSTALL_PREFIX)
	SET(CMAKE_INSTALL_PREFIX ${${config_name}_Install_Dir} CACHE PATH "Where to install ${PROJECT_NAME}" FORCE)
	#====================================User Options Begin=============================
	#是否是框架安装,如果不是框架的安装方式，就以独立库的方式安装处理
	OPTION(${config_name}_Install_With_FrameWork_Mode "Install With FrameWork Mode...." OFF)
	UNSET(INSTALL_WITH_FRAMEWORK_MODE)
	SET(INSTALL_WITH_FRAMEWORK_MODE ${${config_name}_Install_With_FrameWork_Mode})
	
	
	#define Option To Install With PDB File...
	OPTION(${config_name}_Install_With_PDB_File "Install With PDB Files...." OFF)
	UNSET(INSTALL_PDB_FILE)
	SET(INSTALL_PDB_FILE ${${config_name}_Install_With_PDB_File})

	#Define Variable To Decide Install With version of vc..
	#depends by CMake MSVC Version
	#like 	QtUtility/lib/vc100
	#		QtUtility/lib/vc110			
	#		QtUtility/bin/vc100
	OPTION(${config_name}_Install_With_VCVersion "Install With MSCVer...." OFF)
	UNSET(INSTALL_WITH_VCVERSION)
	SET(INSTALL_WITH_VCVERSION ${${config_name}_Install_With_VCVersion})

	#support for the version dir mode when not in framework_mode.
	#it will make install the package with dir name like
	# package-1.0.3/include
	# package-1.0.3/lib
	# package-1.0.3/bin
	UNSET(INSTALL_VERSION_DIR)
	IF(NOT ${config_name}_Install_With_FrameWork_Mode)
		OPTION(${config_name}_Install_With_Version_Dir "Install With VERSION_DIR...." OFF)
		SET(INSTALL_VERSION_DIR ${${config_name}_Install_With_Version_Dir})
	ELSE()
		SET(INSTALL_VERSION_DIR FALSE)
	ENDIF()
	#===================================================================================
ENDMACRO()

macro(INSTALL_WITH_PDB_FILE target_name)
	IF(INSTALL_PDB_FILE)
		_INSTALL_WITH_PDB_FILE(${target_name} INSTALL_PDB)
	ENDIF()
endmacro()

macro(PACKAGE_WITH_PDB_FILE target_name)
    INSTALL_WITH_PDB_FILE(${target_name})
endmacro()

#=================================================
MACRO(BEGIN_INSTALL _libname)
    INSTALL(CODE "MESSAGE(\"====Installing Lib ${_libname} To ${CMAKE_INSTALL_PREFIX}/${_libname}====\")")
ENDMACRO()

MACRO(END_INSTALL _libname)
    INSTALL(CODE "MESSAGE(\"==========Installing Lib ${_libname} Finish==========\")")
ENDMACRO()
#=================================================

#==============================================================
MACRO(_INSTALL_PROC_BASE target_name header_files)
    #===============================================
	BEGIN_INSTALL(${target_name})
	 #===============================================
	#if(INSTALL_WITH_VCVERSION AND INSTALL_WITH_FRAMEWORK_MODE AND INSTALL_PDB_FILE)
		#_INSTALL_PROC_BASE_T1(${target_name} VERSIONED_LIB FRAMEWORK_MODE ${ARGN})
	#ELIF(INSTALL_WITH_VCVERSION)
		#_INSTALL_PROC_BASE_T1(${target_name} VERSIONED_LIB ${ARGN})
	#ELIF(INSTALL_WITH_FRAMEWORK_MODE)
		#_INSTALL_PROC_BASE_T1(${target_name} FRAMEWORK_MODE ${ARGN})
	#ELSE()
		#_INSTALL_PROC_BASE_T1(${target_name} ${ARGN})
	#ENDIF()

	_INSTALL_PROC_BASE_T1(
		${target_name} 
		${header_files} 
		VERSIONED_LIB ${INSTALL_WITH_VCVERSION}
		FRAMEWORK_MODE ${INSTALL_WITH_FRAMEWORK_MODE}
		VERSION_DIR ${INSTALL_VERSION_DIR}
		INSTALL_PDB ${INSTALL_PDB_FILE}
		${ARGN}
	)
	 #===============================================
	END_INSTALL(${target_name})
	#==========================================================
ENDMACRO()

#==============================================================
#${target_name}/include
#${target_name}/lib
MACRO(DEFAULT_INSTALL_PROCESS target_name header_files)
	_INSTALL_PROC_BASE(${target_name} ${header_files} ${ARGN})
ENDMACRO()

MACRO(DEFAULT_INSTALL_PROC target_name header_files)
	_INSTALL_PROC_BASE(${target_name} ${header_files} ${ARGN})
ENDMACRO()
#==============================================================
#include/${target_name}/${_libName}
#${target_name}/lib
MACRO(DEFAULT_INSTALL_HEADER_DIR_PROCESS target_name header_files header_add_dir)
	_INSTALL_PROC_BASE(${target_name} ${header_files} INCLUDE_ADD_DIR ${header_add_dir} ${ARGN})
ENDMACRO()
#==============================================================

