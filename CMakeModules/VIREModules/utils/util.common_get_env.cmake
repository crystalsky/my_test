# get environment variable ${PREFIX}_HOME or ${PREFIX}_ROOT
MACRO(COMMON_GET_ENV OUTVAR PREFIX)
	if(x${PREFIX} STREQUAL 'x')
		message(WARNING "common_get_env Input VAR Is Empty....")
		return()
	endif()

    if(NOT "$ENV{${PREFIX}_HOME}" STREQUAL "")
        file(TO_CMAKE_PATH "$ENV{${PREFIX}_HOME}" ${OUTVAR})
    endif()
    
    if(NOT "$ENV{${PREFIX}_ROOT}" STREQUAL "")
        file(TO_CMAKE_PATH "$ENV{${PREFIX}_ROOT}" ${OUTVAR})
    endif()

    if(NOT "$ENV{${PREFIX}_ROOT_DIR}" STREQUAL "")
        file(TO_CMAKE_PATH "$ENV{${PREFIX}_ROOT_DIR}" ${OUTVAR})
    endif()

    if(NOT "$ENV{${PREFIX}}" STREQUAL "")
        file(TO_CMAKE_PATH "$ENV{${PREFIX}}" ${OUTVAR})
    endif()
ENDMACRO()
