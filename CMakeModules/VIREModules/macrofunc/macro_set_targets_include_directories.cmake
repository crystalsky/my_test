
MACRO(SET_TARGETS_INCLUDE_DIRECTORIES)
	set(options )
    set(oneValueArgs )
    set(multiValueArgs TARGETS DIRECTORIES)

    cmake_parse_arguments(_SET_INCLUDE
        "${options}" 
        "${oneValueArgs}" 
        "${multiValueArgs}" 
        ${ARGN})
	

	set(_my_list_targets ${_SET_INCLUDE_TARGETS})
	set(_my_list_inluce ${_SET_INCLUDE_DIRECTORIES})
	
	MESSAGE(STATUS "  -->SET_TARGETS_INCLUDE_DIRECTORIES: ${_my_list_targets}\n     -->Include Dirs:${_my_list_inluce}")
	foreach(target ${_my_list_targets})
    	if(TARGET ${target})
	    	target_include_directories(
	    		${target} 
	    		PUBLIC
				${_my_list_inluce}
			)
		else()
			message(WARNING "SET_TARGETS_INCLUDE_DIRECTORIES: ${target} Is Not Target...")
    	endif()
	endforeach()
endmacro()

MACRO(SET_TARGETS_INCLUDE_DIRECTORIES_EX listTargets)
	SET_TARGETS_INCLUDE_DIRECTORIES(
		TARGETS 
			${${listTargets}}
		DIRECTORIES
			${ARGN}
	)
endmacro()