#.rst:
# util.common_get_library_name
# -------
#
# Get the debug and release name of the library.
#
# eg. libgdal16_i.dll libgdal16d_i.dll libgdal16_i.so libgdal16d_i.so
#       -->in_RuntimeBaseName: gdal
#       -->RUNTIME_PREFIX:  lib
#       -->RUNTIME_POSTFIX: 16
#       -->DEBUG_SUFFIX:    d
#       -->EX_SUFFIX:       _i
#
function(COMMON_GET_RUNTIME_NAME out_runtimeNameRelease out_runtimeNameDebug in_RuntimeBaseName)
    SET(options)
    SET(oneValueArgs RUNTIME_PREFIX RUNTIME_POSTFIX DEBUG_SUFFIX EX_SUFFIX)
    SET(multiValueArgs)

    STRING(TOUPPER ${in_RuntimeBaseName} _UpperName)
    cmake_parse_arguments(${_UpperName} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN}
    )

    set(_tmpName ${in_RuntimeBaseName})
   

    #if library has prefix, then and the prefix to before the module_name name.
    if(${_UpperName}_RUNTIME_PREFIX)
        set(_tmpName ${${_UpperName}_RUNTIME_PREFIX}${_tmpName})
    endif()

    if(${_UpperName}_RUNTIME_POSTFIX)
        set(_tmpName ${_tmpName}${${_UpperName}_RUNTIME_POSTFIX})
    endif()

    #[0]
    set(_tmpNameRelease ${_tmpName})
    set(_tmpNameDebug ${_tmpName})

    #[1]
    if(NOT ${_UpperName}_DEBUG_SUFFIX)
        set(_tmpNameDebug ${_tmpNameDebug}d)
    else()
        set(_tmpNameDebug ${_tmpNameDebug}${${_UpperName}_DEBUG_SUFFIX})
    endif()

    #[2].set the exsuffix. 
    if(${_UpperName}_EX_SUFFIX)
        set(_tmpNameRelease ${_tmpNameRelease}${${_UpperName}_EX_SUFFIX})
        set(_tmpNameDebug ${_tmpNameDebug}${${_UpperName}_EX_SUFFIX})
    endif()

    if(MSVC)
        set(_tmpNameRelease ${_tmpNameRelease}.dll)
        set(_tmpNameDebug ${_tmpNameDebug}.dll)
    endif()
    
    #[3].out
    set(${out_runtimeNameRelease} ${_tmpNameRelease} PARENT_SCOPE)
    set(${out_runtimeNameDebug} ${_tmpNameDebug} PARENT_SCOPE)
endfunction()