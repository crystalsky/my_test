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

MACRO(FIND_DEPENDENCY DEPNAME INCLUDEFILE LIBRARY_NAMES_BASE SEARCHPATHLIST DEBUGSUFFIX EXSUFFIX)
	#remove the DUPLICATES of the SEARCHPATHLIST
	set(_search_pathes ${SEARCHPATHLIST})
	list(REMOVE_DUPLICATES _search_pathes)
	
	MESSAGE(STATUS "searching ${DEPNAME} -->${INCLUDEFILE}<-->${LIBRARY_NAMES_BASE}<-->${_search_pathes}<-->${DEBUGSUFFIX}<--")
	 
	SET(${DEPNAME}_LIB_SERARTH_DIR "lib")
	
	SET(${DEPNAME}_MSVC_VERION_LIB ${ARGV6})
	SET(TEMP_${DEPNAME}_LIB_SERARTH_DIR ${${DEPNAME}_LIB_SERARTH_DIR})
	IF(${DEPNAME}_MSVC_VERION_LIB)
		IF (WIN32)
			IF (MSVC)
				IF(MSVC12)
					SET(TEMP_${DEPNAME}_LIB_SERARTH_DIR "lib/vc120")
				ELSEIF(MSVC11)
					SET(TEMP_${DEPNAME}_LIB_SERARTH_DIR "lib/vc110")
				ELSEIF(MSVC10)
					SET(TEMP_${DEPNAME}_LIB_SERARTH_DIR "lib/vc100")
				ELSEIF(MSVC90)
					SET(TEMP_${DEPNAME}_LIB_SERARTH_DIR "lib/vc90")
				ELSEIF(MSVC80)
					SET(TEMP_${DEPNAME}_LIB_SERARTH_DIR "lib/vc80")
				ENDIF()
			ENDIF(MSVC)
		ENDIF()
	ENDIF()
	
	if(NOT ${TEMP_${DEPNAME}_LIB_SERARTH_DIR} STREQUAL ${${DEPNAME}_LIB_SERARTH_DIR})
		SET(${DEPNAME}_LIB_SERARTH_DIR ${TEMP_${DEPNAME}_LIB_SERARTH_DIR})
		MESSAGE(STATUS "searching ${DEPNAME} Library File At ${${DEPNAME}_LIB_SERARTH_DIR}")
	endif()
	
    SET(MY_PATH_INCLUDE )
    SET(MY_PATH_LIB )
    
    FOREACH( MYPATH ${_search_pathes} )
        SET(MY_PATH_INCLUDE ${MY_PATH_INCLUDE} ${MYPATH}/include)
        SET(MY_PATH_LIB ${MY_PATH_LIB} ${MYPATH}/${${DEPNAME}_LIB_SERARTH_DIR})
    ENDFOREACH()
    
	#IncludeDir
    FIND_PATH("${DEPNAME}_INCLUDE_DIR" ${INCLUDEFILE}
      ${MY_PATH_INCLUDE}
      NO_DEFAULT_PATH
    )
    MARK_AS_ADVANCED("${DEPNAME}_INCLUDE_DIR")
    #MESSAGE( " ${DEPNAME}_INCLUDE_DIR --> ${${DEPNAME}_INCLUDE_DIR}<--")
    
    SET(LIBRARY_NAMES "")
    FOREACH(LIBNAME ${LIBRARY_NAMES_BASE})
        LIST(APPEND LIBRARY_NAMES "${LIBNAME}${EXSUFFIX}")
    ENDFOREACH(LIBNAME)
	#MESSAGE( " LIBRARY_NAMES --> ${LIBRARY_NAMES}<--")
	
	#Release Lib
    FIND_LIBRARY("${DEPNAME}_LIBRARY"
        NAMES ${LIBRARY_NAMES}
      PATHS ${MY_PATH_LIB}
      NO_DEFAULT_PATH
    )
	MARK_AS_ADVANCED("${DEPNAME}_LIBRARY")
    #MESSAGE( " ${DEPNAME}_LIBRARY --> ${${DEPNAME}_LIBRARY}<--")
	
	
	#Debug Lib
    SET(LIBRARY_NAMES_DEBUG "")
    FOREACH(LIBNAME ${LIBRARY_NAMES_BASE})
        LIST(APPEND LIBRARY_NAMES_DEBUG "${LIBNAME}${DEBUGSUFFIX}${EXSUFFIX}")
    ENDFOREACH(LIBNAME)
	#MESSAGE( " LIBRARY_NAMES_DEBUG --> ${LIBRARY_NAMES_DEBUG}<--")
	
    FIND_LIBRARY("${DEPNAME}_LIBRARY_DEBUG" 
        NAMES ${LIBRARY_NAMES_DEBUG}
      PATHS ${MY_PATH_LIB}
      NO_DEFAULT_PATH
    )
    
    SET( ${DEPNAME}_FOUND "NO" )
    IF(${DEPNAME}_INCLUDE_DIR AND ${DEPNAME}_LIBRARY)
      SET( ${DEPNAME}_FOUND "YES" )
      IF(NOT ${DEPNAME}_LIBRARY_DEBUG)
          MESSAGE("-- Warning Debug ${DEPNAME} not found, using: ${${DEPNAME}_LIBRARY}")
          SET(${DEPNAME}_LIBRARY_DEBUG "${${DEPNAME}_LIBRARY}")
      ENDIF(NOT ${DEPNAME}_LIBRARY_DEBUG)
    ENDIF(${DEPNAME}_INCLUDE_DIR AND ${DEPNAME}_LIBRARY)
	
	MARK_AS_ADVANCED("${DEPNAME}_LIBRARY_DEBUG")
    #MESSAGE( " ${DEPNAME}_LIBRARY_DEBUG --> ${${DEPNAME}_LIBRARY_DEBUG}<--")
ENDMACRO()

#===================================================
include(util.common_get_library_folder)
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

    #DEBUG_MESSAGE(" ~~${DEPNAME}_VERSIONED_LIB:${${DEPNAME}_VERSIONED_LIB}")        
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
    
    #get the dir of the library..
    COMMON_GET_LIBRARY_DIR_INFO(${DEPNAME} 
        _${DEPNAME}_LIB_SERARTH_DIR 
        _${DEPNAME}_BIN_SERARTH_DIR
        ${ARGN}
    )
    DEBUG_MESSAGE("   ~~~:Searching Dir Of ${_${DEPNAME}_LIB_SERARTH_DIR} ${_${DEPNAME}_BIN_SERARTH_DIR}")
    
    SET(${DEPNAME}_LIB_SERARTH_DIR ${_${DEPNAME}_LIB_SERARTH_DIR})
    SET(${DEPNAME}_BIN_SERARTH_DIR ${_${DEPNAME}_BIN_SERARTH_DIR})
ENDMACRO()

MACRO(FIND_DEPENDENCY_EX DEPNAME INCLUDEFILE LIBRARY_NAMES_BASE)
    
    _Analyse_Dependency_Arguments(${DEPNAME} ${ARGN})
    
    #remove the DUPLICATES
    set(_search_pathes ${${DEPNAME}_PATHS} ${${DEPNAME}_UNPARSED_ARGUMENTS})
    list(REMOVE_DUPLICATES _search_pathes)
    
    DEBUG_MESSAGE("   ~~~Searching Dependencies Of ${DEPNAME}: 
      *Include File:${INCLUDEFILE} 
      *Library Name:${LIBRARY_NAMES_BASE}
      *Search Paths:${_search_pathes}
      *Library Path:${${DEPNAME}_LIB_SERARTH_DIR}
      *Debug Suffix:${${DEPNAME}_DEBUGSUFFIX}
      *EXSUFFIX:${${DEPNAME}_EXSUFFIX}")
    
    SET(MY_PATH_INCLUDE )
    SET(MY_PATH_LIB )
    
    FOREACH( MYPATH ${_search_pathes} )
        SET(MY_PATH_INCLUDE ${MY_PATH_INCLUDE} ${MYPATH}/include)
        
        SET(_temp_lib_path ${MYPATH}/${${DEPNAME}_LIB_SERARTH_DIR})
        IF(NOT EXISTS ${_temp_lib_path})
            GET_FILENAME_COMPONENT(_temp_lib_path ${_temp_lib_path} PATH)
        ENDIF()
        SET(MY_PATH_LIB ${MY_PATH_LIB} ${_temp_lib_path})
    ENDFOREACH()
    
    #IncludeDir
    FIND_PATH("${DEPNAME}_INCLUDE_DIR" ${INCLUDEFILE}
      ${MY_PATH_INCLUDE}
      NO_DEFAULT_PATH
    )
    MARK_AS_ADVANCED("${DEPNAME}_INCLUDE_DIR")
    #DEBUG_MESSAGE( " ${DEPNAME}_INCLUDE_DIR --> ${${DEPNAME}_INCLUDE_DIR}<--")
    
    SET(LIBRARY_NAMES "")
    FOREACH(LIBNAME ${LIBRARY_NAMES_BASE})
        LIST(APPEND LIBRARY_NAMES "${LIBNAME}${${DEPNAME}_EXSUFFIX}")
    ENDFOREACH(LIBNAME)
    #DEBUG_MESSAGE( " LIBRARY_NAMES --> ${LIBRARY_NAMES}<--")
    
    #Release Lib
    FIND_LIBRARY("${DEPNAME}_LIBRARY"
        NAMES ${LIBRARY_NAMES}
      PATHS ${MY_PATH_LIB}
      NO_DEFAULT_PATH
    )
    MARK_AS_ADVANCED("${DEPNAME}_LIBRARY")
    #DEBUG_MESSAGE( " ${DEPNAME}_LIBRARY --> ${${DEPNAME}_LIBRARY}<--")
    
    #Debug Lib
    SET(LIBRARY_NAMES_DEBUG "")
    FOREACH(LIBNAME ${LIBRARY_NAMES_BASE})
        LIST(APPEND LIBRARY_NAMES_DEBUG "${LIBNAME}${${DEPNAME}_DEBUGSUFFIX}${${DEPNAME}_EXSUFFIX}")
    ENDFOREACH(LIBNAME)
    DEBUG_MESSAGE( " LIBRARY_NAMES_DEBUG --> ${LIBRARY_NAMES_DEBUG}<--")
    
    FIND_LIBRARY("${DEPNAME}_LIBRARY_DEBUG" 
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
    #DEBUG_MESSAGE( " ${DEPNAME}_LIBRARY_DEBUG --> ${${DEPNAME}_LIBRARY_DEBUG}<--")
ENDMACRO()

#find the include dir
MACRO(FIND_DEPEND_INCLUDE_DIR DEPNAME include_file)
    STRING(TOUPPER ${DEPNAME} DEPNAME)

    SET(options)
    SET(oneValueArgs)
    SET(multiValueArgs PATHS)
    
    cmake_parse_arguments(${DEPNAME} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})
    
    #remove the DUPLICATES
    set(_search_pathes ${${DEPNAME}_PATHS} ${${DEPNAME}_UNPARSED_ARGUMENTS})
    list(REMOVE_DUPLICATES _search_pathes)

    FIND_PATH(_${DEPNAME}_TMP_PATH ${include_file}
      HINTS
            ${_search_pathes}
      PATH_SUFFIXES 
            include
            inc
      #NO_DEFAULT_PATH
    )
    SET(${DEPNAME}_INCLUDE_DIR ${_${DEPNAME}_TMP_PATH})
    MARK_AS_ADVANCED(${DEPNAME}_INCLUDE_DIR)
    MESSAGE(STATUS "      A:Get ${DEPNAME}_INCLUDE_DIR=${${DEPNAME}_INCLUDE_DIR}")

    #get the real dir
    set(_cur_include_file ${${DEPNAME}_INCLUDE_DIR}/${include_file})
    IF(EXISTS ${_cur_include_file})
        #MESSAGE(STATUS "    ${_cur_include_file}")
        
        #get the dir name
        string(REGEX REPLACE "\(.*\)/.*" \\1 _dir_name ${include_file})
        #string(REPLACE "/" "\\" _dir_name ${_dir_name})
        STRING(TOUPPER ${_dir_name} _dir_name)
        #MESSAGE(STATUS "    1.${_dir_name}")

        if(${_dir_name} STREQUAL ${DEPNAME})
            STRING(TOUPPER ${include_file} _upper_include_file)
             #get the include file name..
            string(REGEX REPLACE ${_dir_name}/\(.*\) \\1 _file_name ${_upper_include_file})
            #MESSAGE(STATUS "    2.${_file_name} = ${_upper_include_file}")

            FIND_PATH(_${DEPNAME}_TMP_PATH2 ${_file_name}
                HINTS
                    ${_search_pathes}
                PATH_SUFFIXES 
                    include/${DEPNAME}
                NO_DEFAULT_PATH
            )
            SET(${DEPNAME}_${DEPNAME}_INCLUDE_DIR ${_${DEPNAME}_TMP_PATH2})

            if(EXISTS ${${DEPNAME}_${DEPNAME}_INCLUDE_DIR})
                MARK_AS_ADVANCED(${DEPNAME}_${DEPNAME}_INCLUDE_DIR)
                #set(${DEPNAME}_INCLUDE_DIR 
                     #${${DEPNAME}_INCLUDE_DIR} 
                     #${${DEPNAME}_${DEPNAME}_INCLUDE_DIR}
                #)
                MESSAGE(STATUS "      B:Get ${DEPNAME}_${DEPNAME}_INCLUDE_DIR..")
            endif()
        endif()
    ENDIF()
ENDMACRO()


MACRO(FIND_DEPEND_LIBRARY DEPNAME LIBRARY_NAMES_BASE)
    _Analyse_Dependency_Arguments(${DEPNAME} ${ARGN})
    
    SET(options)
    SET(oneValueArgs BIN_SUFFIX)
    SET(multiValueArgs PATHS)
    
    cmake_parse_arguments(${DEPNAME} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    set(_search_pathes ${${DEPNAME}_PATHS} ${_${DEPNAME}_UNPARSED_ARGUMENTS})
	list(REMOVE_DUPLICATES _search_pathes)

    #MESSAGE(STATUS "   ~~~Searching Dependencies Of ${DEPNAME}: 
    #  *Library Name:${LIBRARY_NAME_BASE}
    #  *Search Paths:${_search_pathes}
    #  *Library Path:${${DEPNAME}_LIB_SERARTH_DIR}
    #  *Debug Suffix:${${DEPNAME}_DEBUGSUFFIX}
    #  *EXSUFFIX:${${DEPNAME}_EXSUFFIX}")
    #IF(${DEPNAME}_BIN_SUFFIX)
    #    #MESSAGE(STATUS "      ${DEPNAME}_BIN_SUFFIX:${${DEPNAME}_BIN_SUFFIX}")
    #ENDIF()
   
    #DEBUG_MESSAGE(" ${DEPNAME}_PATHS:")
    #DEBUG_MESSAGE(" ${DEPNAME}_UNPARSED_ARGUMENTS:${_${DEPNAME}_UNPARSED_ARGUMENTS}")

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
    MARK_AS_ADVANCED(${DEPNAME}_LIBRARY)
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
    
    #if find the release library and not find the debug library,
    #then set the debug library to release library.
    IF(${DEPNAME}_LIBRARY AND NOT ${DEPNAME}_LIBRARY_DEBUG)
          MESSAGE("    -- Warning Debug ${DEPNAME} not found, using: ${${DEPNAME}_LIBRARY}")
          SET(${DEPNAME}_LIBRARY_DEBUG ${${DEPNAME}_LIBRARY})
    ENDIF()

    SET( ${DEPNAME}_FOUND "NO" )
    IF(${DEPNAME}_INCLUDE_DIR AND ${DEPNAME}_LIBRARY)
      SET( ${DEPNAME}_FOUND "YES" )
    ENDIF()
    
    MARK_AS_ADVANCED(${DEPNAME}_LIBRARY_DEBUG)
    #MESSAGE(STATUS " ${DEPNAME}_LIBRARY_DEBUG --> ${${DEPNAME}_LIBRARY_DEBUG}<--")
ENDMACRO()