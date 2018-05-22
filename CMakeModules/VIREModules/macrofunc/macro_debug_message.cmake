
function(DEBUG_MESSAGE msg)
    if(${ProjectVal_PREFIX_CONFIG}_DEBUG_MSG)
        MESSAGE(STATUS "${msg}")
    endif()
endfunction(DEBUG_MESSAGE)

OPTION(${ProjectVal_PREFIX_CONFIG}_DEBUG_MSG "This Variable Is The Debug The CMake")