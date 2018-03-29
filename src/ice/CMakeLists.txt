MACRO(SEARCH_FILE_TO_VAL val_to_set)
	foreach(val ${ARGN})
		file(GLOB temp_source "${val}.*" "${val}")
		set(${val_to_set} ${${val_to_set}} ${temp_source})
	endforeach()
ENDMACRO()

MACRO(SEARCH_DIR_FILE_TO_VAL val_to_set dir)
	foreach(val ${ARGN})
		file(GLOB temp_source "${dir}/${val}.*" "${dir}/${val}")
		set(${val_to_set} ${${val_to_set}} ${temp_source})
	endforeach()
ENDMACRO()

#/////////////////////////////////////////////////////////////////////////
ADD_SUBDIRECTORY(Printer_Test)

ADD_SUBDIRECTORY(DSS_ICEService)
ADD_SUBDIRECTORY(DSSIceService_Test)

option(BUILDICE_proj_ice_fileproc "Build Example Of Ice Callback..." OFF)
if(BUILDICE_proj_ice_fileproc)
	ADD_SUBDIRECTORY(ice_fileproc)
endif()

option(BUILDICE_proj_ice_callback "Build Example Of Ice Callback..." OFF)
if(BUILDICE_proj_ice_callback)
	ADD_SUBDIRECTORY(ice_callback)
endif()