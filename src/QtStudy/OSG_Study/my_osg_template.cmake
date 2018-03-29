function(MAKE_OSG_TEMP_CLASS_FILES _lib_name)
    SET(LIBRARY_NAME ${_lib_name})

    SET(options )
    SET(oneValueArgs SUB_DIR_NAME H_TEMPLATE SRC_TEMPLATE)
    SET(multiValueArgs)
    cmake_parse_arguments(${LIBRARY_NAME} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    SET(_make_class_dir ${CMAKE_CURRENT_LIST_DIR})
    if(${LIBRARY_NAME}_SUB_DIR_NAME)
       SET(_make_class_dir ${CMAKE_CURRENT_LIST_DIR}/${${LIBRARY_NAME}_SUB_DIR_NAME})
    endif()

    IF(NOT ${LIBRARY_NAME}_H_TEMPLATE)
    	SET(${LIBRARY_NAME}_H_TEMPLATE ${CMAKE_CURRENT_LIST_DIR}/my_osg_template.h.in)
    ENDIF()

    IF(NOT ${LIBRARY_NAME}_SRC_TEMPLATE)
    	SET(${LIBRARY_NAME}_SRC_TEMPLATE ${CMAKE_CURRENT_LIST_DIR}/my_osg_template.cpp.in)
    ENDIF()
    
    foreach(_class_file_name ${${LIBRARY_NAME}_UNPARSED_ARGUMENTS})
        SET(Class_File_Name ${_class_file_name})
        
        IF(NOT EXISTS ${_make_class_dir}/${Class_File_Name}.h)
            MESSAGE(STATUS "    ...Ready make file:
        ${${LIBRARY_NAME}_H_TEMPLATE}-->
        ${_make_class_dir}/${Class_File_Name}.h")
            CONFIGURE_FILE(
            	${${LIBRARY_NAME}_H_TEMPLATE} 
            	${_make_class_dir}/${Class_File_Name}.h
            )
        ENDIF()
       
       IF(NOT EXISTS ${_make_class_dir}/${Class_File_Name}.cpp)
            MESSAGE(STATUS "    ...Ready make file:
        ${${LIBRARY_NAME}_SRC_TEMPLATE}-->
        ${_make_class_dir}/${Class_File_Name}.cpp")
            CONFIGURE_FILE(
            	${${LIBRARY_NAME}_SRC_TEMPLATE} 
            	${_make_class_dir}/${Class_File_Name}.cpp
            )
        ENDIF()
    endforeach()
endfunction()
