#
#COMMON_ADD_TARGET_RUNTIME_DEPENDS
#NOTS: This macro always use to the find_package CONFIG Mode...
#This File Call Bu CONFIG Cmake Model
#This function alway use to the find the package runtime depends dlls, about internal external depends..
#like OSG, OSGEARTH, ICE and so on..
#

include(util.common_find_path)
include(util.common_find_library)
include(util.common_find_runtime)
include(FindPackageHandleStandardArgs)

#Usage:
#_target_name: must is the target name which is depends by project target.
#1.
# COMMON_ADD_TARGET_INTERNAL_RUNTIME_DEPENDS(
#     _target_name
#     PATH _path
#     DENPENDS_DIR _dir
#     DENPENDS_NAMES 
#          osgdb_earth
#          osgdb_kml
# )
#2.
# COMMON_ADD_TARGET_INTERNAL_RUNTIME_DEPENDS(
#     _target_name
#     PATH _path
#     DENPENDS_DIR _dir
#     DENPENDS_IN_DIR
# )
function(COMMON_ADD_TARGET_INTERNAL_RUNTIME_DEPENDS _target_name)
    set(_CUR_PACKAGE_TARGET ${_target_name}::${_target_name})
    if(NOT TARGET ${_CUR_PACKAGE_TARGET})
        message(FATAL_ERROR "Invalide Target of ${_CUR_PACKAGE_TARGET}!!")
    endif()

    SET(options STRONG_DEPENDS DENPENDS_IN_DIR IS_PLUGIN)
    SET(oneValueArgs PATH DENPENDS_DIR CHILD_DIR)
    SET(multiValueArgs DENPENDS_NAMES)
    
    cmake_parse_arguments(${_target_name} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    COMMON_CHECK_DEBUG_MSG("====COMMON_ADD_TARGET_INTERNAL_RUNTIME_DEPENDS {{{{: ${_target_name}" ${ARGN} PRINT_ARGN)

    if(NOT EXISTS ${${_target_name}_PATH})
        message(FATAL_ERROR "The PATH = [${${_target_name}_PATH}] Is Invalide!!!")
    endif()

    #[1]serch the depends names in dir:DENPENDS_DIR
    #it will cache all depend name without the 'd' or other posfix of the depend
    #it will only search the DENPENDS_DIR and without subdir which in the DENPENDS_DIR
    if(${_target_name}_DENPENDS_IN_DIR)
        if("x${${_target_name}_DENPENDS_DIR}" STREQUAL "x" )
            message(FATAL_ERROR "Invalide DENPENDS_DIR Parameters...")
        endif()

        #[1]first get the suitable dir...
        COMMON_GET_LIBRARY_DIR_INFO(_temp
            dir_lib
            dir_bin
            ${ARGN}
        )
        set(_serach_path ${${_target_name}_PATH}/${dir_bin}/${${_target_name}_DENPENDS_DIR})
        
        _find_all_file_depends_names_in_dir(
            ${_target_name}_DENPENDS_NAMES 
            ${_serach_path}
            ${ARGN}
        )
        COMMON_CHECK_DEBUG_MSG("    ====DENPENDS_IN_DIR Serched File Names:${${_target_name}_DENPENDS_NAMES}" ${ARGN} PRINT_ARGN)
    endif()

    if(NOT ${_target_name}_DENPENDS_NAMES)
        message(FATAL_ERROR "Invalide DENPENDS_NAMES And DENPENDS_IN_DIR Variables...")
    endif()

    #[1]For the internal depends
    #   We will find the runtime
    set(_target_runtime_debug)
    set(_target_runtime_release)
    foreach(depend_target_name ${${_target_name}_DENPENDS_NAMES})
        #COMMON_CHECK_DEBUG_MSG("  -->Find: ${depend_target_name}" ${ARGN})
        #[1]
        if(NOT ${_target_name}_STRONG_DEPENDS)
            COMMON_FIND_RUNTIME_EX(
                ${depend_target_name} 
                ${${_target_name}_PATH}
                _out_release_name 
                _out_debug_name
                FIND_VAL_PREFIX ${_target_name}
                CHILD_DIR ${${_target_name}_DENPENDS_DIR}
                ${ARGN}
            )
        else()
            COMMON_FIND_RUNTIME_EX(
                ${depend_target_name} 
                ${${_target_name}_PATH}
                _out_release_name 
                _out_debug_name
                FIND_VAL_PREFIX ${_target_name}
                CHILD_DIR ${${_target_name}_DENPENDS_DIR}
                VALIDATE_CHECK
                ${ARGN}
            )
        endif()
       
        #[2]set variable
        if(EXISTS ${${_out_release_name}})
            set(_target_runtime_release ${_target_runtime_release} ${${_out_release_name}})
        endif()

        if(EXISTS ${${_out_debug_name}})
            set(_target_runtime_debug ${_target_runtime_debug} ${${_out_debug_name}})
        endif()

        if("${${_out_release_name}}" STREQUAL "${${_out_debug_name}}")
            #message(WARNING "Debug Runtime Euql ==${${_out_debug_name}}")
        endif()
    endforeach()
    
    # COMMON_CHECK_DEBUG_MSG("    ==COMMON_ADD_TARGET_INTERNAL_RUNTIME_DEPENDS
    #     -->Release_Runtime:${_target_runtime_release}
    #     -->Debug_Runtime:${_target_runtime_debug}" 
    #     ${ARGN}
    # )


    #############################Target Properties###############################
    #[3]Set the target property
    set_target_properties(
        ${_CUR_PACKAGE_TARGET} PROPERTIES
        "INTERNAL_RUNTIME_DEPENDS_DEBUG" "${_target_runtime_debug}"
    ) 

    set_target_properties(
        ${_CUR_PACKAGE_TARGET} PROPERTIES
        "INTERNAL_RUNTIME_DEPENDS_RELEASE" "${_target_runtime_release}"
    ) 

    if(${_target_name}_IS_PLUGIN)
        common_append_target_property(
            ${_CUR_PACKAGE_TARGET}
            "INTERNAL_RUNTIME_IS_PLUGIN" "TRUE"
        )
    else()
        common_append_target_property(
            ${_CUR_PACKAGE_TARGET}
            "INTERNAL_RUNTIME_IS_PLUGIN" "FALSE"
        ) 
    endif()

    COMMON_CHECK_DEBUG(_isDebug ${ARGN})
    if(_isDebug)
        COMMON_PRINT_PROPERTIES(
            TARGETS ${_CUR_PACKAGE_TARGET} 
            PROPERTIES
                INTERNAL_RUNTIME_DEPENDS_DEBUG
                INTERNAL_RUNTIME_DEPENDS_RELEASE
                INTERNAL_RUNTIME_IS_PLUGIN
        )  
    endif()
    COMMON_CHECK_DEBUG_MSG("====COMMON_ADD_TARGET_INTERNAL_RUNTIME_DEPENDS }}}}: ${_target}" ${ARGN})
endfunction()

#Set The External Targets To ${_target_name}::${_target_name}
function(COMMON_ADD_TARGET_EXTERNAL_RUNTIME_DEPENDS _target_name)
    set(_CUR_PACKAGE_TARGET ${_target_name}::${_target_name})
    if(NOT TARGET ${_CUR_PACKAGE_TARGET})
        message(FATAL_ERROR "Invalide Target of ${_CUR_PACKAGE_TARGET}!!")
    endif()

    SET(options)
    SET(oneValueArgs)
    SET(multiValueArgs DEPENDS_TARGETS)
    
    cmake_parse_arguments(${_target_name} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    COMMON_CHECK_DEBUG_MSG("====COMMON_ADD_TARGET_EXTERNAL_RUNTIME_DEPENDS {{{{: ${_target_name}" ${ARGN} PRINT_ARGN)

    if(NOT ${_target_name}_DEPENDS_TARGETS)
        message(FATAL_ERROR "Invalide DENPENDS_NAMES And DENPENDS_IN_DIR Variables...")
    endif()

    #[1]For the internal depends
    #   We will find the runtime
    set(_external_targets_names)
    foreach(depend_target_name ${${_target_name}_DEPENDS_TARGETS})
        set(_ex_target_name ${depend_target_name}::${depend_target_name})
        COMMON_CHECK_DEBUG_MSG("    -->Check External Target: ${_ex_target_name}" ${ARGN})
        
        if(NOT TARGET ${_ex_target_name})
            message(FATAL_ERROR "Invalide External Target of ${_ex_target_name}..")
        endif()
        set(_external_targets_names ${_external_targets_names} ${_ex_target_name})
    endforeach()

    #############################Target Properties###############################
    #[3]Set the target property
    common_append_target_property(
        ${_CUR_PACKAGE_TARGET} 
        "EXTERNAL_RUNTIME_DEPENDS" 
        "${_external_targets_names}"
    ) 

    COMMON_CHECK_DEBUG(_isDebug ${ARGN})
    if(_isDebug)
        COMMON_PRINT_PROPERTIES(
            TARGETS ${_CUR_PACKAGE_TARGET} 
            PROPERTIES
                EXTERNAL_RUNTIME_DEPENDS
        )  
    endif()

    COMMON_CHECK_DEBUG_MSG("====COMMON_ADD_TARGET_EXTERNAL_RUNTIME_DEPENDS }}}}: ${_target}" ${ARGN})
endfunction()


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

include(util.common_get_library_dir_info)
#Note: this function find the file name which has no 'd' at end of name..
function(_find_all_file_depends_names_in_dir _out_list_names _serach_path)
    SET(options )
    SET(oneValueArgs DEBUG_POSTFIX)
    SET(multiValueArgs)
    
    cmake_parse_arguments(_DEP 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    if(NOT _DEP_DEBUG_POSTFIX)
        set(_DEP_DEBUG_POSTFIX "d")
    endif()

    file(GLOB _search_all_fils "${_serach_path}/*.*")

    set(_find_names)
    foreach(_file ${_search_all_fils})
        get_filename_component(_tmp_name ${_file} NAME_WE)
        string(TOLOWER ${_tmp_name} _lower_name)

        string(REGEX MATCH "\(.*\)${_DEP_DEBUG_POSTFIX}$" _matched_name ${_lower_name})
        if("x${_matched_name}" STREQUAL "x")
            # COMMON_CHECK_DEBUG_MSG( 
            #     "      Get File Name:${_lower_name}"
            #     ${ARGN})

            set(_find_names ${_find_names} ${_lower_name})
        endif()
    endforeach()

    set(${_out_list_names} ${_find_names} PARENT_SCOPE)
endfunction()