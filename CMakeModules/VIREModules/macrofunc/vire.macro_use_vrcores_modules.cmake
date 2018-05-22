include(macro_link_with_variables)

macro(make_vrcore_include_variable _target _include_dir)
    string(TOUPPER ${_target} _Upper)
    set(VRCORE_${_Upper}_INCLUDE_DIR ${_include_dir})
    message(STATUS "==VRCORE_${_Upper}_INCLUDE_DIR==${VRCORE_${_Upper}_INCLUDE_DIR}==")
endmacro()

macro(use_vrcores_modules _target)
    if (NOT TARGET ${_target})
        message(FATAL_ERROR "The first argument to use_vrcores_modules must be an existing target.")
    endif()

    SET(options INTERNAL)
    SET(oneValueArgs )
    SET(multiValueArgs)
    cmake_parse_arguments(${_target}
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    SET(_link_libs ${${_target}_UNPARSED_ARGUMENTS})
    if ("${_link_libs}" STREQUAL "")
        message(FATAL_ERROR "use_vrcores_modules requires at least one vrcore module to use.")
    endif()
    message(STATUS "_link_libs==${_link_libs}==")
    message(STATUS "${_target}_INTERNAL==${${_target}_INTERNAL}==")
    set(_outer_libs_)
    foreach(_module ${_link_libs})
        string(TOUPPER ${_module} _Upper)
        if(${${_target}_INTERNAL})
            target_link_libraries(${_target} ${_module})
            message(STATUS "VRCORE_${_Upper}_INCLUDE_DIR->${VRCORE_${_Upper}_INCLUDE_DIR}")
            set_property(TARGET ${_target} 
                APPEND PROPERTY INCLUDE_DIRECTORIES ${VRCORE_${_Upper}_INCLUDE_DIR})
        else()
            set(_outer_libs_ ${_outer_libs_} VRCORE_${_Upper}_LIBRARY)
        endif()
    endforeach()
    if(NOT ${_target}_INTERNAL)
        ADD_3RD_DEPENDENCIES(${_target} _outer_libs_)
    endif()
endmacro()