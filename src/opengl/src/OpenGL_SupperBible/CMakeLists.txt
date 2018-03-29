SET(THIS_FOLDER_NAME Study_OPENGL/OpenGL_SupperBible)

get_filename_component(THIS_DIR_NAME 
${CMAKE_CURRENT_LIST_FILE} 
DIRECTORY)

MESSAGE("${THIS_FOLDER_NAME}")
SET(THIS_OPENGL_HEADER_DIR ${THIS_DIR_NAME}/include)
SET(THIS_OPENGL_LIB_DIR ${THIS_DIR_NAME}/lib)

function(ADD_SUBDIR_TARGETS lstTargets)
	foreach(dir ${${lstTargets}})
		ADD_SUBDIRECTORY (${dir})
		if(TARGET ${dir})
			target_include_directories(${dir} PUBLIC
				${VIRE_INCLUDE_DIR}
				${Boost_INCLUDE_DIR}
				${CMAKE_SOURCE_DIR}/src/library_src/GLTools/include
			)
		endif()
	endforeach()
endfunction()

function(_ADD_SUBDIR_IN_FOLDER _cur_dir)	
	if(NOT EXISTS ${_cur_dir})
		SET(_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
	endif()

	file(GLOB_RECURSE var "*.cpp")	
	foreach(_file ${var})
		STRING(REGEX REPLACE ${_cur_dir}/\(.*\) \\1 _filepath ${_file})

		COMMON_CHECK_DEBUG_MSG( 
			"1.SOURE_GROUP Relative File Path:${_filepath}"
			${ARGN})

		STRING(REGEX REPLACE "\(.*\)/.*" \\1 _dir_name ${_filepath})

		COMMON_CHECK_DEBUG_MSG(
			"2.SOURE_GROUP Group Name:${_dir_name}"
			${ARGN})
			
		STRING(REPLACE "/" "\\" _dir_name ${_dir_name})

		ADD_SUBDIRECTORY(${_dir_name})
		if(TARGET ${_dir_name})
			target_include_directories(${_dir_name} PUBLIC
				${VIRE_INCLUDE_DIR}
				${Boost_INCLUDE_DIR}
				${CMAKE_SOURCE_DIR}/src/library_src/GLTools/include
			)
		endif()
	endforeach()
endfunction()

set(_list_dir
	Chapter01
	Chapter02
	Chapter03
	Chapter04
)

ADD_SUBDIR_TARGETS(_list_dir)
