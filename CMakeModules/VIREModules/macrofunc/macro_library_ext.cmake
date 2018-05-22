#definition the library type
MACRO(DEFINITION_STATIC_LIBRARY _lib_name _true_or_false)
	SET(${_lib_name}_USE_STATIC_LIBRARY ${_true_or_false})
	IF(NOT ${_lib_name}_USE_STATIC_LIBRARY)
		ADD_DEFINITIONS(
			-D${_lib_name}_LIBRARY
		)	
	ENDIF()
ENDMACRO()

MACRO(ADD_LIBRARY_EX _lib_name)
	SET(_use_static false)
	IF(${_lib_name}_USE_STATIC_LIBRARY)
		#IF(${${_lib_name}_USE_STATIC_LIBRARY})
			set(_use_static TRUE)
		#ENDIF()
	ENDIF()

    IF(_use_static)
    	MESSAGE(STATUS "ADD_LIBRARY With Static!!!")
		ADD_LIBRARY(${_lib_name} STATIC 
			${ARGN}
		)
	ELSE()
		MESSAGE(STATUS "ADD_LIBRARY With Shared!!!")
        ADD_LIBRARY(${_lib_name} SHARED 
			${ARGN}
		)
    ENDIF()
ENDMACRO()
