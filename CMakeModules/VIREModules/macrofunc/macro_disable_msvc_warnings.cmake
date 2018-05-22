macro(disable_msvc_warnings)
    if(MSVC)
        foreach(warning ${ARGN})
            add_definitions(-wd${warning})
        endforeach()
    endif()
endmacro()

macro(disable_msvc_warnings_special)
    disable_msvc_warnings(
        4786 #identifier was truncated to '255' characters in the debug information
        4251 # 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
        4250 # ... inherits ... via dominance
        4099 #  'std::_Uninitialized_copy0': Function call with parameters that may be unsafe
        4996 # struct and class mixed
        4819 # The file contains a character that cannot be represented in the current code page (936). Save the file in Unicode format to prevent data loss
    )
endmacro()

macro(disable_msvc_warnings_4819)
    disable_msvc_warnings(4819)
endmacro()



