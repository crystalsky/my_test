include(util.common_list_contains)

#find if the debug mode.
macro(COMMON_CHECK_DEBUG debug_mode)
    set(${debug_mode} FALSE)
    #============================================================
    SET(options DEBUG_MSG _DEBUG_ DBG WITH_DEBUG)
    SET(oneValueArgs)
    SET(multiValueArgs)

    cmake_parse_arguments(_CHECK 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})
    #============================================================
    if( _CHECK_DEBUG_MSG    OR
        _CHECK__DEBUG_      OR 
        _CHECK_DBG          OR
        _CHECK_WITH_DEBUG
    )
        set(${debug_mode} TRUE)
    endif()
endmacro()

#find if the debug mode and output the msg..
macro(COMMON_CHECK_DEBUG_MSG msg)
    #============================================================
    SET(options PRINT_ARGN)
    SET(oneValueArgs LEVEL)
    SET(multiValueArgs)

    cmake_parse_arguments(_DEBUG 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})
    #============================================================
    COMMON_CHECK_DEBUG(_is_debug ${ARGN})

    set(_validate_level "STATUS" "WARNING")
    COMMON_LIST_CONTAINS(is_contain_level 
        ${_DEBUG_LEVEL} 
        ${_validate_level}
    )

    if(NOT _DEBUG_LEVEL OR NOT is_contain_level)
        set(_DEBUG_LEVEL STATUS)
    endif()

    if(_is_debug)
        if(_DEBUG_PRINT_ARGN)
            message(${_DEBUG_LEVEL} "${msg}\n    -->WithARGN:[${ARGN}]")
        else()
            message(${_DEBUG_LEVEL} ${msg})
        endif()
    endif()
endmacro()

macro(COMMON_DEBUG_MSG msg)
    COMMON_CHECK_DEBUG_MSG(msg ${ARGN})
endmacro()

