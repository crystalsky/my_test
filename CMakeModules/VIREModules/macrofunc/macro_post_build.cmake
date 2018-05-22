#此文件定义用于生成完成后自动拷贝文件到目录
#主要用于程序打包（发布）版本库的自动更新到目录
#可以自己设定生成到的目录
#==========================================================================
MACRO(POST_BUILD_CONFIG)
	# IF(_x${config_name} STREQUAL "_x")
	# 	MESSAGE(FATAL_ERROR "You Must Set Install Config Name....")
	# ENDIF()
	# OPTION(${config_name}_PostBuild_Copy "${config_name}_PostBuild Copy Target File To Dir..." OFF)

	# UNSET(_MY_POST_BUILD_CONFIG_NAME)
	# SET(_MY_POST_BUILD_CONFIG_NAME ${config_name})

	# IF(${config_name}_PostBuild_Copy)
	# 	SET(${config_name}_PostBuild_CopyDir ${PROJECT_SOURCE_DIR}/PostBuildCopyFiles CACHE PATH "...")
	# 	UNSET(_MY_POST_COPY_DIR)
	# 	SET(_MY_POST_COPY_DIR ${${config_name}_PostBuild_CopyDir})
	# ENDIF()
	MESSAGE(STATUS "POST_BUILD_CONFIG.....: ${ProjectVal_PREFIX_POST_BUILD}")
	OPTION(${ProjectVal_PREFIX_POST_BUILD}_CONFIG "${ProjectVal_PREFIX_POST_BUILD} Copy Target File To Dir..." OFF)

	UNSET(_MY_POST_BUILD_CONFIG_NAME)
	SET(_MY_POST_BUILD_CONFIG_NAME ${config_name})

	IF(${ProjectVal_PREFIX_POST_BUILD}_CONFIG)
		SET(${ProjectVal_PREFIX_POST_BUILD}_CopyDir ${PROJECT_SOURCE_DIR}/PostBuildCopyFiles CACHE PATH "...")
		UNSET(_MY_POST_COPY_DIR)
		SET(_MY_POST_COPY_DIR ${${ProjectVal_PREFIX_POST_BUILD}_CopyDir})
	ENDIF()
ENDMACRO()

#include(macro_post_build_proc)
MACRO(POST_BUILD_COPY target_name)
	IF(${_MY_POST_BUILD_CONFIG_NAME}_PostBuild_Copy)
    	_POST_BUILD_PROC(${target_name} COPY_DEST_DIR ${_MY_POST_COPY_DIR} POST_BUILD_COPY ${ARGN})
    ENDIF()
ENDMACRO()
#==========================================================================
MACRO(_POST_BUILD_PROC target_name)
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