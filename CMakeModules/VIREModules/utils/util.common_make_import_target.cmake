#.rst:
# COMMON_MAKE_IMPORT_TARGET
# -----------------------------
#
# COMMON_MAKE_IMPORT_TARGET_BASE(
#   <target_namespace> 
#   <target_name>  
#   <target_include_dir>
#   <target_location_debug>
#   <target_location_release>
# )
#
# This function is intended to be used in FindXXX.cmake modules files.
# It handles the REQUIRED arguments to FindXXX.
# It's will make the imported target of target_namespace::target_name
#
#
#
# It's useful to use target_link_libraries(xxx target_namespace::target_name),
# Instead of using  the include_directories and target_link_libararies function command.

macro(COMMON_MAKE_IMPORT_TARGET_BASE target_namespace target_name target_include_dir target_location_debug target_location_release)
#   if(NOT TARGET ${target_namespace}::${target_name})
#     add_library(${target_namespace}::${target_name} UNKNOWN IMPORTED)
#     set_target_properties(${target_namespace}::${target_name} PROPERTIES
#       IMPORTED_LOCATION_DEBUG "${target_location_debug}"
#       IMPORTED_LOCATION_RELEASE "${target_location_release}"
#       INTERFACE_INCLUDE_DIRECTORIES "${target_include_dir}"
#       #IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
#       )
#   endif()
    COMMON_MAKE_IMPORT_TARGET_PROPERTY_BASE(${target_name}
        NAMESPACE ${target_namespace}
        CONFIGURATION DEBUG
        INCLUDE_DIR ${target_include_dir}
        IMP_LIB ${target_location_debug}
        ${ARGN}
    )

    COMMON_MAKE_IMPORT_TARGET_PROPERTY_BASE(${target_name}
        NAMESPACE ${target_namespace}
        CONFIGURATION RELEASE
        INCLUDE_DIR ${target_include_dir}
        IMP_LIB ${target_location_release}
        ${ARGN}
    )
endmacro()


macro(COMMON_MAKE_IMPORT_TARGET target_name target_include_dir target_location_debug target_location_release)
	COMMON_MAKE_IMPORT_TARGET_BASE(
        ${target_name} ${target_name}
        ${target_include_dir}
        ${target_location_debug}
        ${target_location_release}
        ${ARGN}
  )
endmacro()

include(util.common_check_debug)
include(util.common_list_contains)
include(util.common_print_properties)
macro(COMMON_MAKE_IMPORT_TARGET_PROPERTY_BASE target_name)
    if("x${target_name}" STREQUAL "x")
        message(FATAL_ERROR "COMMON_MAKE_IMPORT_TARGET_PROPERTY_BASE target_name must not empty!\n")
    endif()

    COMMON_CHECK_DEBUG(_is_debug ${ARGN})

    SET(options INSTALL)
    SET(oneValueArgs 
        INCLUDE_DIR 
        CONFIGURATION 
        IMP_LIB 
        IMP_LOCATION 
        PDB_LOCATION 
        NAMESPACE 
        TARGET_TYPE
        FIND_VAL_PREFIX
    )
    SET(multiValueArgs)
    
    cmake_parse_arguments(${target_name} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})
    #============================================================
    if(NOT ${target_name}_CONFIGURATION)
        message(FATAL_ERROR "Invalide Configuration Type Of Configuration.${ARGN}.")
    endif()

    set(_validate_configuration "DEBUG" "RELEASE" "RELWITHDEBINFO" "MINSIZEREL")
    COMMON_LIST_CONTAINS(is_contain_config 
        ${${target_name}_CONFIGURATION} 
        ${_validate_configuration}
    )

    if(NOT is_contain_config)
        message(FATAL_ERROR "Invalide Configuration Type Of ${${target_name}_CONFIGURATION}")
    endif()
    #============================================================
    if(NOT ${target_name}_NAMESPACE OR "x${${target_name}_NAMESPACE}" STREQUAL "x")
        #COMMON_CHECK_DEBUG_MSG("  -->Make Default NameSpace Name:${target_name}" ${ARGN})
        SET(${target_name}_NAMESPACE ${target_name})
    endif()
    set(_import_target "${${target_name}_NAMESPACE}::${target_name}")
    #set(${target_name}_IMPORT_TARGET_NAME ${_import_target} CACHE STRING FORCE)
    #mark_as_advanced(_import_target)
    #message(STATUS  _import_target=${${target_name}_IMPORT_TARGET_NAME})
    set(_find_name ${target_name})
    if(NOT "x${${target_name}_FIND_VAL_PREFIX}" STREQUAL "x")
        set(_find_name ${${target_name}_FIND_VAL_PREFIX}_${target_name})
    endif()
    set(${_find_name}_IMPORT_TARGET_NAME ${_import_target} 
        CACHE STRING 
        "The Import Target Name is [${target}]... " FORCE
    )

    #add the import target.
    if(NOT TARGET ${_import_target})
        if(NOT ${target_name}_TARGET_TYPE)
            SET(${target_name}_TARGET_TYPE SHARED)
        endif()
        add_library(${_import_target} ${${target_name}_TARGET_TYPE} IMPORTED)
    endif()

     #include dir of the target..
    if(NOT EXISTS ${${target_name}_INCLUDE_DIR})
        message(FATAL_ERROR "Invalide Include Dir Of The ${_import_target}...${ARGN}")
    else()
        set_target_properties(${_import_target} PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${${target_name}_INCLUDE_DIR}"
        )
    endif()

    #set the configuration of the target.
    set_property(TARGET ${_import_target} 
        APPEND PROPERTY IMPORTED_CONFIGURATIONS ${${target_name}_CONFIGURATION})

    #set the .lib property
    if(NOT EXISTS ${${target_name}_IMP_LIB})
        message(FATAL_ERROR "Invalide library File Of The ${_import_target}...${${target_name}_IMP_LIB}")
    endif()
    set_target_properties(${_import_target} PROPERTIES
        "IMPORTED_IMPLIB_${${target_name}_CONFIGURATION}" ${${target_name}_IMP_LIB}
    )
    
    #set the xx.dll/xx.so property...
    set(_is_has_runtime FALSE)
    if(EXISTS ${${target_name}_IMP_LOCATION})
        #message(STATUS "  -->Invalide dll File Of The ${_import_target}...${${target_name}_IMP_LOCATION}")
    #else()
        set_target_properties(${_import_target} PROPERTIES
            "IMPORTED_LOCATION_${${target_name}_CONFIGURATION}" ${${target_name}_IMP_LOCATION}
        )
        set(_is_has_runtime TRUE)
    endif()

    #set the pdb file property...
    set(_is_has_pdb FALSE)
    if(EXISTS ${${target_name}_PDB_LOCATION})
        set_target_properties(${_import_target} PROPERTIES
            "PDB_LOCATION_${${target_name}_CONFIGURATION}" ${${target_name}_PDB_LOCATION}
        )
        set(_is_has_pdb TRUE)
    endif()
    

    if(_is_debug)
        if(_is_has_runtime)
            if(_is_has_pdb)
                COMMON_PRINT_PROPERTIES(
                    TARGETS ${_import_target} 
                    PROPERTIES
                        INTERFACE_INCLUDE_DIRECTORIES
                        IMPORTED_IMPLIB_${${target_name}_CONFIGURATION}
                        IMPORTED_LOCATION_${${target_name}_CONFIGURATION}
                        PDB_LOCATION_${${target_name}_CONFIGURATION}
                    PREFIX "      "
                )
            else(_is_has_pdb)
                COMMON_PRINT_PROPERTIES(
                    TARGETS ${_import_target} 
                    PROPERTIES
                        INTERFACE_INCLUDE_DIRECTORIES
                        IMPORTED_IMPLIB_${${target_name}_CONFIGURATION}
                        IMPORTED_LOCATION_${${target_name}_CONFIGURATION}
                    PREFIX "      "
                )
            endif(_is_has_pdb)
        else(_is_has_runtime)
            COMMON_PRINT_PROPERTIES(
                TARGETS ${_import_target} 
                PROPERTIES
                    INTERFACE_INCLUDE_DIRECTORIES
                    IMPORTED_IMPLIB_${${target_name}_CONFIGURATION}
            )
        endif(_is_has_runtime)
    endif(_is_debug)
endmacro()
