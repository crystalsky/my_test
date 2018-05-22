#
# COMMON_FIND_LIBRARY: find the library...windows(lib)
#
include(util.common_get_library_dir_info)
include(util.common_get_library_name)

function(COMMON_FIND_LIBRARY module_name path)
    SET(options)
    SET(oneValueArgs FIND_VAL_PREFIX)
    SET(multiValueArgs PATHS)

    STRING(TOUPPER ${module_name} _UpperName)
    cmake_parse_arguments(${_UpperName} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    set(_search_paths ${path} ${${_UpperName}_PATHS})

    #get the debug and release name of the library.
    COMMON_GET_LIBRARY_NAME(
        _libNameRelease 
        _libNameDebug 
        ${module_name} 
        ${ARGN}
    )

    #get the search library dir.
    COMMON_GET_LIBRARY_DIR_INFO(${_UpperName}
        dir_lib
        dir_bin
        ${ARGN}
    )

    COMMON_CHECK_DEBUG_MSG("    ==COMMON_FIND_LIBRARY 
      -->paths:${_search_paths}
      -->dir:${dir_lib}
      -->libNameRelease:${_libNameRelease}
      -->libNameDebug:${_libNameDebug}"  ${ARGN})

    set(_find_name ${_UpperName})
    if(NOT "x${${_UpperName}_FIND_VAL_PREFIX}" STREQUAL "x")
        set(_find_name ${${_UpperName}_FIND_VAL_PREFIX}_${_UpperName})
    endif()

    #find the library.
    find_library(${_find_name}_LIBRARY
        NAMES ${_libNameRelease}
        HINTS
                ${_search_paths}
        PATH_SUFFIXES ${dir_lib}
        PATHS
                /sw # Fink
                /opt/local # DarwinPorts
                /opt/csw # Blastwave
                /opt
                /usr/freeware
        NO_DEFAULT_PATH
    )

    IF(NOT EXISTS ${${_find_name}_LIBRARY})
        COMMON_CHECK_DEBUG_MSG("    ==COMMON_FIND_LIBRARY 
        -->paths:${_search_paths}
        -->dir:${dir_lib}
        -->libNameRelease:${_libNameRelease}
        -->libNameDebug:${_libNameDebug}"  DEBUG_MSG)
        message(FATAL_ERROR "   -->COMMON_FIND_LIBRARY Invalide Package ${_find_name}_LIBRARY...")
    endif()

    find_library(${_find_name}_LIBRARY_DEBUG
        NAMES ${_libNameDebug}
        HINTS
                ${_search_paths}
        PATH_SUFFIXES ${dir_lib}
        PATHS
                /sw # Fink
                /opt/local # DarwinPorts
                /opt/csw # Blastwave
                /opt
                /usr/freeware
        NO_DEFAULT_PATH
    )

    if(NOT ${_find_name}_LIBRARY_DEBUG)
        # They don't have a debug library
        set(${_find_name}_LIBRARY_DEBUG ${${_find_name}_LIBRARY} PARENT_SCOPE)
        set(${_find_name}_LIBRARIES ${${_find_name}_LIBRARY} PARENT_SCOPE)
    else()
        # They really have a FOO_LIBRARY_DEBUG
        set(${_find_name}_LIBRARIES 
            optimized ${${_find_name}_LIBRARY}
            debug ${${_find_name}_LIBRARY_DEBUG}
            PARENT_SCOPE
        )
    endif()

    mark_as_advanced(
        ${_find_name}_LIBRARY 
        ${_find_name}_LIBRARY_DEBUG
    )
endfunction()

macro(COMMON_FIND_LIBARAY_NORMAL OUT_FIND_LIB_VAL DEPNAME libNames)
    SET(options)
    SET(oneValueArgs )
    SET(multiValueArgs PATHS)

    STRING(TOUPPER ${DEPNAME} _UpperDEPNAME)
    cmake_parse_arguments(${_UpperDEPNAME} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    set(_search_paths 
        ${${_UpperDEPNAME}_PATHS}
        ${${_UpperDEPNAME}_DIR}
        $ENV{${_UpperDEPNAME}_DIR}
        ${${_UpperDEPNAME}_ROOT}
        $ENV{${_UpperDEPNAME}_ROOT}
        ${${_UpperDEPNAME}_HOME}
        $ENV{${_UpperDEPNAME}_HOME}
    )
    list(REMOVE_DUPLICATES _search_paths)
    
     #get the search library dir.
    COMMON_GET_LIBRARY_DIR_INFO(${_UpperDEPNAME}
        dir_lib
        dir_bin
        ${ARGN}
    )
    
    FIND_LIBRARY(${OUT_FIND_LIB_VAL}
        NAMES ${libNames}
    PATHS
        ${_search_paths}
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local/lib
        /usr/lib
        /sw/lib
        /opt/local/lib
        /opt/csw/lib
        /opt/lib
    PATH_SUFFIXES
        ${dir_lib}
    )

endmacro()


