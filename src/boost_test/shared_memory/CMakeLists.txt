SET(THIS_FOLDER_NAME Boost_test/interprocess)

get_filename_component(THIS_DIR_NAME 
	${CMAKE_CURRENT_LIST_FILE} 
	DIRECTORY
)

MESSAGE("${THIS_FOLDER_NAME}")
SET(THIS_OPENGL_HEADER_DIR ${THIS_DIR_NAME}/include)
SET(THIS_OPENGL_LIB_DIR ${THIS_DIR_NAME}/lib)

set(_list_dir 
shared_memery_01_reader
shared_memery_01_writer
)

foreach(dir ${_list_dir})
    ADD_SUBDIRECTORY (${dir})
    if(TARGET ${dir})
    	target_include_directories(${dir} PUBLIC
			${VIRE_INCLUDE_DIR}
			${Boost_INCLUDE_DIR}
			${THIS_DIR_NAME}/inc
		)

    endif()
endforeach()

