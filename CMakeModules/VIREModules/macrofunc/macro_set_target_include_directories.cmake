
MACRO( listTargets)
	

	foreach(target ${listTargets})
    	if(TARGET ${target})
	    	target_include_directories(
	    		${target} 
	    		PUBLIC
				${ARGN}
			)
		else()
			message(WARNING "SET_TARGETS_INCLUDE_DIRECTORIES: ${target} Is Not Target...")
    	endif()
	endforeach()
endmacro()