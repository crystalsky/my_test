#
# COMMON_FIND_PATH: find the include dir..
#

function(COMMON_FIND_PATH_NORMAL module_name header)
    SET(options)
    SET(oneValueArgs)
    SET(multiValueArgs PATHS PATH_SUFFIXES)

    STRING(TOUPPER ${module_name} _UpperName)
    cmake_parse_arguments(${_UpperName} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    set(_search_paths ${${_UpperName}_PATHS})
    set(_path_suffixes ${${_UpperName}_PATH_SUFFIXES} include inc)

    find_path(${_UpperName}_INCLUDE_DIR ${header}
        HINTS
            ${_search_paths}
        PATH_SUFFIXES 
            ${_path_suffixes}
        PATHS
            /sw # Fink
            /opt/local # DarwinPorts
            /opt/csw # Blastwave
            /opt
            /usr/freeware
            ~/Library/Frameworks
            /Library/Frameworks
            /usr/local/include
            /usr/include
            /usr/include/cal3d
            /sw/include # Fink
            /opt/local/include # DarwinPorts
            /opt/csw/include # Blastwave
            /opt/include
    )

    IF(NOT EXISTS ${${_UpperName}_INCLUDE_DIR})
        message(FATAL_ERROR "   COMMON_FIND_PATH Invalide Package[${_UpperName}] Include Dir 
        in ${_search_paths}")
    endif()
    mark_as_advanced(${_UpperName}_INCLUDE_DIR)
endfunction()

function(COMMON_FIND_PATH module_name header path)
    SET(options)
    SET(oneValueArgs)
    SET(multiValueArgs PATHS)

    STRING(TOUPPER ${module_name} _UpperName)
    cmake_parse_arguments(${_UpperName} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    set(_search_paths ${path} ${${_UpperName}_PATHS})

    COMMON_FIND_PATH_NORMAL(${module_name}
        ${header}
        PATHS ${_search_paths}
    )
endfunction()

function(test_func var1 var2)
   
    #set(tm "${var}+")
    set(${var1} ${var2}+ PARENT_SCOPE)
endfunction()