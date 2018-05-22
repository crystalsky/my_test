MACRO(VERSIONED_LIB LibName _MajorVersion _MinorVersion _PatchVersion _SOVersion)
	SET(_Lib_Name ${LibName})
	SET(${_Lib_Name}_MajorVersion 	${_MajorVersion})
	SET(${_Lib_Name}_MinorVersion 	${_MinorVersion})
	SET(${_Lib_Name}_PatchVersion 	${_PatchVersion})
	SET(${_Lib_Name}_SOVersion 		${_SOVersion})
	
	SET(_LIB_TARGET_VERSION  
		${${_Lib_Name}_MajorVersion}.${${_Lib_Name}_MinorVersion}.${${_Lib_Name}_PatchVersion}.${${_Lib_Name}_SOVersion})
	MESSAGE(STATUS "===Versioned The Lib:->${_Lib_Name}<-With Version->${_LIB_TARGET_VERSION}<--")
	
	SET(VERSIONED_LIB_RC "${CMAKE_CURRENT_BINARY_DIR}/Version.rc")
	CONFIGURE_FILE("${CMAKE_MODULE_PATH}/resource/Version.rc.in" "${VERSIONED_LIB_RC}")
	MESSAGE("===VERSIONED_LIB_RC===(File###${VERSIONED_LIB_RC})")
ENDMACRO(VERSIONED_LIB LibName _MajorVersion _MinorVersion _PatchVersion _SOVersion)