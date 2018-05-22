set(_list_dir 
	shared_memory

)

foreach(dir ${_list_dir})
    ADD_SUBDIRECTORY (${dir})
endforeach()

