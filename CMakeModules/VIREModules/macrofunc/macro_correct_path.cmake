#---------------------------------------------------
# MACRO CORRECT_PATH VAR PATH 
# corrects slashes in PATH to be cmake conformous ( / ) 
# and puts result in VAR 
#---------------------------------------------------
MACRO(CORRECT_PATH VAR PATH)
    SET(${VAR} ${PATH})
	IF(WIN32)    
    	STRING(REGEX REPLACE "/" "\\\\" ${VAR} "${PATH}")
    	#file(TO_CMAKE_PATH ${PATH} ${VAR})
	ENDIF(WIN32)    
ENDMACRO()