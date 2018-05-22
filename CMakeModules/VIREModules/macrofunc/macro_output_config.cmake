
#======================================================================
MACRO(_MAKE_OUTPUT_DIR config_name path)
  IF(NOT EXISTS ${path})
    MAKE_DIRECTORY(${path})
  ENDIF()

  #SET(VR_OUTPUT_BINARIES_DIR "${PROJECT_SOURCE_DIR}/bin" CACHE STRING "The Default OutPutDir")
  SET(${config_name}_OUTPUT_BIN_DIR ${path})

  SET(${config_name}_OUTPUT_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)
  MAKE_DIRECTORY(${${config_name}_OUTPUT_LIB_DIR})

  MESSAGE(STATUS "${config_name}_OUTPUT_BIN_DIR = ${${config_name}_OUTPUT_BIN_DIR}")

  SET(VIRE_OUTPUT_BIN_DIR ${${config_name}_OUTPUT_BIN_DIR})
  SET(VIRE_OUTPUT_LIB_DIR ${${config_name}_OUTPUT_LIB_DIR})

  SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${VIRE_OUTPUT_LIB_DIR})
  SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${VIRE_OUTPUT_BIN_DIR})
  SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${VIRE_OUTPUT_BIN_DIR})
ENDMACRO()


MACRO(OUTPUT_CONFIG config_name)
	IF(_x${config_name} STREQUAL "_x")
		MESSAGE(FATAL_ERROR "You Must Set Output Config Name....")
	ENDIF()
	OPTION(${config_name}_OutPutConfig "${config_name}_OutPutConfig Output Target File To Dir..." OFF)

	UNSET(_MY_OUTPUTCONFIG_NAME)
	SET(_MY_OUTPUTCONFIG_NAME ${config_name})

	IF(${config_name}_OutPutConfig)
		SET(${config_name}_OutPutConfigDir ${PROJECT_SOURCE_DIR}/Bin CACHE PATH "...")
		
		#Last Variable Set
		UNSET(_MY_OUTPUTCONFIG_DIR)
		SET(_MY_OUTPUTCONFIG_DIR ${${config_name}_OutPutConfigDir})

		_MAKE_OUTPUT_DIR(${config_name} ${_MY_OUTPUTCONFIG_DIR})
	ELSE()
		_MAKE_OUTPUT_DIR(${config_name} ${PROJECT_SOURCE_DIR}/Bin)
	ENDIF()
ENDMACRO()

