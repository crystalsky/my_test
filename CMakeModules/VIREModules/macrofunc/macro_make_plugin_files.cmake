MACRO(MAKE_VIRE_BSPLUGIN_FILES LibName)
	SET(_Lib_Name ${LibName})
	
	SET(${_Lib_Name}_EXPORT "${VIRE_INCLUDE_DIR}/VRPlugins/BSPlugins/${_Lib_Name}/${_Lib_Name}_Export.h")
	IF(NOT EXISTS ${${_Lib_Name}_EXPORT})
	CONFIGURE_FILE("${CMAKE_MODULE_PATH}/Templates/BSPluginTemplate/plugin_export.h.in" "${${_Lib_Name}_EXPORT}")
	ENDIF(NOT EXISTS ${${_Lib_Name}_EXPORT})
	
	SET(${_Lib_Name}_HEADER "${VIRE_INCLUDE_DIR}/VRPlugins/BSPlugins/${_Lib_Name}/${_Lib_Name}Plugin.h")
	IF(NOT EXISTS ${${_Lib_Name}_HEADER})
	CONFIGURE_FILE("${CMAKE_MODULE_PATH}/Templates/BSPluginTemplate/plugin_file.h.in" "${${_Lib_Name}_HEADER}")
	ENDIF(NOT EXISTS ${${_Lib_Name}_HEADER})
	
	SET(${_Lib_Name}_SRC "${VIRE_SRC_DIR}/VRPlugins/BSPlugins/${_Lib_Name}/${_Lib_Name}Plugin.cpp")
	IF(NOT EXISTS ${${_Lib_Name}_SRC})
	CONFIGURE_FILE("${CMAKE_MODULE_PATH}/Templates/BSPluginTemplate/plugin_file.cpp.in" "${${_Lib_Name}_SRC}")
	ENDIF(NOT EXISTS ${${_Lib_Name}_SRC})
	
	SET(MAKE_BSPLUGIN_FILE_HEADER ${${_Lib_Name}_EXPORT} ${${_Lib_Name}_HEADER})
	MESSAGE("===MAKE_BSPLUGIN_FILE_HEADER===(File###${MAKE_BSPLUGIN_FILE_HEADER})")
	
	SET(MAKE_BSPLUGIN_FILE_SRC ${${_Lib_Name}_SRC})
	MESSAGE("===MAKE_BSPLUGIN_FILE_SRC===(File###${MAKE_BSPLUGIN_FILE_SRC})")
	
	#===================================================
	# 定义标识符
	ADD_DEFINITIONS(-D${LIB_NAME}_LIB)
	#===================================================
ENDMACRO(MAKE_VIRE_BSPLUGIN_FILES LibName _MajorVersion _MinorVersion _PatchVersion _SOVersion)