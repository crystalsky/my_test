#
# Try to find PITCHRTI library and include path.
# Once done this will define
#
# PITCHRTI_FOUND
# PITCHRTI_INCLUDE_PATH
# PITCHRTI_NG_LIBRARY
# 
IF (WIN32)
    include(util.common_get_msvc_version_lib_dir)
    COMMON_GET_MSVC_VERSION_LIB_DIR(libdir)
    message(STATUS "-->PITCHRTI_HOME:${PITCHRTI_HOME}---${libdir}")

    find_path(PITCHRTI_INCLUDE_DIR
        NAMES RTI.hh
        PATHS ${PITCHRTI_HOME}
        PATH_SUFFIXES include include/HLA13
        DOC "The RTI Include Files")

    find_library(PITCHRTI_NG_LIBRARY_DEBUG
        NAMES libRTI-NGd
        PATHS ${PITCHRTI_HOME}
        PATH_SUFFIXES ${libdir}
        DOC "The RTI-NG Debug Library")

    find_library(PITCHRTI_NG_LIBRARY
        NAMES libRTI-NG
        PATHS ${PITCHRTI_HOME}
        PATH_SUFFIXES ${libdir}
        DOC "The RTI-NG Library")

    message(STATUS "-->PITCHRTI_FEDTIME_NEWTIME_LIBRARY_DEBUG:${PITCHRTI_HOME}/${libdir}/newtime")
    find_library(PITCHRTI_FEDTIME_NEWTIME_LIBRARY_DEBUG
        NAMES libfedtimed
        PATHS ${PITCHRTI_HOME}
        PATH_SUFFIXES ${libdir}/newtime
        DOC "The libfedtime newtiem Debug Library")

    find_library(PITCHRTI_FEDTIME_NEWTIME_LIBRARY
        NAMES libfedtime
        PATHS ${PITCHRTI_HOME}
        PATH_SUFFIXES ${libdir}/newtime
        DOC "The libfedtime newtime Library")

    find_library(PITCHRTI_FEDTIME_OLDTIME_LIBRARY_DEBUG
        NAMES libfedtimed
        PATHS ${PITCHRTI_HOME}
        PATH_SUFFIXES ${libdir}/oldtime
        DOC "The RTI-NG Debug Library")

    find_library(PITCHRTI_FEDTIME_OLDTIME_LIBRARY
        NAMES libfedtime
        PATHS ${PITCHRTI_HOME}
        PATH_SUFFIXES ${libdir}/oldtime
        DOC "The RTI-NG Library")

ELSE (WIN32)
	
ENDIF (WIN32)

include(macro_find_package_handle_standard_args)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PITCHRTI
	FOUND_VAR PITCHRTI_FOUND 	
	REQUIRED_VARS PITCHRTI_INCLUDE_DIR 
	PITCHRTI_NG_LIBRARY 
	PITCHRTI_NG_LIBRARY_DEBUG
)
MESSAGE(STATUS "PITCHRTI_FOUND...............${PITCHRTI_FOUND}")
IF(NOT PITCHRTI_FOUND)
	MESSAGE(FATAL_ERROR "--PITCHRTI not found")
ENDIF(NOT PITCHRTI_FOUND)

if(PITCHRTI_FOUND)
	set(PITCHRTI_LIBRARIES ${PITCHRTI_NG_LIBRARY_DEBUG} ${PITCHRTI_NG_LIBRARY})
	
	include(util.common_make_import_target)
	COMMON_MAKE_IMPORT_TARGET_BASE(PITCHRTI PITCHRTI_NG
		${PITCHRTI_INCLUDE_DIR}
        #${PITCHRTI_NG_LIBRARY_DEBUG}
        ${PITCHRTI_NG_LIBRARY}
		${PITCHRTI_NG_LIBRARY}
    )
    
    #COMMON_MAKE_IMPORT_TARGET_BASE(PITCHRTI PITCHRTI_FEDTIME_NEWTIME
    #    ${PITCHRTI_INCLUDE_DIR}
    #    ${PITCHRTI_FEDTIME_NEWTIME_LIBRARY_DEBUG}
    #    ${PITCHRTI_FEDTIME_NEWTIME_LIBRARY}
    #)

    COMMON_MAKE_IMPORT_TARGET_BASE(PITCHRTI PITCHRTI_FEDTIME_OLDTIME
        ${PITCHRTI_INCLUDE_DIR}
        ${PITCHRTI_FEDTIME_OLDTIME_LIBRARY}
        ${PITCHRTI_FEDTIME_OLDTIME_LIBRARY}
    )
endif()

set(RTI_DEFINITIONS "-DRTI_USES_STD_FSTREAM")

mark_as_advanced(
  PITCHRTI_INCLUDE_DIR
  PITCHRTI_NG_LIBRARY_DEBUG
  PITCHRTI_NG_LIBRARY
)
