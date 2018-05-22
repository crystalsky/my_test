#自定义生成类型
macro(BUILD_TYPE_CONFIG)
	OPTION(${ProjectVal_PREFIX_BUILD_TYPE}_CONFIG "Set The Build Type!" OFF)

	SET(Default_Build_Types "Debug;Release")
	SET(_MySetBuildType ${Default_Build_Types})

	IF(${ProjectVal_PREFIX_BUILD_TYPE}_CONFIG)
		OPTION(${ProjectVal_PREFIX_BUILD_TYPE}_ReleaseWithDebugInfo "Set The Build Type!" OFF)
		OPTION(${ProjectVal_PREFIX_BUILD_TYPE}_MinSizeRel "Set The Build Type!" OFF)

		IF(${ProjectVal_PREFIX_BUILD_TYPE}_ReleaseWithDebugInfo)
			set(_MySetBuildType ${_MySetBuildType} "RelWithDebInfo")
		ENDIF()

		IF(${ProjectVal_PREFIX_BUILD_TYPE}_MinSizeRel)
			set(_MySetBuildType ${_MySetBuildType} "MinSizeRel")
		ENDIF()
	ENDIF()

	#only for display
	UNSET(${ProjectVal_PREFIX_BUILD_TYPE}_Current CACHE)
	SET(${ProjectVal_PREFIX_BUILD_TYPE}_Current ${_MySetBuildType} CACHE STRING "Only For Display In CMake-GUI")	

	UNSET(CMAKE_CONFIGURATION_TYPES CACHE)
	SET(CMAKE_CONFIGURATION_TYPES ${${ProjectVal_PREFIX_BUILD_TYPE}_Current} CACHE STRING "Debug Release RelWithDebInfo MinSizeRel." FORCE)
endmacro()