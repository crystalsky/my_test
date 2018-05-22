#.rst:
# util.common_get_library_name
# -------
#
# Get the debug and release name of the library.
#
#
# eg. libgdal16_i.lib libgdal16d_i.lib
#       -->in_RuntimeBaseName: gdal
#       -->RUNTIME_PREFIX:  lib
#       -->RUNTIME_POSTFIX: 16
#       -->DEBUG_SUFFIX:    d
#       -->EX_SUFFIX:       _i
#
function(COMMON_GET_LIBRARY_NAME out_libNameRelease out_libNameDebug in_libBaseName)
    SET(options)
    SET(oneValueArgs LIB_PREFIX LIB_POSTFIX DEBUG_SUFFIX EX_SUFFIX)
    SET(multiValueArgs)

    STRING(TOUPPER ${in_libBaseName} _UpperName)
    cmake_parse_arguments(${_UpperName} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN}
    )
    #message(STATUS "====COMMON_GET_LIBRARY_NAME: ${ARGN}")

    set(_tmpName ${in_libBaseName})
    
    #if library has prefix, then and the prefix to before the module_name name.
    if(${_UpperName}_LIB_PREFIX)
        set(_tmpName ${${_UpperName}_LIB_PREFIX}${_tmpName})
    endif()

    if(${_UpperName}_LIB_POSTFIX)
        set(_tmpName ${_tmpName}${${_UpperName}_LIB_POSTFIX})
    endif()

    #[0]
    set(_tmpLibNameRelease ${_tmpName})
    set(_tmpLibNameDebug ${_tmpName})

    #[1]
    if(NOT ${_UpperName}_DEBUG_SUFFIX)
        set(_tmpLibNameDebug ${_tmpLibNameDebug}d)
    else()
        set(_tmpLibNameDebug ${_tmpLibNameDebug}${${_UpperName}_DEBUG_SUFFIX})
    endif()

    #[2].set the exsuffix. 
    if(${_UpperName}_EX_SUFFIX)
        set(_tmpLibNameRelease ${_tmpLibNameRelease}${${_UpperName}_EX_SUFFIX})
        set(_tmpLibNameDebug ${_tmpLibNameDebug}${${_UpperName}_EX_SUFFIX})
    endif()
    
    #[3].out
    set(${out_libNameRelease} ${_tmpLibNameRelease} PARENT_SCOPE)
    set(${out_libNameDebug} ${_tmpLibNameDebug} PARENT_SCOPE)
endfunction()