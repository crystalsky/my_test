#
#COMMON_FIND_PACKAGE COMMON_FIND_PACKAGE_COMPONENTS
#NOTS: This macro always use to the find_package CONFIG Mode...
#This File Call Bu CONFIG Cmake Model
#this function alway use to the find the package with other components.
#like OSG, OSGEARTH, ICE and so on..
#

include(util.common_find_path)
include(util.common_find_library)
include(util.common_find_runtime)
include(FindPackageHandleStandardArgs)

function(_CHECK_FIND_PATHS is_valide lstPaths)
    COMMON_CHECK_DEBUG_MSG("    ==CHECK_FIND_PATHS:${${lstPaths}}" ${ARGN})

    set(${is_valide} FALSE PARENT_SCOPE)
    foreach(_path ${${lstPaths}})
        if(EXISTS ${_path})
            set(${is_valide} TRUE PARENT_SCOPE)
            break()
        endif()
    endforeach()
endfunction()

function(COMMON_FIND_PACKAGE _target _root_path _header_file)
    if("x${_target}" STREQUAL "x")
        message(FATAL_ERROR "Invalide target name..")
    endif()

    SET(options)
    SET(oneValueArgs)
    SET(multiValueArgs PATHS)
    
    cmake_parse_arguments(${_target} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    COMMON_CHECK_DEBUG_MSG("====COMMON_FIND_PACKAGE {{{{: ${_target} ${_root_path} ${_header_file}" ${ARGN} PRINT_ARGN)

    COMMON_CHECK_DEBUG_MSG("  1.COMMON_FIND_PACKAGE Find Depends Files..." ${ARGN})
    

    set(_search_paths ${_root_path} ${${_target}_PATHS})

    #check the paths...
    _CHECK_FIND_PATHS(valide_path _search_paths ${ARGN})
    if(NOT valide_path)
        message(FATAL_ERROR "COMMON_FIND_PACKAGE With No Exist Paths To Serach Package..
        ${_search_paths}")
    endif()
    
    STRING(TOUPPER ${_target} _UpperTarget)
    
    #find the include dir...
    COMMON_FIND_PATH(
        ${_target} 
        ${_header_file} 
        ${_root_path} 
        ${ARGN}
    )

    #find the library...
    COMMON_FIND_LIBRARY(
        ${_target} 
        ${_root_path} 
        ${ARGN}
    )
   
    #find the runtime...
    CHECK_FIND_RUNTIME(has_runtime ${ARGN})
    if(has_runtime)
        #COMMON_CHECK_DEBUG_MSG("  2.COMMON_FIND_PACKAGE has_runtime.." ${ARGN})
        COMMON_FIND_RUNTIME(
            ${_target} 
            ${_root_path} 
            ${ARGN}
        )
    endif()
    
    #then....confirm the depends files...
    COMMON_CHECK_DEBUG_MSG("  2.COMMON_FIND_PACKAGE Check Depends Files..." ${ARGN})
    if(has_runtime)
        FIND_PACKAGE_HANDLE_STANDARD_ARGS(${_UpperTarget} 
            REQUIRED_VARS
            ${_UpperTarget}_INCLUDE_DIR
            ${_UpperTarget}_RUNTIME_FILE
            ${_UpperTarget}_RUNTIME_FILE_DEBUG
        )
        if(${_UpperTarget}_FOUND)
            
        endif()
    else()
        FIND_PACKAGE_HANDLE_STANDARD_ARGS(${_UpperTarget} 
            REQUIRED_VARS
            ${_UpperTarget}_LIBRARY 
            ${_UpperTarget}_INCLUDE_DIR
            ${_UpperTarget}_LIBRARY_DEBUG
        )
        if(${_UpperTarget}_FOUND)
            
        endif()
    endif()

    #last: make import target...
    COMMON_CHECK_DEBUG_MSG("  3.COMMON_FIND_PACKAGE Make Import Target..." ${ARGN})
    COMMON_MAKE_IMPORT_TARGET_PROPERTY_BASE(${_UpperTarget}
        INCLUDE_DIR ${${_UpperTarget}_INCLUDE_DIR}
        CONFIGURATION DEBUG
        IMP_LIB ${${_UpperTarget}_LIBRARY_DEBUG}
        IMP_LOCATION ${${_UpperTarget}_RUNTIME_FILE_DEBUG}
        #PDB_LOCATION "${_IMPORT_PREFIX}/${dir_bin}/UtilityKitd.pdb"
        ${ARGN}
    )

    COMMON_MAKE_IMPORT_TARGET_PROPERTY_BASE(${_UpperTarget}
        INCLUDE_DIR ${${_UpperTarget}_INCLUDE_DIR}
        CONFIGURATION RELEASE
        IMP_LIB ${${_UpperTarget}_LIBRARY}
        IMP_LOCATION ${${_UpperTarget}_RUNTIME_FILE}
        #PDB_LOCATION "${_IMPORT_PREFIX}/${dir_bin}/UtilityKitd.pdb"
        ${ARGN}
    )
    COMMON_CHECK_DEBUG_MSG("====COMMON_FIND_PACKAGE }}}}" ${ARGN})
endfunction()

#
#COMMON_FIND_PACKAGE_COMPONENTS
#search the components list packages, 
#this function alway use to the find the package with other components.
#like OSG, OSGEARTH, ICE and so on..
#
function(COMMON_FIND_PACKAGE_COMPONENTS _PackageName _root_path _header_file)
    if("x${_PackageName}" STREQUAL "x")
        message(FATAL_ERROR "Invalide target name..")
    endif()

    STRING(TOUPPER ${_PackageName} _Upper_PackageName)

    SET(options )
    SET(oneValueArgs FIND_VAL_PREFIX)
    SET(multiValueArgs COMPONENTS PATHS)

    cmake_parse_arguments(${_Upper_PackageName} 
        "${options}" 
        "${oneValueArgs}" 
        "${multiValueArgs}" 
        ${ARGN}
    )

    COMMON_CHECK_DEBUG(_isDebug ${ARGN})
    if(_isDebug)
        message(STATUS "====COMMON_FIND_PACKAGE_COMPONENTS: ${_target} ${_root_path} ${_header_file}
        with arguments:${ARGN}")
    endif()

    set(_search_paths ${_root_path} ${${_Upper_PackageName}_PATHS})
    _CHECK_FIND_PATHS(valide_path _search_paths ${ARGN})
    if(NOT valide_path)
        message(FATAL_ERROR "COMMON_FIND_PACKAGE_COMPONENTS With No Exist Paths To Serach Package..
        ${_search_paths}")
    endif()

    if(NOT ${_Upper_PackageName}_COMPONENTS)
        message(FATAL_ERROR "COMMON_FIND_PACKAGE_COMPONENTS Invalide Components..")
    endif()

    COMMON_CHECK_DEBUG_MSG("    Components: ${${_Upper_PackageName}_COMPONENTS}" ${ARGN})
    
    #find the total package include dir...
    COMMON_FIND_PATH(
        ${_Upper_PackageName} 
        ${_header_file} 
        ${_root_path} ${ARGN}
    )

    #find the runtime...
    CHECK_FIND_RUNTIME(has_runtime ${ARGN})

    #find all componets...
    foreach(_component ${${_Upper_PackageName}_COMPONENTS})
        STRING(TOUPPER ${_component} _UpperTarget)

        #find the library...
        COMMON_FIND_LIBRARY(
            ${_component} 
            ${_root_path} 
            ${ARGN}
        )

        #get the prifix lib val or runtime file prifix name
        set(_find_val_name ${_UpperTarget})
        if(NOT "x${${_Upper_PackageName}_FIND_VAL_PREFIX}" STREQUAL "x")
            set(_find_val_name ${${_Upper_PackageName}_FIND_VAL_PREFIX}_${_UpperTarget})
        endif()

        #find the runtime...
        if(has_runtime)
            COMMON_FIND_RUNTIME(
                ${_component} 
                ${_root_path} 
                ${ARGN}
            )

            FIND_PACKAGE_HANDLE_STANDARD_ARGS(${_UpperTarget} 
                REQUIRED_VARS
                ${_find_val_name}_RUNTIME_FILE
                ${_find_val_name}_RUNTIME_FILE_DEBUG
            )
            if(${_UpperTarget}_FOUND)
                mark_as_advanced(
                    ${_find_val_name}_RUNTIME_FILE
                    ${_find_val_name}_RUNTIME_FILE_DEBUG
            )
            endif()
        else()
            FIND_PACKAGE_HANDLE_STANDARD_ARGS(${_UpperTarget} 
                REQUIRED_VARS
                ${_find_val_name}_LIBRARY 
                ${_find_val_name}_LIBRARY_DEBUG
            )
        endif()

        #last: make import target...
        COMMON_MAKE_IMPORT_TARGET_PROPERTY_BASE(${_UpperTarget}
            NAMESPACE ${_Upper_PackageName}
            INCLUDE_DIR ${${_Upper_PackageName}_INCLUDE_DIR}
            CONFIGURATION DEBUG
            IMP_LIB ${${_find_val_name}_LIBRARY_DEBUG}
            IMP_LOCATION ${${_find_val_name}_RUNTIME_FILE_DEBUG}
            #PDB_LOCATION "${_IMPORT_PREFIX}/${dir_bin}/UtilityKitd.pdb"
            ${ARGN}
        )

        COMMON_MAKE_IMPORT_TARGET_PROPERTY_BASE(${_UpperTarget}
            NAMESPACE ${_Upper_PackageName}
            INCLUDE_DIR ${${_Upper_PackageName}_INCLUDE_DIR}
            CONFIGURATION RELEASE
            IMP_LIB ${${_find_val_name}_LIBRARY}
            IMP_LOCATION ${${_find_val_name}_RUNTIME_FILE}
            #PDB_LOCATION "${_IMPORT_PREFIX}/${dir_bin}/UtilityKitd.pdb"
            ${ARGN}
        )
    endforeach()
endfunction()