include(util.common_get_library_folder)
include(util.common_check_debug)

#BIT X86|X64
MACRO(COMMON_GET_LIBRARY_DIR_INFO DEPNAME dir_lib dir_bin)
    
    SET(options VERSIONED_LIB VERSION_LIB)
    SET(oneValueArgs PLATFORM BIT)
    SET(multiValueArgs)
    
    cmake_parse_arguments(${DEPNAME} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    #COMMON_CHECK_DEBUG_MSG("   COMMON_GET_LIBRARY_DIR_INFO-->${DEPNAME}<-->${ARGN}" ${ARGN})
    #COMMON_CHECK_DEBUG_MSG("   ~~${DEPNAME}_VERSIONED_LIB:${${DEPNAME}_VERSIONED_LIB}" ${ARGN})        
    #COMMON_CHECK_DEBUG_MSG("   ${DEPNAME}_PLATFORM:${${DEPNAME}_PLATFORM}")
    #COMMON_CHECK_DEBUG_MSG(" ${DEPNAME}_UNPARSED_ARGUMENTS:${_${DEPNAME}_UNPARSED_ARGUMENTS}")
    
    if(NOT ${DEPNAME}_PLATFORM)
        #COMMON_CHECK_DEBUG_MSG("     Default PLATFORM WIN32" ${ARGN})
        SET(${DEPNAME}_PLATFORM WIN32)
    else()
        STRING(TOUPPER ${${DEPNAME}_PLATFORM} ${DEPNAME}_PLATFORM)
    endif()
    
    # if(NOT ${DEPNAME}_BIT)
        # COMMON_CHECK_DEBUG_MSG("     Default BIT X86" ${ARGN})
        # SET(${DEPNAME}_BIT "X86")
    # endif()

    set(_tmp_lib_dir)
    set(_tmp_bin_dir)

    if(${${DEPNAME}_PLATFORM} STREQUAL WIN32)
        #COMMON_CHECK_DEBUG_MSG("     ~~~Use PlatForm ${${DEPNAME}_PLATFORM}" ${ARGN})
        IF(${DEPNAME}_VERSIONED_LIB OR ${DEPNAME}_VERSION_LIB)
           COMMON_GET_VERSION_LIB_DIR(_tmp_lib_dir)
           COMMON_GET_VERSION_BIN_DIR(_tmp_bin_dir)
        ELSE()
            set(_tmp_lib_dir "lib")
            set(_tmp_bin_dir "bin")
        ENDIF()
    else()
        MESSAGE(FATAL_ERROR "Not Support The PlatForm Of ${${DEPNAME}_PLATFORM}")
    endif()
    
    #COMMON_CHECK_DEBUG_MSG("2.....${${DEPNAME}_LIB_SERARTH_DIR}" ${ARGN})
    #X86 or X64
    #make the x64 lib /bin dir,
    IF(CMAKE_CL_64)
        SET(${DEPNAME}_BIT X64)
    ELSE(CMAKE_CL_64)
        SET(${DEPNAME}_BIT X86)
    ENDIF(CMAKE_CL_64)

    #when bit is x86, default lib dir not changed,
    #if bit is x64, then the dir will change to %{dir}/x64.
    IF(NOT ${${DEPNAME}_BIT} STREQUAL "X86")
        STRING(CONCAT _tmp_lib_dir ${_tmp_lib_dir} "/x64")
        STRING(CONCAT _tmp_bin_dir ${_tmp_bin_dir} "/x64")
    endif()
    
     COMMON_CHECK_DEBUG_MSG("    COMMON_GET_LIBRARY_DIR_INFO:
         dir_lib=${_tmp_lib_dir}
         dir_bin=${_tmp_bin_dir}" ${ARGN})
    
    SET(${dir_lib} ${_tmp_lib_dir})
    SET(${dir_bin} ${_tmp_bin_dir})
ENDMACRO()