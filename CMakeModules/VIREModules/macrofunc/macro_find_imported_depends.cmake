################################################################################################
# this Macro find a generic dependency, handling debug suffix
# all the paramenter are required, in case of lists, use "" in calling
###############################################################	#################################
#宏参数说明：
#DEPNAME：指名变量名，当找到对应的 #{DEPNAME}_FOUND就会为真
#INCLUDEFILE：头文件名
#LIBRARY_NAMES_BASE:库文件名（不含扩展名"libjpeg;jpeg;..."）
#SEARCHPATHLIST：搜索路径（用';'区分 "a:/debug;d:/my;..."）
#DEBUGSUFFIX:库后缀名，一般说来Debug和Release有不同的后缀 Debug:"d"/"D"
#EXSUFFIX:名扩展 一般说为空""，也可以为"_i"(有些库名带有不同的后缀名)
###
#FIND_DEPENDENCY(GDAL gdal.h "gdal;gdal16" ${OSG_3RDPARTY_BIN} "d" "_i")
#FIND_DEPENDENCY(GLUT GL/glut.h glut32 ${OSG_3RDPARTY_BIN} "D" "")
###
#======注意：以下的参数取值不能随意更改
#${ARGV6} 为是否需要用vc版本的查找库文件 ON/OFF


MACRO(_Analyse_Dependency_Arguments DEPNAME)
    
    #DEBUG_MESSAGE(" _Analyse_Dependency_Arguments-->${DEPNAME}<-->${ARGN}")
    
    SET(options VERSIONED_LIB)
    SET(oneValueArgs PLATFORM DEBUGSUFFIX EXSUFFIX)
    SET(multiValueArgs PATHS)
    
    cmake_parse_arguments(${DEPNAME} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    DEBUG_MESSAGE(" ~~${DEPNAME}_VERSIONED_LIB:${${DEPNAME}_VERSIONED_LIB}")        
    #DEBUG_MESSAGE(" ${DEPNAME}_PLATFORM:${${DEPNAME}_PLATFORM}")
    #DEBUG_MESSAGE(" ${DEPNAME}_BIT:${${DEPNAME}_BIT}")
    #DEBUG_MESSAGE(" ${DEPNAME}_PATHS:${${DEPNAME}_PATHS}")
    #DEBUG_MESSAGE(" ${DEPNAME}_UNPARSED_ARGUMENTS:${_${DEPNAME}_UNPARSED_ARGUMENTS}")
    
    if(NOT ${DEPNAME}_PLATFORM)
        DEBUG_MESSAGE("   Default PLATFORM WIN32")
        SET(${DEPNAME}_PLATFORM WIN32)
    else()
        STRING(TOUPPER ${${DEPNAME}_PLATFORM} ${DEPNAME}_PLATFORM)
    endif()
    
    if(NOT ${DEPNAME}_VERSIONED_LIB)
        DEBUG_MESSAGE("   Default VERSIONED_LIB FALSE")
        SET(${DEPNAME}_VERSIONED_LIB FALSE)
    endif()
    
    if(NOT ${DEPNAME}_DEBUGSUFFIX)
        DEBUG_MESSAGE("   Default DEBUGSUFFIX d")
        SET(${DEPNAME}_DEBUGSUFFIX "d")
    endif()
    
    SET(${DEPNAME}_LIB_SERARTH_DIR "lib")
    SET(${DEPNAME}_BIN_SERARTH_DIR "bin")
    #MESSAGE("1.....${${DEPNAME}_LIB_SERARTH_DIR}")
    SET(_${DEPNAME}_LIB_SERARTH_DIR ${${DEPNAME}_LIB_SERARTH_DIR})
    SET(_${DEPNAME}_BIN_SERARTH_DIR ${${DEPNAME}_BIN_SERARTH_DIR})
    if(${${DEPNAME}_PLATFORM} STREQUAL WIN32)
        DEBUG_MESSAGE("   ~~~Use PlatForm ${${DEPNAME}_PLATFORM}")
        IF(${DEPNAME}_VERSIONED_LIB)
            IF (MSVC)
                DEBUG_MESSAGE("   Use MSVC Versioned Lib...")
                IF(MSVC12)
                    SET(_${DEPNAME}_LIB_SERARTH_DIR "lib/vc120")
                    SET(_${DEPNAME}_BIN_SERARTH_DIR "bin/vc120")
                ELSEIF(MSVC11)
                    SET(_${DEPNAME}_LIB_SERARTH_DIR "lib/vc110")
                    SET(_${DEPNAME}_BIN_SERARTH_DIR "bin/vc110")
                ELSEIF(MSVC10)
                    SET(_${DEPNAME}_LIB_SERARTH_DIR "lib/vc100")
                    SET(_${DEPNAME}_BIN_SERARTH_DIR "bin/vc100")
                ELSEIF(MSVC90)
                    SET(_${DEPNAME}_LIB_SERARTH_DIR "lib/vc90")
                    SET(_${DEPNAME}_BIN_SERARTH_DIR "bin/vc90")
                ELSEIF(MSVC80)
                    SET(_${DEPNAME}_LIB_SERARTH_DIR "lib/vc80")
                    SET(_${DEPNAME}_BIN_SERARTH_DIR "bin/vc80")
                ENDIF()
            ELSE()
                
            ENDIF(MSVC)
            
        ENDIF()
    else()
        MESSAGE(FATAL_ERROR "Not Support The PlatForm Of ${${DEPNAME}_PLATFORM}")
    endif()
    
    #DEBUG_MESSAGE("2.....${${DEPNAME}_LIB_SERARTH_DIR}")
    #X86 or X64
    IF(CMAKE_CL_64)
        SET(${DEPNAME}_BIT X64)
    ELSE(CMAKE_CL_64)
        SET(${DEPNAME}_BIT X86)
    ENDIF(CMAKE_CL_64)
    IF(NOT ${${DEPNAME}_BIT} STREQUAL "X86")
        STRING(CONCAT _${DEPNAME}_LIB_SERARTH_DIR ${_${DEPNAME}_LIB_SERARTH_DIR} "/x64")
        STRING(CONCAT _${DEPNAME}_BIN_SERARTH_DIR ${_${DEPNAME}_BIN_SERARTH_DIR} "/x64")
    endif()
    
    SET(${DEPNAME}_LIB_SERARTH_DIR ${_${DEPNAME}_LIB_SERARTH_DIR})
    SET(${DEPNAME}_BIN_SERARTH_DIR ${_${DEPNAME}_BIN_SERARTH_DIR})
ENDMACRO()

MACRO(FIND_IMPORTED_DEPENDS DEPNAME inc_file_name)
    string(TOUPPER ${DEPNAME} _uppered_name)

    SET(options FindParentDir)
    SET(oneValueArgs)
    SET(multiValueArgs PATHS)
    
    cmake_parse_arguments(${DEPNAME} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

   
    



    MESSAGE(STATUS "Find Library In ${${THIS_LIB_DEPEND_NAME}_DIR}..${inc_file_name}")
    IF (WIN32)
        COMMON_GET_MSVC_VERSION_LIB_DIR(libdir)

        FIND_PATH(ICE_${_uppered_name}_INCLUDE_DIR 
            ${inc_file_name}
            PATHS ${${THIS_LIB_DEPEND_NAME}_DIR}
            PATH_SUFFIXES include/${_uppered_name}
            DOC "The directory where ice.h resides")

        FIND_LIBRARY(${_uppered_name}_LIBRARY_DEBUG
            NAMES ${libname}d
            PATHS "${${THIS_LIB_DEPEND_NAME}_DIR}"
            PATH_SUFFIXES ${libdir}
            DOC "The ${libname} Debug library")

        FIND_LIBRARY(${_uppered_name}_LIBRARY
            NAMES ${libname}
            PATHS "${${THIS_LIB_DEPEND_NAME}_DIR}"
            PATH_SUFFIXES ${libdir}
            DOC "The ${libname} Release library")

        FIND_PACKAGE_HANDLE_STANDARD_ARGS(${_uppered_name}
            FOUND_VAR ${_uppered_name}_FOUND 	
            REQUIRED_VARS ${_uppered_name}_INCLUDE_DIR 
            ${_uppered_name}_LIBRARY 
            ${_uppered_name}_LIBRARY_DEBUG
        )

        IF(NOT ${_uppered_name}_FOUND)
            MESSAGE(FATAL_ERROR "--${_uppered_name} not found")
        ENDIF(NOT ${_uppered_name}_FOUND)

        if(${_uppered_name}_FOUND)
            set(${_uppered_name}_LIBRARIES ${${_uppered_name}_LIBRARY_DEBUG} ${${_uppered_name}_LIBRARY})
            COMMON_MAKE_IMPORT_TARGET_BASE(${THIS_LIB_DEPEND_NAME} ${_uppered_name}
                ${ICE_${_uppered_name}_INCLUDE_DIR}
                ${${_uppered_name}_LIBRARY_DEBUG}
                ${${_uppered_name}_LIBRARY}
            )
        endif()

        mark_as_advanced(
            ${_uppered_name}_INCLUDE_DIR
            ${_uppered_name}_LIBRARY_DEBUG
            ${_uppered_name}_LIBRARY
        )
    ELSE ()
        
    ENDIF ()
ENDMACRO()



#find the include dir
MACRO(_FIND_DEPEND_INCLUDE_DIR DEPNAME include_file)
    SET(options FindParentDir)
    SET(oneValueArgs)
    SET(multiValueArgs PATHS )
    
    cmake_parse_arguments(${DEPNAME} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})
    
    #remove the DUPLICATES
    set(_search_pathes ${${DEPNAME}_PATHS} ${${DEPNAME}_UNPARSED_ARGUMENTS})
    list(REMOVE_DUPLICATES _search_pathes)
    
   #MESSAGE(STATUS "   ~~~Searching Include Of ${DEPNAME}: 
   #  *Include File:${include_file} 
   #  *Search Paths:${_search_pathes}"
   #  )
    
    #SET(MY_PATH_INCLUDE )

    #FOREACH( MYPATH ${_search_pathes} )
        #SET(MY_PATH_INCLUDE ${MY_PATH_INCLUDE} ${MYPATH}/include)
    #ENDFOREACH()
    
    #IncludeDir Finding
    FIND_PATH(${DEPNAME}_INCLUDE_DIR ${include_file}
      HINTS
            ${_search_pathes}
      PATH_SUFFIXES 
            include
            inc
            include/${DEPNAME}
      #NO_DEFAULT_PATH
    )
    MESSAGE(STATUS "       ${DEPNAME}_INCLUDE_DIR = ${${DEPNAME}_INCLUDE_DIR}")
    MARK_AS_ADVANCED(${DEPNAME}_INCLUDE_DIR)
ENDMACRO()

MACRO(_FIND_DEPEND_LIBRARY DEPNAME LIBRARY_NAMES_BASE)
    
    _Analyse_Dependency_Arguments(${DEPNAME} ${ARGN})
    

    SET(options)
    SET(oneValueArgs BIN_SUFFIX)
    SET(multiValueArgs PATHS)
    
    cmake_parse_arguments(${DEPNAME} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})
    #MESSAGE(STATUS "   ~~~Searching Dependencies Of ${DEPNAME}: 
    #  *Library Name:${LIBRARY_NAME_BASE}
    #  *Search Paths:${_search_pathes}
    #  *Library Path:${${DEPNAME}_LIB_SERARTH_DIR}
    #  *Debug Suffix:${${DEPNAME}_DEBUGSUFFIX}
    #  *EXSUFFIX:${${DEPNAME}_EXSUFFIX}")
    #IF(${DEPNAME}_BIN_SUFFIX)
    #    #MESSAGE(STATUS "      ${DEPNAME}_BIN_SUFFIX:${${DEPNAME}_BIN_SUFFIX}")
    #ENDIF()
   
    SET(MY_PATH_LIB )
    SET(MY_PATH_BIN )
    FOREACH( MYPATH ${_search_pathes} )
        SET(_temp_lib_path ${MYPATH}/${${DEPNAME}_LIB_SERARTH_DIR})
        SET(_temp_bin_path ${MYPATH}/${${DEPNAME}_BIN_SERARTH_DIR})
        #MESSAGE(STATUS " _temp_lib_path --> ${_temp_lib_path}<--")
        IF(NOT EXISTS ${_temp_lib_path})
            GET_FILENAME_COMPONENT(_temp_lib_path ${_temp_lib_path} PATH)
        ENDIF()
        SET(MY_PATH_LIB ${MY_PATH_LIB} ${_temp_lib_path})
        SET(MY_PATH_BIN ${MY_PATH_BIN} ${_temp_bin_path})
    ENDFOREACH()
    #MESSAGE(STATUS "      MY_PATH_BIN --> ${MY_PATH_BIN}<--")

    SET(LIBRARY_NAMES "")
    FOREACH(LIBNAME ${LIBRARY_NAMES_BASE})
        LIST(APPEND LIBRARY_NAMES "${LIBNAME}${${DEPNAME}_EXSUFFIX}")
    ENDFOREACH()
    #MESSAGE(STATUS " LIBRARY_NAMES --> ${LIBRARY_NAMES}<--")
    

    #{Begin Release
    #{Begin Lib
    FIND_LIBRARY(${DEPNAME}_LIBRARY
        NAMES ${LIBRARY_NAMES}
      PATHS ${MY_PATH_LIB}
      NO_DEFAULT_PATH
    )
    #MESSAGE(STATUS "      ${DEPNAME}_LIBRARY --> ${${DEPNAME}_LIBRARY}<--")
    MARK_AS_ADVANCED("${DEPNAME}_LIBRARY")
    #}End Lib
    
    #{Begin Bin

    #SET(${DEPNAME}_BIN_RELEASE ${LIBRARY_NAMES}${${DEPNAME}_BIN_SUFFIX}.dll)
    #MESSAGE(STATUS "      Find Bin File:[${${DEPNAME}_BIN_RELEASE}] ...")
    #SET(_BIN "")
    #find_file(_BIN
    #    ${${DEPNAME}_BIN_RELEASE}
    #    ${MY_PATH_BIN}
    #    )
    #SET(${DEPNAME}_BIN ${_BIN})
    #MESSAGE(STATUS "        ${DEPNAME}_BIN At: ${_temp_BIN}") 
    #}End Bin
    
    #}End Release

    #=============Debug Lib
    SET(LIBRARY_NAMES_DEBUG "")
    FOREACH(LIBNAME ${LIBRARY_NAMES_BASE})
        LIST(APPEND LIBRARY_NAMES_DEBUG "${LIBNAME}${${DEPNAME}_DEBUGSUFFIX}${${DEPNAME}_EXSUFFIX}")
    ENDFOREACH(LIBNAME)
    #MESSAGE(STATUS " LIBRARY_NAMES_DEBUG --> ${LIBRARY_NAMES_DEBUG}<--")
    
    FIND_LIBRARY(${DEPNAME}_LIBRARY_DEBUG
        NAMES ${LIBRARY_NAMES_DEBUG}
        PATHS ${MY_PATH_LIB}
        NO_DEFAULT_PATH
    )
    
    SET( ${DEPNAME}_FOUND "NO" )
    IF(${DEPNAME}_INCLUDE_DIR AND ${DEPNAME}_LIBRARY)
      SET( ${DEPNAME}_FOUND "YES" )
      IF(NOT ${DEPNAME}_LIBRARY_DEBUG)
          MESSAGE("    -- Warning Debug ${DEPNAME} not found, using: ${${DEPNAME}_LIBRARY}")
          SET(${DEPNAME}_LIBRARY_DEBUG "${${DEPNAME}_LIBRARY}")
      ENDIF(NOT ${DEPNAME}_LIBRARY_DEBUG)
    ENDIF(${DEPNAME}_INCLUDE_DIR AND ${DEPNAME}_LIBRARY)
    
    MARK_AS_ADVANCED("${DEPNAME}_LIBRARY_DEBUG")
    #MESSAGE(STATUS " ${DEPNAME}_LIBRARY_DEBUG --> ${${DEPNAME}_LIBRARY_DEBUG}<--")
ENDMACRO()


