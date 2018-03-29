SET(THIS_FOLDER_NAME Study_OPENGL)

get_filename_component(THIS_DIR_NAME 
${CMAKE_CURRENT_LIST_FILE} 
DIRECTORY)

MESSAGE("${THIS_FOLDER_NAME}")
SET(THIS_OPENGL_HEADER_DIR ${THIS_DIR_NAME}/include)
SET(THIS_OPENGL_LIB_DIR ${THIS_DIR_NAME}/lib)

OPTION(Build_OpenGL_SupperBible  "Build OpenGL_SupperBible...." OFF)

set(_list_dir 
	#src/test1
	#src/test2
)

if(Build_OpenGL_SupperBible)
	list(APPEND _list_dir "src/OpenGL_SupperBible")
	
endif()

foreach(dir ${_list_dir})
    ADD_SUBDIRECTORY (${dir})
    if(TARGET ${dir})
    	target_include_directories(${dir} PUBLIC
			${VIRE_INCLUDE_DIR}
			${Boost_INCLUDE_DIR}
			${DSS_INCLUDE_DIR}/DSSLibs
    		)
    endif()
endforeach()

