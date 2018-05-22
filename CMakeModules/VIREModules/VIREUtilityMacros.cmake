include(UtilityMacros)
include(_macro_vire_include)
#===================================================================================
# Where is this and what do we need it for?
MACRO(FILTER_OUT FILTERS INPUTS OUTPUT)
     # Mimicks Gnu Make's $(filter-out) which removes elements 
     # from a list that match the pattern.
     # Arguments:
     #  FILTERS - list of patterns that need to be removed
     #  INPUTS  - list of inputs that will be worked on
     #  OUTPUT  - the filtered list to be returned
     # 
     # Example: 
     #  SET(MYLIST this that and the other)
     #  SET(FILTS this that)
     #
     #  FILTER_OUT("${FILTS}" "${MYLIST}" OUT)
     #  MESSAGE("OUTPUT = ${OUT}")
     #
     # The output - 
     #   OUTPUT = and;the;other
     #
     SET(FOUT "")
     FOREACH(INP ${INPUTS})
         SET(FILTERED 0)
         FOREACH(FILT ${FILTERS})
             IF(${FILTERED} EQUAL 0)
                 IF("${FILT}" STREQUAL "${INP}")
                     SET(FILTERED 1)
                 ENDIF("${FILT}" STREQUAL "${INP}")
             ENDIF(${FILTERED} EQUAL 0)
         ENDFOREACH(FILT ${FILTERS})
         IF(${FILTERED} EQUAL 0)
             SET(FOUT ${FOUT} ${INP})
         ENDIF(${FILTERED} EQUAL 0)
     ENDFOREACH(INP ${INPUTS})
     SET(${OUTPUT} ${FOUT})
 ENDMACRO(FILTER_OUT FILTERS INPUTS OUTPUT)


 MACRO(GET_HEADERS_EXTENSIONLESS DIR GLOB_PATTERN OUTPUT)
          FILE(GLOB TMP "${DIR}/${GLOB_PATTERN}" )
    #FOREACH(F ${TMP})
          #    DEBUG_MESSAGE( "header-->${F}<--")
    #ENDFOREACH(F ${TMP})
          FILTER_OUT("${DIR}/CVS" "${TMP}" TMP)
          FILTER_OUT("${DIR}/cvs" "${TMP}" ${OUTPUT})
          FILTER_OUT("${DIR}/.svn" "${TMP}" ${OUTPUT})
 ENDMACRO(GET_HEADERS_EXTENSIONLESS DIR GLOB_PATTERN OUTPUT)
   
MACRO(ADD_DIRS_TO_ENV_VAR _VARNAME )
 FOREACH(_ADD_PATH ${ARGN}) 
    FILE(TO_NATIVE_PATH ${_ADD_PATH} _ADD_NATIVE)
    #SET(_CURR_ENV_PATH $ENV{PATH})
    #LIST(SET _CURR_ENV_PATH ${_ADD_PATH})
    #SET(ENV{PATH} ${_CURR_ENV_PATH})${_FILE}
    IF(WIN32)
        SET(ENV{${_VARNAME}} "$ENV{${_VARNAME}};${_ADD_NATIVE}")
    ELSE(WIN32)
        SET(ENV{${_VARNAME}} "$ENV{${_VARNAME}}:${_ADD_NATIVE}")
    ENDIF(WIN32)
    #MESSAGE(" env ${_VARNAME} --->$ENV{${_VARNAME}}<---")
 ENDFOREACH(_ADD_PATH)
ENDMACRO(ADD_DIRS_TO_ENV_VAR _VARNAME )

MACRO(TARGET_LOCATIONS_SET_FILE FILE)
 SET(ACCUM_FILE_TARGETS ${FILE})
 FILE(WRITE ${ACCUM_FILE_TARGETS} "")
ENDMACRO(TARGET_LOCATIONS_SET_FILE FILE)

MACRO(TARGET_LOCATIONS_ACCUM TARGET_NAME)
 IF(ACCUM_FILE_TARGETS)
  IF(EXISTS ${ACCUM_FILE_TARGETS})
    GET_TARGET_PROPERTY(_FILE_LOCATION ${TARGET_NAME} LOCATION)
    FILE(APPEND ${ACCUM_FILE_TARGETS} "${_FILE_LOCATION};")
    #SET(_TARGETS_LIST ${_TARGETS_LIST} "${_FILE_LOCATION}" CACHE INTERNAL "lista dll")
    #MESSAGE("adding target -->${TARGET_NAME}<-- file -->${_FILE_LOCATION}<-- to list -->${_TARGETS_LIST}<--")
    #SET(ACCUM_FILE_TARGETS ${ACCUM_FILE_TARGETS} ${_FILE_LOCATION})
  ENDIF(EXISTS ${ACCUM_FILE_TARGETS})
 ENDIF(ACCUM_FILE_TARGETS)
ENDMACRO(TARGET_LOCATIONS_ACCUM TARGET_NAME)

MACRO(TARGET_LOCATIONS_GET_LIST _VAR)
 IF(ACCUM_FILE_TARGETS)
  IF(EXISTS ${ACCUM_FILE_TARGETS})
      FILE(READ ${ACCUM_FILE_TARGETS} ${_VAR})    
  ENDIF(EXISTS ${ACCUM_FILE_TARGETS})
 ENDIF(ACCUM_FILE_TARGETS)
ENDMACRO(TARGET_LOCATIONS_GET_LIST _VAR)

#SET(MACRO_MESSAGE_DEBUG TRUE)
MACRO(MACRO_MESSAGE MYTEXT)
    IF(MACRO_MESSAGE_DEBUG)
        MESSAGE("in file -->${CMAKE_CURRENT_LIST_FILE}<-- line -->${CMAKE_CURRENT_LIST_LINE}<-- message  ${MYTEXT}")
    ELSE(MACRO_MESSAGE_DEBUG)
        DEBUG_MESSAGE( "in file -->${CMAKE_CURRENT_LIST_FILE}<-- line -->${CMAKE_CURRENT_LIST_LINE}<-- message  ${MYTEXT}")
    ENDIF(MACRO_MESSAGE_DEBUG)
ENDMACRO(MACRO_MESSAGE MYTEXT)

MACRO(LINK_WITH_VARIABLES TRGTNAME)
    FOREACH(varname ${ARGN})
      IF (WIN32)
        IF(${varname}_RELEASE)
           IF(${varname}_DEBUG)
               TARGET_LINK_LIBRARIES(${TRGTNAME} optimized "${${varname}_RELEASE}" debug "${${varname}_DEBUG}")
           ELSE(${varname}_DEBUG)
               TARGET_LINK_LIBRARIES(${TRGTNAME} optimized "${${varname}_RELEASE}" debug "${${varname}_RELEASE}" )
           ENDIF(${varname}_DEBUG)
        ELSE(${varname}_RELEASE)
           IF(${varname}_DEBUG)
               TARGET_LINK_LIBRARIES(${TRGTNAME} optimized "${${varname}}" debug "${${varname}_DEBUG}")
           ELSE(${varname}_DEBUG)
               TARGET_LINK_LIBRARIES(${TRGTNAME} optimized "${${varname}}" debug "${${varname}}" )
           ENDIF(${varname}_DEBUG)
        ENDIF(${varname}_RELEASE)
      ELSE (WIN32)
        IF(${varname}_RELEASE)
           TARGET_LINK_LIBRARIES(${TRGTNAME} "${${varname}_RELEASE}")
        ELSE(${varname}_RELEASE)
           TARGET_LINK_LIBRARIES(${TRGTNAME} "${${varname}}")
        ENDIF(${varname}_RELEASE)
      ENDIF (WIN32)
    ENDFOREACH(varname)
ENDMACRO(LINK_WITH_VARIABLES TRGTNAME)

# Try to ascertain the version...
MACRO(FIND_OSG_VERSION)
    IF(OSG_INCLUDE_DIR)

        SET(_osg_Version_file "${OSG_INCLUDE_DIR}/osg/Version")
        IF("${OSG_INCLUDE_DIR}" MATCHES "\\.framework$" AND NOT EXISTS "${_osg_Version_file}")
            SET(_osg_Version_file "${OSG_INCLUDE_DIR}/Headers/Version")
        ENDIF()

        IF(EXISTS "${_osg_Version_file}")
          FILE(READ "${_osg_Version_file}" _osg_Version_contents)
        ELSE()
          SET(_osg_Version_contents "unknown")
        ENDIF()

        STRING(REGEX MATCH ".*#define OSG_VERSION_MAJOR[ \t]+[0-9]+.*"
            _osg_old_defines "${_osg_Version_contents}")
        STRING(REGEX MATCH ".*#define OPENSCENEGRAPH_MAJOR_VERSION[ \t]+[0-9]+.*"
            _osg_new_defines "${_osg_Version_contents}")
        IF(_osg_old_defines)
            STRING(REGEX REPLACE ".*#define OSG_VERSION_MAJOR[ \t]+([0-9]+).*"
                "\\1" _osg_VERSION_MAJOR ${_osg_Version_contents})
            STRING(REGEX REPLACE ".*#define OSG_VERSION_MINOR[ \t]+([0-9]+).*"
                "\\1" _osg_VERSION_MINOR ${_osg_Version_contents})
            STRING(REGEX REPLACE ".*#define OSG_VERSION_PATCH[ \t]+([0-9]+).*"
                "\\1" _osg_VERSION_PATCH ${_osg_Version_contents})
        ELSEIF(_osg_new_defines)
            STRING(REGEX REPLACE ".*#define OPENSCENEGRAPH_MAJOR_VERSION[ \t]+([0-9]+).*"
                "\\1" _osg_VERSION_MAJOR ${_osg_Version_contents})
            STRING(REGEX REPLACE ".*#define OPENSCENEGRAPH_MINOR_VERSION[ \t]+([0-9]+).*"
                "\\1" _osg_VERSION_MINOR ${_osg_Version_contents})
            STRING(REGEX REPLACE ".*#define OPENSCENEGRAPH_PATCH_VERSION[ \t]+([0-9]+).*"
                "\\1" _osg_VERSION_PATCH ${_osg_Version_contents})
        ELSE()
            MESSAGE("[ FindOpenSceneGraph.cmake:${CMAKE_CURRENT_LIST_LINE} ] "
                "Failed to parse version number, please report this as a bug")
        ENDIF()

        SET(OSG_VERSION_MAJOR ${_osg_VERSION_MAJOR})
        SET(OSG_VERSION_MINOR ${_osg_VERSION_MINOR})
        SET(OSG_VERSION_PATCH ${_osg_VERSION_PATCH})

        SET(OPENSCENEGRAPH_VERSION "${_osg_VERSION_MAJOR}.${_osg_VERSION_MINOR}.${_osg_VERSION_PATCH}"
                                    CACHE INTERNAL "The version of OSG which was detected")                
    ENDIF()
ENDMACRO(FIND_OSG_VERSION)

INCLUDE(ListHandle)


  MACRO(FILTER_OUT FILTERS INPUTS OUTPUT)
       # Mimicks Gnu Make's $(filter-out) which removes elements 
       # from a list that match the pattern.
       # Arguments:
       #  FILTERS - list of patterns that need to be removed
       #  INPUTS  - list of inputs that will be worked on
       #  OUTPUT  - the filtered list to be returned
       # 
       # Example: 
       #  SET(MYLIST this that and the other)
       #  SET(FILTS this that)
       #
       #  FILTER_OUT("${FILTS}" "${MYLIST}" OUT)
       #  MESSAGE("OUTPUT = ${OUT}")
       #
       # The output - 
       #   OUTPUT = and;the;other
       #
       SET(FOUT "")
       FOREACH(INP ${INPUTS})
           SET(FILTERED 0)
           FOREACH(FILT ${FILTERS})
               IF(${FILTERED} EQUAL 0)
                   IF("${FILT}" STREQUAL "${INP}")
                       SET(FILTERED 1)
                   ENDIF("${FILT}" STREQUAL "${INP}")
               ENDIF(${FILTERED} EQUAL 0)
           ENDFOREACH(FILT ${FILTERS})
           IF(${FILTERED} EQUAL 0)
               SET(FOUT ${FOUT} ${INP})
           ENDIF(${FILTERED} EQUAL 0)
       ENDFOREACH(INP ${INPUTS})
       SET(${OUTPUT} ${FOUT})
   ENDMACRO(FILTER_OUT FILTERS INPUTS OUTPUT)


   MACRO(GET_HEADERS_EXTENSIONLESS DIR GLOB_PATTERN OUTPUT)
            FILE(GLOB TMP "${DIR}/${GLOB_PATTERN}" )
      #FOREACH(F ${TMP})
            #    DEBUG_MESSAGE( "header-->${F}<--")
      #ENDFOREACH(F ${TMP})
            FILTER_OUT("${DIR}/CVS" "${TMP}" TMP)
            FILTER_OUT("${DIR}/cvs" "${TMP}" ${OUTPUT})
            FILTER_OUT("${DIR}/.svn" "${TMP}" ${OUTPUT})
   ENDMACRO(GET_HEADERS_EXTENSIONLESS DIR GLOB_PATTERN OUTPUT)
   
MACRO(ADD_DIRS_TO_ENV_VAR _VARNAME )
 FOREACH(_ADD_PATH ${ARGN}) 
    FILE(TO_NATIVE_PATH ${_ADD_PATH} _ADD_NATIVE)
    #SET(_CURR_ENV_PATH $ENV{PATH})
    #LIST(SET _CURR_ENV_PATH ${_ADD_PATH})
    #SET(ENV{PATH} ${_CURR_ENV_PATH})${_FILE}
    IF(WIN32)
        SET(ENV{${_VARNAME}} "$ENV{${_VARNAME}};${_ADD_NATIVE}")
    ELSE(WIN32)
        SET(ENV{${_VARNAME}} "$ENV{${_VARNAME}}:${_ADD_NATIVE}")
    ENDIF(WIN32)
    #MESSAGE(" env ${_VARNAME} --->$ENV{${_VARNAME}}<---")
 ENDFOREACH(_ADD_PATH)
ENDMACRO(ADD_DIRS_TO_ENV_VAR _VARNAME )

#---------------------------------------------------
# MACRO CORRECT_PATH VAR PATH 
# corrects slashes in PATH to be cmake conformous ( / ) 
# and puts result in VAR 
#---------------------------------------------------

MACRO(CORRECT_PATH VAR PATH)
    SET(${VAR} ${PATH})
IF(WIN32)    
    STRING(REGEX REPLACE "/" "\\\\" ${VAR} "${PATH}")
ENDIF(WIN32)    
ENDMACRO(CORRECT_PATH)

MACRO(TARGET_LOCATIONS_SET_FILE FILE)
 SET(ACCUM_FILE_TARGETS ${FILE})
 FILE(WRITE ${ACCUM_FILE_TARGETS} "")
ENDMACRO(TARGET_LOCATIONS_SET_FILE FILE)

MACRO(TARGET_LOCATIONS_ACCUM TARGET_NAME)
 IF(ACCUM_FILE_TARGETS)
  IF(EXISTS ${ACCUM_FILE_TARGETS})
    GET_TARGET_PROPERTY(_FILE_LOCATION ${TARGET_NAME} LOCATION)
    FILE(APPEND ${ACCUM_FILE_TARGETS} "${_FILE_LOCATION};")
    #SET(_TARGETS_LIST ${_TARGETS_LIST} "${_FILE_LOCATION}" CACHE INTERNAL "lista dll")
    #MESSAGE("adding target -->${TARGET_NAME}<-- file -->${_FILE_LOCATION}<-- to list -->${_TARGETS_LIST}<--")
    #SET(ACCUM_FILE_TARGETS ${ACCUM_FILE_TARGETS} ${_FILE_LOCATION})
  ENDIF(EXISTS ${ACCUM_FILE_TARGETS})
 ENDIF(ACCUM_FILE_TARGETS)
ENDMACRO(TARGET_LOCATIONS_ACCUM TARGET_NAME)

MACRO(TARGET_LOCATIONS_GET_LIST _VAR)
 IF(ACCUM_FILE_TARGETS)
  IF(EXISTS ${ACCUM_FILE_TARGETS})
      FILE(READ ${ACCUM_FILE_TARGETS} ${_VAR})    
  ENDIF(EXISTS ${ACCUM_FILE_TARGETS})
 ENDIF(ACCUM_FILE_TARGETS)
ENDMACRO(TARGET_LOCATIONS_GET_LIST _VAR)


MACRO(FIND_DEPENDENCY DEPNAME INCLUDEFILE LIBRARY SEARCHPATHLIST)

DEBUG_MESSAGE( "searching ${DEPNAME} -->${INCLUDEFILE}<-->${LIBRARY}<-->${SEARCHPATHLIST}<--")

SET(MY_PATH_INCLUDE )
SET(MY_PATH_LIB )
SET(MY_PATH_BIN )

FOREACH( MYPATH ${SEARCHPATHLIST} )
    SET(MY_PATH_INCLUDE ${MY_PATH_INCLUDE} ${MYPATH}/include)
    SET(MY_PATH_LIB ${MY_PATH_LIB} ${MYPATH}/lib)
    SET(MY_PATH_BIN ${MY_PATH_BIN} ${MYPATH}/bin)
ENDFOREACH( MYPATH ${SEARCHPATHLIST} )

SET(MYLIBRARY "${LIBRARY}")
SEPARATE_ARGUMENTS(MYLIBRARY)

#MESSAGE( " include paths: -->${MY_PATH_INCLUDE}<--")

#MESSAGE( " ${DEPNAME}_INCLUDE_DIR --> ${${DEPNAME}_INCLUDE_DIR}<--")
    
FIND_PATH("${DEPNAME}_INCLUDE_DIR" ${INCLUDEFILE}
  ${MY_PATH_INCLUDE}
)
MARK_AS_ADVANCED("${DEPNAME}_INCLUDE_DIR")
#MESSAGE( " ${DEPNAME}_INCLUDE_DIR --> ${${DEPNAME}_INCLUDE_DIR}<--")

FIND_LIBRARY("${DEPNAME}_LIBRARY" 
    NAMES ${MYLIBRARY}
  PATHS ${MY_PATH_LIB}
)
IF(${DEPNAME}_LIBRARY)
    GET_FILENAME_COMPONENT(MYLIBNAME ${${DEPNAME}_LIBRARY} NAME_WE)
    GET_FILENAME_COMPONENT(MYBINPATH ${${DEPNAME}_LIBRARY} PATH)
    GET_FILENAME_COMPONENT(MYBINPATH ${MYBINPATH} PATH)
    SET(MYBINPATH "${MYBINPATH}/bin")
    IF(EXISTS ${MYBINPATH})
        SET(MYFOUND 0)
        FOREACH(MYPATH ${MY_ACCUM_BINARY_DEP})
            IF(MYPATH MATCHES ${MYBINPATH})
                SET(MYFOUND 1)
                #MESSAGE("found -->${MYPATH}<-->${MYBINPATH}<--")
            ENDIF(MYPATH MATCHES ${MYBINPATH})
        ENDFOREACH(MYPATH )
        IF(MYFOUND EQUAL 0)
            SET(MY_ACCUM_BINARY_DEP ${MY_ACCUM_BINARY_DEP} ${MYBINPATH})
        ENDIF(MYFOUND EQUAL 0)
    ENDIF(EXISTS ${MYBINPATH})
    #MESSAGE("${DEPNAME}_BINDEP searching -->${MYLIBNAME}${CMAKE_SHARED_MODULE_SUFFIX}<--in-->${MY_PATH_BIN}<--")
#    FIND_FILE("${DEPNAME}_BINDEP" 
#        ${MYLIBNAME}${CMAKE_SHARED_MODULE_SUFFIX}
#      PATHS ${MY_PATH_BIN}
#    )
#    FIND_LIBRARY("${DEPNAME}_BINDEP" 
#        NAMES ${MYLIBRARY}
#      PATHS ${MY_PATH_BIN}
#    )
ENDIF(${DEPNAME}_LIBRARY)
MARK_AS_ADVANCED("${DEPNAME}_LIBRARY")
#MESSAGE( " ${DEPNAME}_LIBRARY --> ${${DEPNAME}_LIBRARY}<--")
IF(${DEPNAME}_INCLUDE_DIR)
  IF(${DEPNAME}_LIBRARY)
    SET( ${DEPNAME}_FOUND "YES" )
    SET( ${DEPNAME}_LIBRARIES ${${DEPNAME}_LIBRARY} )
  ENDIF(${DEPNAME}_LIBRARY)
ENDIF(${DEPNAME}_INCLUDE_DIR)
ENDMACRO(FIND_DEPENDENCY DEPNAME INCLUDEFILE LIBRARY SEARCHPATHLIST)
SET(MYLIBRARY "${LIBRARY}")
SEPARATE_ARGUMENTS(MYLIBRARY)
#SET(MACRO_MESSAGE_DEBUG TRUE)
MACRO(MACRO_MESSAGE MYTEXT)
    IF(MACRO_MESSAGE_DEBUG)
        MESSAGE("in file -->${CMAKE_CURRENT_LIST_FILE}<-- line -->${CMAKE_CURRENT_LIST_LINE}<-- message  ${MYTEXT}")
    ELSE(MACRO_MESSAGE_DEBUG)
        DEBUG_MESSAGE( "in file -->${CMAKE_CURRENT_LIST_FILE}<-- line -->${CMAKE_CURRENT_LIST_LINE}<-- message  ${MYTEXT}")
    ENDIF(MACRO_MESSAGE_DEBUG)
ENDMACRO(MACRO_MESSAGE MYTEXT)
#############################################################

MACRO(MESSAGE_SETUP_LIBRARY _libName)
	SET(ThisLibName ${_libName})
	MESSAGE("**************************Setting Up ${ThisLibName}************************")
	SET(${_libName}_LIB_SRC "") #定义库全局变量
ENDMACRO(MESSAGE_SETUP_LIBRARY _libName)

MACRO(BEGIN_LIB libName)
	BEGIN_TARGET(${libName})
ENDMACRO(BEGIN_LIB libName)

MACRO(END_LIB libName)
	END_TARGET(${libName})
ENDMACRO(END_LIB libName)

#############################################################

MACRO(FIND_FILES_IN_SUB_DIRECTORY sub_directory)
   MESSAGE("------Find File In Sub Directory ${sub_directory}") 
	
   FILE(GLOB ${sub_directory}_src "${sub_directory}/*.h" "${sub_directory}/*.cpp" "${sub_directory}/*.cc")
   
   FILE(GLOB ${sub_directory}_uis 	"${sub_directory}/*.ui")
   
   FILE(GLOB ${sub_directory}_rcs	"${sub_directory}/*.qrc")

   set(${sub_directory}_all_files ${${sub_directory}_src} ${${sub_directory}_uis} ${${sub_directory}_rcs})

   MESSAGE("---FIND_FILES_IN_SUB_DRECTORY ${sub_directory}_src===" ${${sub_directory}_src})	
   #MESSAGE("---FIND_FILES_IN_SUB_DRECTORY ${sub_directory}_uis===" ${${sub_directory}_uis})	
   #MESSAGE("---FIND_FILES_IN_SUB_DRECTORY ${sub_directory}_rcs===" ${${sub_directory}_rcs})
   #MESSAGE("---FIND_FILES_IN_SUB_DRECTORY ${sub_directory}_all_files===" ${${sub_directory}_all_files})
ENDMACRO(FIND_FILES_IN_SUB_DIRECTORY sub_directory)

#############################################################

MACRO(SETUP_VIRE_BSPLUGIN_VERSION_LIBRARY libName)
	SET(_LIB_NAME 		${libName})

	#===================================================
	SET(CMAKE_INCLUDE_CURRENT_DIR ON)
	SET(CMAKE_AUTOMOC ON)
	#===================================================
	INCLUDE_DIRECTORIES(
		${VIRE_INCLUDE_DIR}
		${VIRE_BSPLUGIN_INCLUDE_DIR}/${LIB_NAME}
	)
	#===================================================
	SET(CMAKE_INCLUDE_CURRENT_DIR ON)
	SET(CMAKE_AUTOMOC ON)
	#===================================================
	#设置UI资源
	FILE(GLOB LIB_QT_UIS "*.ui")

	# 设置图片资源
	SET(GLOB LIB_QT_RCS "*.qrc")
	
	IF(Qt5Widgets_FOUND)
		QT5_ADD_RESOURCES( LIB_RC_SRCS ${LIB_QT_RCS} )
		QT5_WRAP_UI( LIB_UI_HDRS ${LIB_QT_UIS} )
		IF(Qt5Widgets_VERSION VERSION_LESS 5.2.0)
		   QT5_WRAP_CPP( LIB_UI_SRCS ${LIB_UI_HDRS} OPTIONS "-f" )
		ELSE()
			QT5_WRAP_CPP( LIB_UI_SRCS ${LIB_UI_HDRS} )
		ENDIF()
	ELSE(Qt5Widgets_FOUND)
	   INCLUDE( ${QT_USE_FILE} )
		QT4_ADD_RESOURCES( LIB_RC_SRCS ${LIB_QT_RCS} )
		QT4_WRAP_UI( LIB_UI_HDRS ${LIB_QT_UIS} )
		QT4_WRAP_CPP( LIB_UI_SRCS ${LIB_UI_HDRS} OPTIONS "-f" )
	ENDIF(Qt5Widgets_FOUND)

	# 设置h代码
	FILE(GLOB ${LIB_NAME}_LIB_HEADERS "*.h" "${VIRE_BSPLUGIN_INCLUDE_DIR}/${LIB_NAME}/*.h")
	
	# 设置cpp代码
	FILE(GLOB ${LIB_NAME}_LIB_SRCS "*.cpp")
	
	SET(_LIB_HEADER 
		${LIB_UI_HDRS}
		${LIB_QT_UIS}
		${${LIB_NAME}_LIB_HEADERS}
		${MAKE_BSPLUGIN_FILE_HEADER}
	)
	MESSAGE("---${_LIB_NAME} Headers:" ${_LIB_HEADER})	

	SET(_LIB_CPP 		
		${VERSIONED_LIB_RC} 
		${MAKE_BSPLUGIN_FILE_SRC}
		${${LIB_NAME}_LIB_SRCS}
		${${LIB_NAME}_LIB_SRC}
		${LIB_RC_SRCS}
		${LIB_QT_RCS}
	)
	MESSAGE("---${_LIB_NAME} cpps:" ${_LIB_CPP})	
	
	ADD_LIBRARY(${_LIB_NAME} SHARED
		${_LIB_HEADER}
		${_LIB_CPP})
		
	# Generated Files
	SOURCE_GROUP(
		"Generated Files"
		FILES 
			${LIB_RC_SRCS}
			${LIB_UI_HDRS}
	)
	
	# Form Files
	SOURCE_GROUP(
		"Form Files"
		FILES  
		${LIB_QT_UIS}
	)

	#Resources Files
	SOURCE_GROUP(
		"Resource Files"
		FILES  
		${LIB_QT_RCS}
		${VERSIONED_LIB_RC} 
	)
	
ENDMACRO(SETUP_VIRE_BSPLUGIN_VERSION_LIBRARY libName)
#############################################################
MACRO(ADD_LIB_SUBDIRECTORY libName sub_directories)
	
	FOREACH(subdir ${sub_directories})
	   FILE(GLOB _sub_src 	"${subdir}/*.h" "${subdir}/*.cpp")
	   FILE(GLOB _sub_uis 	"${subdir}/*.ui")
	   FILE(GLOB _sub_rcs	"${subdir}/*.qrc")
	  
	   IF(Qt5Widgets_FOUND)
			QT5_ADD_RESOURCES(_sub_LIB_RC_SRCS ${_sub_rcs} )
			QT5_WRAP_UI( _sub_LIB_UI_HDRS ${${libName}_temp_uis} )
		IF(Qt5Widgets_VERSION VERSION_LESS 5.2.0)
		   QT5_WRAP_CPP( _sub_LIB_UI_SRCS ${_sub_LIB_UI_HDRS} OPTIONS "-f" )
		ELSE()
			QT5_WRAP_CPP( _sub_LIB_UI_SRCS ${_sub_LIB_UI_HDRS} )
		ENDIF()
		ELSE(Qt5Widgets_FOUND)
		    INCLUDE( ${QT_USE_FILE} )
			QT4_ADD_RESOURCES( _sub_LIB_RC_SRCS ${_sub_rcs} )
			QT4_WRAP_UI( _sub_LIB_UI_HDRS ${_sub_uis} )
			QT4_WRAP_CPP( _sub_LIB_UI_SRCS ${_sub_LIB_UI_HDRS} OPTIONS "-f" )
	ENDIF(Qt5Widgets_FOUND)

	# Generated Files
	SOURCE_GROUP(
		"_${subdir}_"
		FILES 
			${_sub_src}
			${_sub_uis}
			${_sub_rcs}
	)
	

	SET(${libName}_LIB_SRC ${${LibName}_LIB_SRC} ${_sub_src})

	
	SET(${libName}_LIB_UI_SRC ${${LibName}_LIB_UI_SRC} ${_sub_LIB_UI_SRCS})

	
	SET(${libName}_LIB_RC_SRC ${${LibName}_LIB_RC_SRC} ${_sub_LIB_RC_SRCS})
	
	if(${ProjectVal_PREFIX_CONFIG}_DEBUG_MSG)
		MESSAGE("xxxxx==============${${libName}_LIB_SRC}")
	endif()
	
   ENDFOREACH(subdir ${sub_directories})
ENDMACRO(ADD_LIB_SUBDIRECTORY libName sub_directories)

#############################################################
MACRO(VIRE_COPY_EXPORT_LIB_HEADER lib_name destDir export_define)
	
	SET(_DEST_INCLUDE_DIR "${destDir}/${lib_name}")
	
	DEBUG_MESSAGE( "MACRO VIRE_COPY_EXPORT_LIB_HEADER:->${lib_name}<->${_DEST_INCLUDE_DIR}")
	
	add_custom_command(TARGET  ${lib_name} POST_BUILD
	  COMMAND echo "create directory ${_DEST_INCLUDE_DIR}..."
	  COMMAND ${CMAKE_COMMAND} -E make_directory ${_DEST_INCLUDE_DIR}
	 )
 
	foreach(file ${${lib_name}_LIB_HEADERS})
		#DEBUG_MESSAGE( "file:->${file}")
		get_filename_component(_dir ${file} DIRECTORY)
		#DEBUG_MESSAGE( "get_filename_component DIRECTORY:->${_dir}")
		get_filename_component(_name ${file} NAME)
		#DEBUG_MESSAGE( "get_filename_component NAME:->${_name}")
		get_filename_component(_EXT ${file} EXT)
		#DEBUG_MESSAGE( "get_filename_component EXT:->${_EXT}")
		get_filename_component(_parent_dir ${_dir} DIRECTORY)
		#DEBUG_MESSAGE( "get_filename_component DIRECTORY:->${_parent_dir}")
		string(REPLACE "${_parent_dir}/" "" _sub_dir  ${_dir})


		#DEBUG_MESSAGE( "REPLACE:->${_sub_dir}")
		#string(FIND ${_dir} "${_parent_dir}/" findval)
		#string(LENGTH "${_parent_dir}/" lenth_of_parent_dir)
		#DEBUG_MESSAGE( "string FIND:->${findval}")

		#FILE(STRINGS ${file} _file_string )
		#DEBUG_MESSAGE( "_file_string:->${_file_string}")
		#string(FIND _file_string ${export_define} find2va)
		#DEBUG_MESSAGE( "find2va:->${find2va}")

		IF(${_sub_dir} STREQUAL ${lib_name})

		add_custom_command(TARGET  ${lib_name} POST_BUILD
		  COMMAND echo "Copy Header : ${file} To ${_DEST_INCLUDE_DIR}"
		  COMMAND ${CMAKE_COMMAND} -E copy ${file} ${_DEST_INCLUDE_DIR}
		)
		ELSE()

		SET(_SUB_DIR_PATH "${_DEST_INCLUDE_DIR}/${_sub_dir}")
		add_custom_command(TARGET  ${lib_name} POST_BUILD
		  COMMAND ${CMAKE_COMMAND} -E make_directory ${_SUB_DIR_PATH}
		)

		add_custom_command(TARGET  ${lib_name} POST_BUILD
		  COMMAND echo "Copy Header : ${file} To ${_SUB_DIR_PATH}"
		 COMMAND ${CMAKE_COMMAND} -E copy ${file} ${_SUB_DIR_PATH}
		)

		ENDIF()
		
	endforeach()
ENDMACRO(VIRE_COPY_EXPORT_LIB_HEADER lib_name destDir export_define)

#############################################################
MACRO(VIRE_SUB_DIR_SERACH_FILES_FOR_EXPORTED_LIB lib_name export_include_path)
	TARGET_SERACH_SUB_DIRS_FILES(${lib_name} EXPORT HEADER_DIR_PATH ${export_include_path} SUB_DIRS ${ARGN})
ENDMACRO(VIRE_SUB_DIR_SERACH_FILES_FOR_EXPORTED_LIB lib_name export_include_path)

MACRO(VIRE_SUB_DIR_SERACH_FILES_FOR_EXPORTED_LIB_EX lib_name export_include_path)
	TARGET_SERACH_SUB_DIRS_FILES(${lib_name} EXPORT HEADER_DIR_PATH ${export_include_path} SUB_DIRS ${ARGN})
ENDMACRO(VIRE_SUB_DIR_SERACH_FILES_FOR_EXPORTED_LIB_EX lib_name export_include_path)
#=================================================================================================
include(macro_link_with_variables)

macro(make_vrcore_include_variable _target _include_dir)
    string(TOUPPER ${_target} _Upper)
    set(VRCORE_${_Upper}_INCLUDE_DIR ${_include_dir})
    message(STATUS "==VRCORE_${_Upper}_INCLUDE_DIR==${VRCORE_${_Upper}_INCLUDE_DIR}==")
endmacro()

macro(use_vrcores_modules _target)
    if (NOT TARGET ${_target})
        message(FATAL_ERROR "The first argument to use_vrcores_modules must be an existing target.")
    endif()

    SET(options INTERNAL)
    SET(oneValueArgs )
    SET(multiValueArgs)
    cmake_parse_arguments(${_target}
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    SET(_link_libs ${${_target}_UNPARSED_ARGUMENTS})
    if ("${_link_libs}" STREQUAL "")
        message(FATAL_ERROR "use_vrcores_modules requires at least one vrcore module to use.")
    endif()
    message(STATUS "_link_libs==${_link_libs}==")
    message(STATUS "${_target}_INTERNAL==${${_target}_INTERNAL}==")
    set(_outer_libs_)
    foreach(_module ${_link_libs})
        string(TOUPPER ${_module} _Upper)
        if(${${_target}_INTERNAL})
            target_link_libraries(${_target} ${_module})
            message(STATUS "VRCORE_${_Upper}_INCLUDE_DIR->${VRCORE_${_Upper}_INCLUDE_DIR}")
            set_property(TARGET ${_target} 
                APPEND PROPERTY INCLUDE_DIRECTORIES ${VRCORE_${_Upper}_INCLUDE_DIR})
        else()
            set(_outer_libs_ ${_outer_libs_} VRCORE_${_Upper}_LIBRARY)
        endif()
    endforeach()
    if(NOT ${_target}_INTERNAL)
        ADD_3RD_DEPENDENCIES(${_target} _outer_libs_)
    endif()
endmacro()
#=================================================================================================
MACRO(VIRE_ADD_LIBRARY _libName)

SET(${_libName}_LIB_HEADER 
    ${${_libName}_UI_HDRS}
    ${${_libName}_QT_UIS}
    ${${_libName}_HEADERS}
)

SET(${_libName}_LIB_CPP        
    ${VERSIONED_LIB_RC} 
    ${${_libName}_SRCS}
    ${${_libName}_RC_SRCS}
    ${${_libName}_QT_RCS}
)

ADD_LIBRARY(${_libName} SHARED
    ${${_libName}_LIB_HEADER}
    ${${_libName}_LIB_CPP}
)
ENDMACRO()
#=================================================================================================
include(macro_debug_message)
include(macro_make_export_file)

MACRO(VIRE_MAKE_BSPLUGIN_FILES LibName)
  SET(LIB_NAME ${LibName})

  #HEADER_PATH 头文件的目录
  SET(options )
  SET(oneValueArgs HEADER_DIR_PATH)
  SET(multiValueArgs)
  cmake_parse_arguments(_Make_File
      "${options}" 
      "${oneValueArgs}" 
      "${multiValueArgs}" 
      ${ARGN})

  SET(_DIR_OF_Template ${THIS_MODULE_TEMPLATES_PATH})

  SET(_header_path ${CMAKE_CURRENT_SOURCE_DIR})
  IF(_Make_File_HEADER_DIR_PATH)
    SET(_header_path "${_Make_File_HEADER_DIR_PATH}")
  ENDIF()

  MAKE_EXPORT_FILE(${LibName} ${_header_path})

  SET(${LibName}_HEADER "${_header_path}/${LibName}.h")
  IF(NOT EXISTS ${${LibName}_HEADER})
    CONFIGURE_FILE("${_DIR_OF_Template}/BSPluginTemplate/plugin_file.h.in" "${${LibName}_HEADER}")
  ENDIF()
  
  SET(${LibName}_SRC "${CMAKE_CURRENT_SOURCE_DIR}/${LibName}.cpp")
  IF(NOT EXISTS ${${LibName}_SRC})
    CONFIGURE_FILE("${_DIR_OF_Template}/BSPluginTemplate/plugin_file.cpp.in" "${${LibName}_SRC}")
  ENDIF()
  
  SET(MAKE_BSPLUGIN_FILE_HEADER ${${LibName}_EXPORT} ${${LibName}_HEADER})
  DEBUG_MESSAGE("===MAKE_BSPLUGIN_FILE_HEADER===(File###${MAKE_BSPLUGIN_FILE_HEADER})")
  
  SET(MAKE_BSPLUGIN_FILE_SRC ${${LibName}_SRC})
  DEBUG_MESSAGE("===MAKE_BSPLUGIN_FILE_SRC===(File###${MAKE_BSPLUGIN_FILE_SRC})")
ENDMACRO()

MACRO(VIRE_MAKE_BSPLUGIN_FILES_INNER LibName)
  VIRE_MAKE_BSPLUGIN_FILES(${LibName} ${ARGN})
ENDMACRO()

MACRO(VIRE_MAKE_BSPLUGIN_FILES_EXPORT LibName _hederdir)
  VIRE_MAKE_BSPLUGIN_FILES(${LibName} 
    HEADER_DIR_PATH 
    ${_hederdir}
  )
ENDMACRO(VIRE_MAKE_BSPLUGIN_FILES_EXPORT LibName)
#=================================================================================================
# Where is this and what do we need it for?
#############################################################
include(macro_make_class_file)
#############################################################

#产生QObject子类文件
MACRO(VIRE_MAKE_CLASS_WITH_QOBJECT _lib_name)
    MAKE_CLASS_WITH_QOBJECT(${_lib_name} ${ARGN})
ENDMACRO()

#产生带导出标志的QObject子类文件
MACRO(VIRE_MAKE_EXPORT_CLASS_WITH_QOBJECT _lib_name _export_header_dir)
    MAKE_EXPORT_CLASS_WITH_QOBJECT(
        ${_lib_name} 
        ${_export_header_dir}
        ${ARGN}
    )
ENDMACRO()

#========================================================
#产生有UI文件QWidget子类文件
MACRO(VIRE_MAKE_CLASS_WITH_UI_WIDGET _lib_name)
    MAKE_CLASS_WITH_UI_WIDGET(${_lib_name} ${ARGN})
ENDMACRO()

#产生没有UI文件QWidget子类文件
MACRO(VIRE_MAKE_CLASS_WIDGET _lib_name)
    MAKE_CLASS_WIDGET(${_lib_name} ${ARGN})
ENDMACRO()

#产生有UI文件QWidget子类导出文件
MACRO(VIRE_MAKE_EXPORT_CLASS_WITH_UI_WIDGET _lib_name _export_header_dir)
    MAKE_EXPORT_CLASS_WITH_UI_WIDGET(
        ${_lib_name} 
        ${_export_header_dir}
        ${ARGN}
    )
ENDMACRO()

#产生没有UI文件QWidget子类导出文件
MACRO(VIRE_MAKE_EXPORT_CLASS_WIDGET _lib_name _export_header_dir)
    MAKE_EXPORT_CLASS_WIDGET(
        ${_lib_name} 
        ${_export_header_dir}
        ${ARGN}
    )
ENDMACRO()
#========================================================
#产生有UI文件QDialog子类文件
MACRO(VIRE_MAKE_CLASS_WITH_UI_DIALOG _lib_name)
    MAKE_CLASS_WITH_UI_DIALOG(${_lib_name} ${ARGN})
ENDMACRO()

#产生有QDialog子类文件
MACRO(VIRE_MAKE_CLASS_DIALOG _lib_name)
    MAKE_CLASS_DIALOG(${_lib_name} ${ARGN})
ENDMACRO()

#产生有UI文件QDialog子类导出文件
MACRO(VIRE_MAKE_EXPORT_CLASS_WITH_UI_DIALOG _lib_name _export_header_dir)
    MAKE_EXPORT_CLASS_WITH_UI_DIALOG(
        ${_lib_name} 
        ${_export_header_dir}
        ${ARGN}
    )
ENDMACRO()

#产生有UI文件QDialog子类导出文件
MACRO(VIRE_MAKE_EXPORT_CLASS_DIALOG _lib_name _export_header_dir)
    MAKE_EXPORT_CLASS_DIALOG(
        ${_lib_name} 
        ${_export_header_dir}
        ${ARGN}
    )
ENDMACRO()
#========================================================
#产生普通类文件
MACRO(VIRE_MAKE_CLASS _lib_name)
    MAKE_CLASS(${_lib_name} ${ARGN})
ENDMACRO()

MACRO(VIRE_MAKE_EXPORT_CLASS _lib_name _export_header_dir)
    MAKE_EXPORT_CLASS(
        ${_lib_name}
        ${_export_header_dir}
        ${ARGN}
    )
ENDMACRO()
#############################################################

#以下的宏是为匹配以前工程用的宏使用
MACRO(VIRE_MAKE_CLASS_FILE_WITH_QOBJECT_EX _lib_name)
    VIRE_MAKE_CLASS_WITH_QOBJECT(${_lib_name} ${ARGN})
ENDMACRO()

MACRO(VIRE_MAKE_CLASS_FILE_WITH_UI_WIDGET_EX _lib_name)
    VIRE_MAKE_CLASS_WITH_UI_WIDGET(${_lib_name} ${ARGN})
ENDMACRO()

MACRO(VIRE_MAKE_CLASS_FILE_WITH_UI_DIALOG_EX _lib_name)
    VIRE_MAKE_CLASS_WITH_UI_DIALOG(${_lib_name} ${ARGN})
ENDMACRO()

MACRO(VIRE_MAKE_CLASS_FILE_EX _lib_name)
    VIRE_MAKE_CLASS(${_lib_name} ${ARGN})
ENDMACRO(VIRE_MAKE_CLASS_FILE_EX _lib_name)
#===================================================================================
MACRO(VIRE_SUB_DIR_SEARCH_FILES_FOR_LIB_INNER lib_name)
    
    SET(sub_dirs ${ARGN})
    
    DEBUG_MESSAGE( "MACRO SUB_DIR_SERACH_FILES_FOR_LIB_INNER:->${lib_name}<->${sub_dirs}")
        
    SET(ALL_SUB_DIR_HDR )
    SET(ALL_SUB_DIR_SRCS )
    SET(ALL_SUB_DIR_UIS )
    SET(ALL_SUB_DIR_RCS )

    FOREACH(_dir_ ${sub_dirs} ) 
        #FIND Files In SubDir
        FILE(GLOB TEMP_SOURCES_HDR "${_dir_}/*.h" "${_dir_}/*.inl" "${_dir_}/*.hpp")
        FILE(GLOB TEMP_SOURCES_SRC "${_dir_}/*.cpp" "${_dir_}/*.cc")
        FILE(GLOB TEMP_UIS "${_dir_}/*.ui")
        FILE(GLOB TEMP_RCS "${_dir_}/*.qrc")
        
        #Set The Param Val
        SET(ALL_SUB_DIR_HDR ${ALL_SUB_DIR_HDR} ${TEMP_SOURCES_HDR})
        SET(ALL_SUB_DIR_SRCS ${ALL_SUB_DIR_SRCS} ${TEMP_SOURCES_HDR} ${TEMP_SOURCES_SRC}) 
        SET(ALL_SUB_DIR_UIS ${ALL_SUB_DIR_UIS} ${TEMP_UIS}) 
        SET(ALL_SUB_DIR_RCS ${ALL_SUB_DIR_RCS} ${TEMP_RCS}) 
        
        #File Groups
        SOURCE_GROUP( "_${_dir_}" FILES 
        ${TEMP_SOURCES_HDR} 
        ${TEMP_SOURCES_SRC}
        ${TEMP_UIS}
        ${TEMP_RCS}
    )
    ENDFOREACH( _dir_ ${sub_dirs} )
    
    DEBUG_MESSAGE( "MACRO:ALL_SUB_DIR_SRCS:${ALL_SUB_DIR_SRCS}")
    DEBUG_MESSAGE( "MACRO:ALL_SUB_DIR_UIS:${ALL_SUB_DIR_UIS}")
    DEBUG_MESSAGE( "MACRO:ALL_SUB_DIR_RCS:${ALL_SUB_DIR_RCS}")
    
    SET(${lib_name}_LIB_HEADERS ${${lib_name}_LIB_HEADERS} ${ALL_SUB_DIR_HDR})
    SET(${lib_name}_LIB_SRCS ${${lib_name}_LIB_SRCS} ${ALL_SUB_DIR_SRCS})
    SET(LIB_QT_UIS ${LIB_QT_UIS} ${ALL_SUB_DIR_UIS})
    SET(LIB_QT_RCS ${LIB_QT_RCS} ${ALL_SUB_DIR_RCS})
ENDMACRO(VIRE_SUB_DIR_SEARCH_FILES_FOR_LIB_INNER lib_name)

#====================================================================================================

MACRO(VIRE_SUB_DIR_SEARCH_FILES_FOR_LIB_INNER lib_name)
    
    SET(sub_dirs ${ARGN})
    
    DEBUG_MESSAGE( "MACRO SUB_DIR_SERACH_FILES_FOR_LIB_INNER:->${lib_name}<->${sub_dirs}")
        
    SET(ALL_SUB_DIR_HDR )
    SET(ALL_SUB_DIR_SRCS )
    SET(ALL_SUB_DIR_UIS )
    SET(ALL_SUB_DIR_RCS )

    FOREACH(_dir_ ${sub_dirs} ) 
        #FIND Files In SubDir
        FILE(GLOB TEMP_SOURCES_HDR "${_dir_}/*.h" "${_dir_}/*.inl" "${_dir_}/*.hpp")
        FILE(GLOB TEMP_SOURCES_SRC "${_dir_}/*.cpp" "${_dir_}/*.cc")
        FILE(GLOB TEMP_UIS "${_dir_}/*.ui")
        FILE(GLOB TEMP_RCS "${_dir_}/*.qrc")
        
        #Set The Param Val
        SET(ALL_SUB_DIR_HDR ${ALL_SUB_DIR_HDR} ${TEMP_SOURCES_HDR})
        SET(ALL_SUB_DIR_SRCS ${ALL_SUB_DIR_SRCS} ${TEMP_SOURCES_HDR} ${TEMP_SOURCES_SRC}) 
        SET(ALL_SUB_DIR_UIS ${ALL_SUB_DIR_UIS} ${TEMP_UIS}) 
        SET(ALL_SUB_DIR_RCS ${ALL_SUB_DIR_RCS} ${TEMP_RCS}) 
        
        #File Groups
        SOURCE_GROUP( "_${_dir_}" FILES 
        ${TEMP_SOURCES_HDR} 
        ${TEMP_SOURCES_SRC}
        ${TEMP_UIS}
        ${TEMP_RCS}
    )
    ENDFOREACH( _dir_ ${sub_dirs} )
    
    DEBUG_MESSAGE( "MACRO:ALL_SUB_DIR_SRCS:${ALL_SUB_DIR_SRCS}")
    DEBUG_MESSAGE( "MACRO:ALL_SUB_DIR_UIS:${ALL_SUB_DIR_UIS}")
    DEBUG_MESSAGE( "MACRO:ALL_SUB_DIR_RCS:${ALL_SUB_DIR_RCS}")
    
    SET(${lib_name}_LIB_HEADERS ${${lib_name}_LIB_HEADERS} ${ALL_SUB_DIR_HDR})
    SET(${lib_name}_LIB_SRCS ${${lib_name}_LIB_SRCS} ${ALL_SUB_DIR_SRCS})
    SET(LIB_QT_UIS ${LIB_QT_UIS} ${ALL_SUB_DIR_UIS})
    SET(LIB_QT_RCS ${LIB_QT_RCS} ${ALL_SUB_DIR_RCS})
ENDMACRO(VIRE_SUB_DIR_SEARCH_FILES_FOR_LIB_INNER lib_name)

#====================================================================================================
#############################################################
#VIRE_TARGET_SERACH_SUB_DIRS_FILES
#此宏主要是查找子目录，将查找到的头文件、源文件、UI文件、QRC文件分别依附到“处理树上”，并将以在公程中以子目录分类显示
#
MACRO(VIRE_TARGET_SERACH_SUB_DIRS_FILES target_name)
    TARGET_SERACH_SUB_DIRS_FILES(${target_name} ${ARGN})
ENDMACRO(VIRE_TARGET_SERACH_SUB_DIRS_FILES target_name)

#############################################################
#VIRE_SERACH_LIB_SUB_DIRS_FILES
#此宏主要是查找子目录，将查找到的头文件、源文件、UI文件、QRC文件分别依附到“处理树上”，并将以在公程中以子目录分类显示
#
MACRO(VIRE_SERACH_LIB_SUB_DIRS_FILES lib_name)
    SET(sub_dirs ${ARGN})
    VIRE_TARGET_SERACH_SUB_DIRS_FILES(${lib_name} ${sub_dirs})
ENDMACRO(VIRE_SERACH_LIB_SUB_DIRS_FILES lib_name)
#====================================================================================================
include(macro_target_source_group)

MACRO(VIRE_TARGET_SOURCE_GROUP target_name)
   TARGET_SOURCE_GROUP(${target_name})
ENDMACRO()

MACRO(VIRE_SOURCE_GROUP)
    TARGET_SOURCE_GROUP(${LIB_NAME})
ENDMACRO(VIRE_SOURCE_GROUP)

#=======================================================================================
MACRO(VIRE_POST_BUILD_COPY_EXE target_name destDir)

ENDMACRO()
