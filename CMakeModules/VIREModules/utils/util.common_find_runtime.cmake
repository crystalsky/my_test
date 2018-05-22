#
#COMMON_FIND_RUNTIME: find the runtime library....win(dll)
#

include(util.common_get_library_dir_info)
include(util.common_get_runtime_name)
#
#COMMON_FIND_RUNTIME: find the runtime library....win(dll)
#CHILD_DIR: Specific the Child Dir in Path: 
#   find libarary in path D:/xxx/osg3.2.1/bin/vc110/osgPlugins-3.2.1
#   path:       D:/xxx/osg3.2.1/bin
#   CHILD_DIR:  osgPlugins-3.2.1
#
function(COMMON_FIND_RUNTIME runtime_base_name path)
    SET(options VALIDATE_CHECK)
    SET(oneValueArgs CHILD_DIR FIND_VAL_PREFIX)
    SET(multiValueArgs PATHS)

    STRING(TOUPPER ${runtime_base_name} _UpperName)
    cmake_parse_arguments(${_UpperName} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    set(_search_paths ${path} ${${_UpperName}_PATHS})

    #get the debug and release name of the runtime.
    COMMON_GET_RUNTIME_NAME(
        _runtimeNameRelease 
        _runtimeNameDebug 
        ${runtime_base_name} 
        ${ARGN}
    )

    COMMON_GET_LIBRARY_DIR_INFO(${_UpperName}
        dir_lib
        dir_bin
        ${ARGN}
    )

    if(${_UpperName}_CHILD_DIR AND NOT "x${${_UpperName}_CHILD_DIR}" STREQUAL "x")
        set(dir_bin ${dir_bin}/${${_UpperName}_CHILD_DIR})
    endif()

    COMMON_CHECK_DEBUG_MSG("    ==COMMON_FIND_RUNTIME
      -->paths:${_search_paths}
      -->dir:${dir_bin}
      -->runtimeNameRelease:${_runtimeNameRelease}
      -->runtimeNameDebug:${_runtimeNameDebug}" ${ARGN} PRINT_ARGN)

    set(_find_name ${_UpperName})
    if(NOT "x${${_UpperName}_FIND_VAL_PREFIX}" STREQUAL "x")
        set(_find_name ${${_UpperName}_FIND_VAL_PREFIX}_${_UpperName})
    endif()

    find_file(${_find_name}_RUNTIME_FILE
        NAMES ${_runtimeNameRelease}
        HINTS
                ${_search_paths}
        PATH_SUFFIXES ${dir_bin}
        PATHS
            /sw # Fink
            /opt/local # DarwinPorts
            /opt/csw # Blastwave
            /opt
            /usr/freeware
    )

    if(${_UpperName}_VALIDATE_CHECK)
        if(NOT EXISTS ${${_find_name}_RUNTIME_FILE})
            MESSAGE(FATAL_ERROR "  COMMON_FIND_RUNTIME: Not Find RuntimeName Of ${_find_runtime_name}")
        endif()
    endif()

    find_file(${_find_name}_RUNTIME_FILE_DEBUG
        NAMES ${_runtimeNameDebug}
        HINTS
                ${_search_paths}
        PATH_SUFFIXES ${dir_bin}
        PATHS
            /sw # Fink
            /opt/local # DarwinPorts
            /opt/csw # Blastwave
            /opt
            /usr/freeware
    )

    if(NOT EXISTS ${${_find_name}_RUNTIME_FILE_DEBUG})
        set(${_find_name}_RUNTIME_FILE_DEBUG ${${_find_name}_RUNTIME_FILE} CACHE PATH "File Path" FORCE)
        #MESSAGE(WARNING "  COMMON_FIND_RUNTIME: Not Find Debug RuntimeName.Set ${_find_name}_RUNTIME_FILE_DEBUG = ${${_release_val_name}}")        
    endif()

    if(EXISTS ${${_find_name}_RUNTIME_FILE})
        mark_as_advanced(
            ${_find_name}_RUNTIME_FILE
            ${_find_name}_RUNTIME_FILE_DEBUG
        )
    endif()
endfunction()

function(COMMON_FIND_RUNTIME_EX runtime_base_name path out_debug_name out_release_name)
    #[1]
    COMMON_FIND_RUNTIME(
        ${runtime_base_name} 
        ${path}
        ${ARGN}
    )

    #[2]get the find val name
    _common_get_runtime_val_name(
        ${runtime_base_name} 
        _out_release_name 
        _out_debug_name 
        ${ARGN}
    )

    set(${out_release_name} ${_out_release_name} PARENT_SCOPE)
    set(${out_debug_name} ${_out_debug_name} PARENT_SCOPE)
endfunction()

function(_common_get_runtime_val_name runtime_base_name _out_release_name _out_debug_name)
    SET(options)
    SET(oneValueArgs FIND_VAL_PREFIX)
    SET(multiValueArgs )

    STRING(TOUPPER ${runtime_base_name} _UpperName)    
    cmake_parse_arguments(${_UpperName} 
        "${options}" 
        "${oneValueArgs}" 
        "${multiValueArgs}" 
        ${ARGN}
    )

    set(_find_runtime_name ${_UpperName})
    if(${_UpperName}_FIND_VAL_PREFIX AND NOT "x${${_UpperName}_FIND_VAL_PREFIX}" STREQUAL "x")
        set(_find_runtime_name ${${_UpperName}_FIND_VAL_PREFIX}_${_UpperName})
    endif()

    set(${_out_release_name} ${_find_runtime_name}_RUNTIME_FILE PARENT_SCOPE)
    set(${_out_debug_name} ${_find_runtime_name}_RUNTIME_FILE_DEBUG PARENT_SCOPE)
endfunction()

include(util.common_list_contains)
function(CHECK_FIND_RUNTIME _is_runtime)
    set(${_is_runtime} FALSE PARENT_SCOPE)
    set(runtime_flag RUNTIME_PREFIX RUNTIME_POSTFIX RUNTIME)
    foreach(_flag ${runtime_flag})
        COMMON_LIST_CONTAINS(_is_contain ${_flag} ${ARGN})
        if(_is_contain)
            set(${_is_runtime} TRUE PARENT_SCOPE)
            break()
        endif()
    endforeach()
endfunction(CHECK_FIND_RUNTIME _is_runtime)


