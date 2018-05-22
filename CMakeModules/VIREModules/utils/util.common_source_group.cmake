macro(common_source_group_by_file_base_name groupname)
    if(MSVC)
        #MESSAGE(STATUS "source_group_ex begin groupName:${groupname}....")
        
        SET(options)
        SET(oneValueArgs HEADER_DIR_PATH)
        SET(multiValueArgs)
        cmake_parse_arguments(FILE
          "${options}" 
          "${oneValueArgs}" 
          "${multiValueArgs}" 
          ${ARGN}) 

        #MESSAGE(STATUS "source_group_ex header dir ${FILE_HEADER_DIR_PATH}     files:${FILE_UNPARSED_ARGUMENTS}")    
        if(NOT FILE_HEADER_DIR_PATH)
            SET(FILE_HEADER_DIR_PATH ${CMAKE_CURRENT_SOURCE_DIR})
        endif()
        #MESSAGE(STATUS "source_group_ex header dir ${${FILE}_HEADER_DIR_PATH}")    

        SET(_filepath "")
        #MESSAGE(STATUS "111 source_group_ex header: ${_filepath}")
        foreach(file ${FILE_UNPARSED_ARGUMENTS})
            #MESSAGE(STATUS "${file}")
            if(EXISTS ${FILE_HEADER_DIR_PATH}/${file}.h)
                SET(_filepath ${_filepath} ${FILE_HEADER_DIR_PATH}/${file}.h)
            elseif(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${file}.h)
                SET(_filepath ${_filepath} ${CMAKE_CURRENT_SOURCE_DIR}/${file}.h)
            endif()
            if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${file}.cpp)
                SET(_filepath ${_filepath} ${CMAKE_CURRENT_SOURCE_DIR}/${file}.cpp)     
            endif()
        endforeach()

        #MESSAGE(STATUS "source_group_ex header: ${_filepath}")

        source_group(${groupname} FILES ${_filepath})

    endif(MSVC)
endmacro()

macro(common_source_group_by_file_base_name_headerdir groupname header_dir)
    common_source_group_by_file_base_name(${groupname} ${HEADER_DIR_PATH} ${ARGN})
endmacro()

include(util.common_check_debug)
macro(common_source_group_by_subdir)
    if(MSVC)
        SET(options)
        SET(oneValueArgs)
        SET(multiValueArgs FILES)
        cmake_parse_arguments(_GROUPED
          "${options}" 
          "${oneValueArgs}" 
          "${multiValueArgs}" 
          ${ARGN})

        SET(_all_grouped_files ${_GROUPED_FILES} ${_GROUPED_UNPARSED_ARGUMENTS}) 
        
        COMMON_CHECK_DEBUG(_is_debug)
        if(_is_debug)        
            MESSAGE(STATUS "common_source_group_by_subdir files : ${_all_grouped_files}")
        endif()
        
        SET(_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
        
        foreach(_file ${_all_grouped_files})
            STRING(REGEX REPLACE ${_cur_dir}/\(.*\) \\1 _filepath ${_file})

            COMMON_CHECK_DEBUG_MSG( 
                 "1.SOURE_GROUP Relative File Path:${_filepath}"
                 ${ARGN})

            STRING(REGEX REPLACE "\(.*\)/.*" \\1 _group_name ${_filepath})

            COMMON_CHECK_DEBUG_MSG(
                "2.SOURE_GROUP Group Name:${_group_name}"
                ${ARGN})

            STRING(COMPARE EQUAL ${_filepath} ${_group_name} _CheckIfNoGroup)
            STRING(REPLACE "/" "\\" _group_name ${_group_name})
            
            if(_CheckIfNoGroup)
                source_group("Source Files" FILES ${_file})
            else()
                source_group(_${_group_name} FILES ${_file})
            endif()
        endforeach()
    endif(MSVC)
endmacro()
