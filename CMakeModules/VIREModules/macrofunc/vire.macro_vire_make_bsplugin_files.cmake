include(macro_debug_message)
include(macro_make_export_file)

MACRO(VIRE_MAKE_BSPLUGIN_FILES LibName)
	SET(LIB_NAME ${LibName})

	#HEADER_PATH 头文件的目录
	SET(options )
	SET(oneValueArgs HEADER_DIR_PATH)
	SET(multiValueArgs)
	cmake_parse_arguments(_Make_File
			"${options}" 
			"${oneValueArgs}" 
			"${multiValueArgs}" 
			${ARGN})

	SET(_DIR_OF_Template ${THIS_MODULE_TEMPLATES_PATH})

	SET(_header_path ${CMAKE_CURRENT_SOURCE_DIR})
	IF(_Make_File_HEADER_DIR_PATH)
		SET(_header_path "${_Make_File_HEADER_DIR_PATH}")
	ENDIF()

	MAKE_EXPORT_FILE(${LibName} ${_header_path})

	SET(${LibName}_HEADER "${_header_path}/${LibName}.h")
	IF(NOT EXISTS ${${LibName}_HEADER})
		CONFIGURE_FILE("${_DIR_OF_Template}/BSPluginTemplate/plugin_file.h.in" "${${LibName}_HEADER}")
	ENDIF()
	
	SET(${LibName}_SRC "${CMAKE_CURRENT_SOURCE_DIR}/${LibName}.cpp")
	IF(NOT EXISTS ${${LibName}_SRC})
		CONFIGURE_FILE("${_DIR_OF_Template}/BSPluginTemplate/plugin_file.cpp.in" "${${LibName}_SRC}")
	ENDIF()
	
	SET(MAKE_BSPLUGIN_FILE_HEADER ${${LibName}_EXPORT} ${${LibName}_HEADER})
	DEBUG_MESSAGE("===MAKE_BSPLUGIN_FILE_HEADER===(File###${MAKE_BSPLUGIN_FILE_HEADER})")
	
	SET(MAKE_BSPLUGIN_FILE_SRC ${${LibName}_SRC})
	DEBUG_MESSAGE("===MAKE_BSPLUGIN_FILE_SRC===(File###${MAKE_BSPLUGIN_FILE_SRC})")
ENDMACRO()

MACRO(VIRE_MAKE_BSPLUGIN_FILES_INNER LibName)
	VIRE_MAKE_BSPLUGIN_FILES(${LibName} ${ARGN})
ENDMACRO()

MACRO(VIRE_MAKE_BSPLUGIN_FILES_EXPORT LibName _hederdir)
	VIRE_MAKE_BSPLUGIN_FILES(${LibName} 
		HEADER_DIR_PATH 
		${_hederdir}
	)
ENDMACRO(VIRE_MAKE_BSPLUGIN_FILES_EXPORT LibName)