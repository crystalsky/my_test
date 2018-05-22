#_DECIDE_INSTALL_DIR(${TARGET_NAME} FRAMEWORK_MODE INCLUDE_ADD_DIR ${BASE_DIR_NAME})
MACRO(_DECIDE_INSTALL_DIR _libName)
    set(options )#是否是框架安装,如果不是框架的安装方式，就以独立库的方式安装处理
    set(oneValueArgs FRAMEWORK_MODE VERSIONED_LIB INCLUDE_ADD_DIR VERSION_DIR)#增加的包含目录处理 ： include/${dir}/&{libname}
    set(multiValueArgs PATHS)
      
    cmake_parse_arguments(${_libName} 
        "${options}" 
        "${oneValueArgs}" 
        "${multiValueArgs}" 
        ${ARGN})

    if(NOT ${_libName}_FRAMEWORK_MODE)
        MESSAGE(STATUS "Install The ${_libName}, SingleInstall Mode...${ARGN}")
        set(${_libName}_lib_dir )
		set(${_libName}_bin_dir ) 
		COMMON_GET_LIBRARY_DIR_INFO(
			${_libName} 
			${_libName}_lib_dir
			${_libName}_bin_dir
			${ARGN}
		)

		set(_root_dir ${_libName})
		if(${_libName}_VERSION_DIR)
			set(_version_target_name "${_libName}::TARGET_VERSION")
			if(TARGET ${_version_target_name})
				get_property(${_libName}_version 
					TARGET ${_version_target_name}
					PROPERTY TARGET_VERSION
					#SET
				)
				if(NOT "x${${_libName}_version}" STREQUAL "x")
					set(_root_dir "${_libName}-${${_libName}_version}")
					MESSAGE(STATUS "   ---->  SingleInstall Mode VERSION_DIR=${${_libName}_VERSION_DIR} At:${_root_dir}")
				endif()
			endif()
		endif()

        set(${_libName}_INSTALL_HEADER  ${_root_dir}/include)
        set(${_libName}_INSTALL_RUNTIME ${_root_dir}/${${_libName}_bin_dir})
        set(${_libName}_INSTALL_LIBRARY ${_root_dir}/${${_libName}_lib_dir})
        set(${_libName}_INSTALL_ARCHIVE ${_root_dir}/${${_libName}_lib_dir})
    else()
        MESSAGE(STATUS "Install The ${_libName}, Framework Install Mode...")
        
        set(${_libName}_lib_dir )
		set(${_libName}_bin_dir )
		
		if(${_libName}_VERSIONED_LIB)
			COMMON_GET_LIBRARY_DIR_INFO(
				${_libName} 
				${_libName}_lib_dir
				${_libName}_bin_dir
				${ARGN}
			)
		else()
			IF(NOT CMAKE_CL_64)
				set(${_libName}_lib_dir "lib")
				set(${_libName}_bin_dir "bin")
			ELSE()
				set(${_libName}_lib_dir "lib/x64")
				set(${_libName}_bin_dir "bin/x64")
			ENDIF()
		endif()

        IF(x${_libName}_INCLUDE_ADD_DIR STREQUAL "x")
        	set(${_libName}_INSTALL_HEADER  include/${_libName})
        ELSE()
        	set(${_libName}_INSTALL_HEADER  include/${${_libName}_INCLUDE_ADD_DIR}/${_libName})
        ENDIF()
        set(${_libName}_INSTALL_RUNTIME ${${_libName}_bin_dir})
        set(${_libName}_INSTALL_LIBRARY ${${_libName}_lib_dir})
        set(${_libName}_INSTALL_ARCHIVE ${${_libName}_lib_dir})
    endif()

    COMMON_CHECK_DEBUG_MSG("${_libName}_INSTALL_HEADER = ${CMAKE_INSTALL_PREFIX}/${${_libName}_INSTALL_HEADER}" ${ARGN})
    COMMON_CHECK_DEBUG_MSG("${_libName}_INSTALL_RUNTIME = ${CMAKE_INSTALL_PREFIX}/${${_libName}_INSTALL_RUNTIME}" ${ARGN})
    COMMON_CHECK_DEBUG_MSG("${_libName}_INSTALL_LIBRARY = ${CMAKE_INSTALL_PREFIX}/${${_libName}_INSTALL_LIBRARY}" ${ARGN})
    COMMON_CHECK_DEBUG_MSG("${_libName}_INSTALL_ARCHIVE = ${CMAKE_INSTALL_PREFIX}/${${_libName}_INSTALL_ARCHIVE}" ${ARGN})
ENDMACRO()

function(func1 lst)
    set(_my_list ${${lst}})
    MESSAGE(STATUS "  -->func1:${_my_list}")
endfunction()

function(mac1 lst)
    set(_my_list ${${lst}})
    MESSAGE(STATUS "  -->mac1:${_my_list}")
endfunction()

macro(__INSTALL_WITH_PDB_FILE target_name)
	set(options INSTALL_PDB)
    set(oneValueArgs )
    set(multiValueArgs )

    cmake_parse_arguments(${target_name} 
        "${options}" 
        "${oneValueArgs}" 
        "${multiValueArgs}" 
        ${ARGN})
    
	IF(CMAKE_C_FLAGS_DEBUG AND ${target_name}_INSTALL_PDB)
	  	GET_PROPERTY(${target_name}_OUT_PUT_DIR TARGET ${target_name} PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG)
	    SET(${target_name}_PDB_FILE ${${target_name}_OUT_PUT_DIR}/${target_name}${CMAKE_DEBUG_POSTFIX}.pdb)
	    IF(EXISTS ${${target_name}_PDB_FILE})
	        MESSAGE(STATUS "Find ${target_name} PDB File: ${${target_name}_PDB_FILE}")
	        INSTALL(
	            FILES ${${target_name}_PDB_FILE} 
	            DESTINATION ${${target_name}_INSTALL_RUNTIME} 
	            COMPONENT Development
	        )
	    ELSE()
	        #MESSAGE(WARNING "No Find ${target_name} PDB File...")
	    ENDIF()
	ENDIF()
endmacro()

MACRO(_INSTALL_HEADER_FILES target_name header_files)
	set(options)
    set(oneValueArgs )
    set(multiValueArgs DIRS)

    cmake_parse_arguments(${target_name} 
        "${options}" 
        "${oneValueArgs}" 
        "${multiValueArgs}" 
		${ARGN}
	)
    
    list(LENGTH ${target_name}_DIRS _len_of_dir)
    if(NOT _len_of_dir EQUAL 0)
    	MESSAGE(STATUS "===Begin Header_files Dir Mode....${${target_name}_DIRS}")
    	#generate the regexp val from all the dirs
	    #like "(\/Dir1\/)|(\/Dir2\/)|(\/Dir3\/)"
	    set(_regex_string)
	    foreach(dir ${${target_name}_DIRS})
	    	STRING(REPLACE "val" ${dir} _rstring "\\/val\\/")
	    	STRING(CONCAT _regex_string ${_regex_string} ${_rstring} "|")
	    endforeach()
	    string(LENGTH ${_regex_string} _len_of_string)
	    math(EXPR len "${_len_of_string} - 1")
	    string(SUBSTRING ${_regex_string} 0 ${len} _regex_string)
	    MESSAGE(STATUS "Find Regexp: ${_regex_string}")
	    
	    #MESSAGE(STATUS "header_files: ${${header_files}}")
	    #match process
	    set(_files_not_in_dir)
	    set(_checked_install_dirs )
		foreach(hdr_file ${${header_files}})
	    	string(REGEX MATCH ${_regex_string} _match ${hdr_file})
	    	#MESSAGE(STATUS "file: ${hdr_file} find ${dir} At:${_match}")
	    	if(x${_match} STREQUAL "x")
	    		#MESSAGE(STATUS "single file: ${hdr_file}")
	    		list(APPEND _files_not_in_dir ${hdr_file})
	    	else()
	    		get_filename_component(_dir_of_file ${hdr_file} DIRECTORY)
	    		#MESSAGE(STATUS "_dir_of_file=${_dir_of_file}")
	    		list(APPEND _checked_install_dirs ${_dir_of_file})
	    	endif()
	    endforeach()
	    list(REMOVE_DUPLICATES _checked_install_dirs)
	    MESSAGE(STATUS "_files_not_in_dir: ${_files_not_in_dir}")
	    MESSAGE(STATUS "_checked_install_dirs: ${_checked_install_dirs}")

	    INSTALL(
	  		FILES ${_files_not_in_dir}
	  		DESTINATION ${${target_name}_INSTALL_HEADER}
	  		COMPONENT Development
	  	)
	    
	    INSTALL(
	  		DIRECTORY ${_checked_install_dirs}
	  		DESTINATION ${${target_name}_INSTALL_HEADER}
	  		COMPONENT Development
	  	)
	  	MESSAGE(STATUS "===End Header_files Dir Mode!!!")
	else()
		INSTALL(
	  		FILES ${${header_files}}
	  		DESTINATION ${${target_name}_INSTALL_HEADER}
	  		COMPONENT Development
	  	)
    endif()
ENDMACRO()

#==============================================================
MACRO(_INSTALL_PROC_BASE_T1 target_name header_files)
	#MESSAGE(STATUS "_INSTALL_PROC_BASE_T1...")
	#===================================================
	_DECIDE_INSTALL_DIR(${target_name} ${ARGN})
	#===================================================
	#INSTALL(
	#  FILES ${${header_files}}
	#  DESTINATION ${${target_name}_INSTALL_HEADER}
	#  COMPONENT Development
	#  )
	_INSTALL_HEADER_FILES(${target_name} ${header_files} ${ARGN})
	#===================================================
	__INSTALL_WITH_PDB_FILE(${target_name} ${ARGN})
	#===================================================
	INSTALL(
	    TARGETS ${target_name}
	    RUNTIME DESTINATION ${${target_name}_INSTALL_RUNTIME} COMPONENT Runtime
	    LIBRARY DESTINATION ${${target_name}_INSTALL_LIBRARY} COMPONENT Development
	    ARCHIVE DESTINATION ${${target_name}_INSTALL_ARCHIVE} COMPONENT Development
	)
	#===================================================
ENDMACRO()
#==============================================================

#==============================================================
MACRO(_INSTALL_PROC_BASE_T2 target_name header_files)
	
ENDMACRO()
#==============================================================

