include(util.common_check_debug)
macro(COMMON_SEARCH_TARGET_FILES target_name)
    SET(options VERSIONED_LIB)
    SET(oneValueArgs)
    SET(multiValueArgs EXTS PATHS)
    
    cmake_parse_arguments(_${target_name} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN}) 
    
    SET(${target_name}_QT_UIS )
    SET(${target_name}_QT_RCS )
    SET(${target_name}_HEADERS )
    SET(${target_name}_SRCS )

    set(_search_pathes ${_${target_name}_PATHS} ${_${target_name}_UNPARSED_ARGUMENTS})

    if(NOT _${target_name}_EXTS)
        DEBUG_MESSAGE("   Default VERSIONED_LIB FALSE")
        SET(_${target_name}_EXTS "*.h" "*.cpp" "*.ui" "*.qrc")
    endif()

    #find all files....
    set(_all_files )
    foreach(_path ${_search_pathes})
        FILE(GLOB_RECURSE _fils "${_path}/*.*")
        set(_all_files ${_all_files} ${_fils})
    endforeach(_path ${_search_pathes})
    #MESSAGE(STATUS "common_search_target_files:_all_files = ${_all_files}")
    #string(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})  
     #string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
    #MESSAGE(STATUS "common_search_target_files:_${target_name}_EXTS = ${_${target_name}_EXTS}")
  
   # elseif(${_file} MATCHES "\\.h|\\.cpp|\\.qrc|\\.ui|\\.c|\\.cc")  
    
    foreach(_file ${_all_files})
        if(${_file} MATCHES "\\.h")
            set(${target_name}_HEADERS ${${target_name}_HEADERS} ${_file})
        elseif(${_file} MATCHES "\\.cpp|\\.c|\\.cc")  
            set(${target_name}_SRCS ${${target_name}_SRCS} ${_file})
        elseif(${_file} MATCHES "\\.ui")  
            set(${target_name}_QT_UIS ${${target_name}_QT_UIS} ${_file})
        elseif(${_file} MATCHES "\\.qrc")  
            set(${target_name}_QT_RCS ${${target_name}_QT_RCS} ${_file})
        endif()
    endforeach()
    
    COMMON_CHECK_DEBUG_MSG(
        "common_search_target_files:${target_name}_HEADERS = ${${target_name}_HEADERS}"
         ${ARGN})
    COMMON_CHECK_DEBUG_MSG(
        "common_search_target_files:${target_name}_SRCS = ${${target_name}_SRCS}"
        ${ARGN})
    COMMON_CHECK_DEBUG_MSG(
        "common_search_target_files:${target_name}_QT_UIS = ${${target_name}_QT_UIS}"
        ${ARGN})
    COMMON_CHECK_DEBUG_MSG(
        "common_search_target_files:${target_name}_QT_RCS = ${${target_name}_QT_RCS}"
        ${ARGN})
endmacro()

macro(COMMON_SEARCH_TARGET_FILES_QT target_name)
    SET(options)
    SET(oneValueArgs)
    SET(multiValueArgs PATHS)
    
    cmake_parse_arguments(_${target_name} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN}) 
    
    set(_search_pathes ${_${target_name}_PATHS} ${_${target_name}_UNPARSED_ARGUMENTS})

    COMMON_SEARCH_TARGET_FILES(${target_name} 
        EXTS "*.h" "*.cpp" "*.ui" "*.qrc" "*.c" "*.cc"
        PATHS ${_search_pathes}
    )
endmacro()

macro(COMMON_SEARCH_TARGET_FILES_CPP target_name)
    SET(options)
    SET(oneValueArgs)
    SET(multiValueArgs PATHS)
    
    cmake_parse_arguments(_${target_name} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN}) 
    
    set(_search_pathes ${_${target_name}_PATHS} ${_${target_name}_UNPARSED_ARGUMENTS})

    COMMON_SEARCH_TARGET_FILES(${target_name} 
        EXTS "*.h" "*.cpp" "*.c" "*.cc"
        PATHS ${_search_pathes}
    )
endmacro()