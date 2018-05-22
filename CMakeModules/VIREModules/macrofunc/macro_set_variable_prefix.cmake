#!NOTICE:
#This file not support modify by self, 
#It Relation Many Other CMake Macros
macro(_SET_PROJECT_VARIABLE_PRIFIX variable_name prefix_value docstring)
	if(x${prefix_value} STREQUAL "x")
		set(${prefix_value} "Project${variable_name}")
	endif()

	UNSET(ProjectVal_PREFIX_${variable_name} CACHE)
	set(ProjectVal_PREFIX_${variable_name} ${prefix_value} CACHE STRING ${docstring})
	mark_as_advanced(ProjectVal_PREFIX_${variable_name})
endmacro()

#	ProjectVal_PREFIX_ProjectConfig
_SET_PROJECT_VARIABLE_PRIFIX("CONFIG" "ProjectConfig" "Set The Prefix Of Config...")

#	ProjectVal_PREFIX_OPTION
_SET_PROJECT_VARIABLE_PRIFIX("OPTION" "ProjectOption" "Set The Prefix Of Option...")

#	ProjectVal_PREFIX_BUILD_TYPE
_SET_PROJECT_VARIABLE_PRIFIX("BUILD_TYPE" "ProjectBuildType" "Set The Prefix Of Build Type...")

#	ProjectVal_PREFIX_POST_BUILD
_SET_PROJECT_VARIABLE_PRIFIX("POST_BUILD" "ProjectPostBuild" "Set The Prefix Of Post Build...")

#	ProjectVal_PREFIX_OUT_PUT
_SET_PROJECT_VARIABLE_PRIFIX("OUT_PUT" "ProjectOutPut" "Set The Prefix Of Post Project Out Put Dir...")
