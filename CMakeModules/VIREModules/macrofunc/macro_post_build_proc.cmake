MACRO(POST_BUILD_PROC target_name)
    set(options EXE POST_BUILD_COPY)
    set(oneValueArgs COPY_DEST_DIR SUBDIR)
    set(multiValueArgs )

    cmake_parse_arguments(${target_name} 
        "${options}" 
        "${oneValueArgs}" 
        "${multiValueArgs}" 
        ${ARGN})

    IF(${target_name}_POST_BUILD_COPY)
    	MESSAGE(STATUS "POST_BUILD_COPY Copy File...${target_name}")
    	IF(NOT ${target_name}_COPY_DEST_DIR)
    		SET(${target_name}_COPY_DEST_DIR ${PROJECT_SOURCE_DIR}/PostBuildCopyFiles)
    	ENDIF()

    	IF(${target_name}_SUBDIR)
            STRING(CONCAT ${target_name}_COPY_DEST_DIR ${${target_name}_COPY_DEST_DIR} "/" ${${target_name}_SUBDIR})
            #MESSAGE(STATUS "POST_BUILD_COPY CONCAT ${${target_name}_COPY_DEST_DIR}")
    	ENDIF()

    	IF(NOT EXISTS ${${target_name}_COPY_DEST_DIR})
	        make_directory(${${target_name}_COPY_DEST_DIR})
	    ENDIF()

	    IF(CMAKE_C_FLAGS_RELEASE)
	        SET(_FILE_EXT ".dll")
	        IF(${target_name}_EXE)
	            SET(_FILE_EXT ".exe")
	        ENDIF()

	        GET_PROPERTY(${target_name}_OUT_PUT_DIR TARGET ${target_name} PROPERTY RUNTIME_OUTPUT_DIRECTORY_RELEASE)
	        IF(NOT EXISTS ${${target_name}_OUT_PUT_DIR})
	        	MESSAGE(WARNING "POST_BUILD_COPY NOT EXISTS ${target_name}_OUT_PUT_DIR")
	        ENDIF()
	        SET(${target_name}_FILE ${${target_name}_OUT_PUT_DIR}/${target_name}${_FILE_EXT})
	         
	        IF(EXISTS ${${target_name}_FILE})
	            add_custom_command(
	                TARGET ${target_name} POST_BUILD
	                #COMMAND ${CMAKE_COMMAND} -E echo "  -->Copying ${${target_name}_OUT_PUT_DIR}/${target_name}${_FILE_EXT} To  ${${target_name}_COPY_DEST_DIR}/${target_name}${_FILE_EXT}..."
	                COMMAND ${CMAKE_COMMAND} -E echo "  -->Copying Target File To ${${target_name}_COPY_DEST_DIR}/${target_name}${_FILE_EXT}..."
	                COMMAND ${CMAKE_COMMAND} -E copy_if_different ${${target_name}_OUT_PUT_DIR}/${target_name}${_FILE_EXT} ${${target_name}_COPY_DEST_DIR}/${target_name}${_FILE_EXT}
	            )
	        ENDIF()
	    ENDIF()
	ENDIF()
ENDMACRO()