#---------------------------------------------------
# MACRO CORRECT_PATH VAR PATH 
# corrects slashes in PATH to be cmake conformous ( / ) 
# and puts result in VAR 
#---------------------------------------------------
MACRO(MAKE_CORRECT_PATH VAR PATH)
    SET(${VAR} ${PATH} )
	IF(WIN32)    
	    STRING(REGEX REPLACE "\\\\" "/" outVal "${PATH}")
	    SET(${VAR} ${outVal})
	ENDIF()    
ENDMACRO()