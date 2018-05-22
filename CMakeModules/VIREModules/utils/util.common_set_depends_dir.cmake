#TYPE: NORMAL ENV ALL
MACRO(COMMON_SET_DEPENDS_DIR _depends_name _root_dir)
	SET(options)
    SET(oneValueArgs TYPE)
    SET(multiValueArgs MAYBE_DIR)
    
    cmake_parse_arguments(_dir 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN}
	)

    #[1]
	set(_validate_configuration "NORMAL" "ENV" "ALL")
    COMMON_LIST_CONTAINS(contained_type 
        ${_dir_TYPE} 
        ${_validate_configuration}
    )

    if(NOT contained_type)
        set(_dir_TYPE ALL)
    endif()

    if(NOT _dir_MAYBE_DIR)
        set(_lstMayBeDir "ROOT" "HOME")
    else()
        set(_lstMayBeDir ${_dir_MAYBE_DIR})
    endif()
    
    COMMON_CHECK_DEBUG_MSG("  ==SET_DEPENDS_DIR:
        DependsName=${_depends_name}
        DirType=${_dir_TYPE} 
        MayBeDir=${_lstMayBeDir}" 
        ${ARGN} 
        PRINT_ARGN
    )

    #[2]
    _set_dep_func(${_depends_name} ${_root_dir} ${_dir_TYPE} _lstMayBeDir)

	STRING(TOUPPER ${_depends_name} _UpperDependsName)
    if(NOT "x${_depends_name}" STREQUAL "x${_UpperDependsName}")
        _set_dep_func(${_UpperDependsName} ${_root_dir} ${_dir_TYPE} _lstMayBeDir)
	endif()
    
    #[3]
	COMMON_CHECK_DEBUG_MSG("   $[ENV]${_depends_name}([_ROOT|_HOME|_DIR|_ROOT_DIR])) = ${${_depends_name}_ROOT}" ${ARGN})
	IF(NOT EXISTS ${${_depends_name}_ROOT} AND NOT EXISTS ${${_depends_name}_HOME} AND NOT EXISTS ${${_depends_name}_DIR})
		MESSAGE(WARNING "${_depends_name}[_ROOT|_ROOT_DIR]) Not Exist....")
	ENDIF()

ENDMACRO()

MACRO(SET_DEPENDS_DIR _depends_name _root_dir)
    COMMON_SET_DEPENDS_DIR(
        ${_depends_name} 
        ${_root_dir}
        MAYBE_DIR "ROOT" "HOME" "DIR"
        ${ARGN}
    )
ENDMACRO()


MACRO(_set_dep_func _depends_name _root_dir _dir_TYPE _lisMayBeDir)
    if(${_dir_TYPE} STREQUAL "NORMAL")
        _set_dir_func(${_depends_name} ${_root_dir} ${_lisMayBeDir} FALSE)
    elseif(${_dir_TYPE} STREQUAL "ENV")
        _set_dir_func(${_depends_name} ${_root_dir} ${_lisMayBeDir} TRUE)
    elseif(${_dir_TYPE} STREQUAL "ALL")
        _set_dir_func(${_depends_name} ${_root_dir} ${_lisMayBeDir} FALSE)
        _set_dir_func(${_depends_name} ${_root_dir} ${_lisMayBeDir} TRUE)
    endif()
ENDMACRO()

MACRO(_set_dir_func _depends_name _root_dir _lisMayBeDir _isEnv)
    #message(STATUS "_set_dir_func ${${_lisMayBeDir}}")
    foreach(_maydir ${${_lisMayBeDir}})
        if(NOT _isEnv)
            SET(${_depends_name}_${_maydir} 			${_root_dir})
        else()
            if(NOT EXISTS $ENV{${_depends_name}_${_maydir}})
                SET(ENV{${_depends_name}_${_maydir}} 		${_root_dir})
            endif()
        endif()
    endforeach()
ENDMACRO()

function(GET_DEPENDS_DIR DEPNAME OUT_DIR_FOLDERS)

    set(_out_paths )
    
    set(_out_paths
        ${_out_paths} 
        ${${DEPNAME}_DIR}
        $ENV{${DEPNAME}_DIR}
        ${${DEPNAME}_ROOT}
        $ENV{${DEPNAME}_ROOT}
        ${${DEPNAME}_HOME}
        $ENV{${DEPNAME}_HOME}
    )
    message(STATUS "GET_DEPENDS_DIR:${_out_paths}")
    list(REMOVE_DUPLICATES _out_paths)

    set(${OUT_DIR_FOLDERS} ${_out_paths} PARENT_SCOPE)

endfunction()


