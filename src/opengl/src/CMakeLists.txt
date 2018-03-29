SET(THIS_FOLDER_NAME Study_OPENGL/OpenGL_SupperBible)

get_filename_component(THIS_DIR_NAME 
${CMAKE_CURRENT_LIST_FILE} 
DIRECTORY)

MESSAGE("${THIS_FOLDER_NAME}")
SET(THIS_OPENGL_HEADER_DIR ${THIS_DIR_NAME}/include)
SET(THIS_OPENGL_LIB_DIR ${THIS_DIR_NAME}/lib)

set(_list_dir 
	T001_HelloTriangle
	#T002_MoveRectangle
	#T003_Bounce
)

foreach(dir ${_list_dir})
    ADD_SUBDIRECTORY (${dir})
    if(TARGET ${dir})
    	target_include_directories(${dir} PUBLIC
			${VIRE_INCLUDE_DIR}
			${Boost_INCLUDE_DIR}
    		)
    endif()
endforeach()

