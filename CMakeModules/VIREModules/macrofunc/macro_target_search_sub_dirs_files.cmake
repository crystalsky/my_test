#TARGET_SERACH_SUB_DIRS_FILES
#此宏主要是查找子目录，将查找到的头文件、源文件、UI文件、QRC文件分别依附到“处理树上”，并将以在公程中以子目录分类显示
#
MACRO(TARGET_SERACH_SUB_DIRS_FILES _target_name)
    #EXPORT 是否是导出类头文件
    #HEADER_PATH 头文件的目录
    #SUB_DIR_NAME 工程下子目录名称
    SET(options EXPORT)
    SET(oneValueArgs HEADER_DIR_PATH)
    SET(multiValueArgs SUB_DIRS)
    cmake_parse_arguments(${_target_name} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})
            
    if(NOT ${_target_name}_HEADER_DIR_PATH)
        SET(${_target_name}_HEADER_DIR_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    endif()
    
    SET(${_target_name}_SUB_DIRS ${${_target_name}_SUB_DIRS} ${${_target_name}_UNPARSED_ARGUMENTS})
    
    DEBUG_MESSAGE("MACRO TARGET_SERACH_SUB_DIRS_FILES:->${_target_name}<->${${_target_name}_SUB_DIRS}")
    
    SET(${_target_name}_ALL_SUB_DIR_INC ${${_target_name}_HEADER_DIR_PATH})
    
    SET(${_target_name}_ALL_SUB_DIR_HDR )
    SET(${_target_name}_ALL_SUB_DIR_SRCS )
    SET(${_target_name}_ALL_SUB_DIR_UIS )
    SET(${_target_name}_ALL_SUB_DIR_RCS )

    FOREACH(_dir_name ${${_target_name}_SUB_DIRS} ) 
        #FIND Files In SubDir
        STRING(CONCAT ${_target_name}_HEADER_DIR_SUB_PATH ${${_target_name}_HEADER_DIR_PATH} "/" ${_dir_name})
        STRING(CONCAT ${_target_name}_SRC_DIR_SUB_PATH ${CMAKE_CURRENT_SOURCE_DIR} "/" ${_dir_name})
        
        GET_FILENAME_COMPONENT(PARENT_DIR ${${_target_name}_HEADER_DIR_SUB_PATH} PATH)
        IF(NOT ${PARENT_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
            SET(${_target_name}_ALL_SUB_DIR_INC ${${_target_name}_ALL_SUB_DIR_INC} ${${_target_name}_HEADER_DIR_SUB_PATH})
            INCLUDE_DIRECTORIES(${${_target_name}_HEADER_DIR_SUB_PATH})
        ENDIF()
        
        FILE(GLOB ${_target_name}_TEMP_SOURCES_HDR 
      "${${_target_name}_HEADER_DIR_SUB_PATH}/*.h" 
      "${${_target_name}_HEADER_DIR_SUB_PATH}/*.inl" 
      "${${_target_name}_HEADER_DIR_SUB_PATH}/*.hpp")
        
    FILE(GLOB ${_target_name}_TEMP_SOURCES_SRC 
      "${${_target_name}_SRC_DIR_SUB_PATH}/*.h" 
      "${${_target_name}_SRC_DIR_SUB_PATH}/*.cpp" 
      "${${_target_name}_SRC_DIR_SUB_PATH}/*.cc")

        FILE(GLOB ${_target_name}_TEMP_UIS 
      "${${_target_name}_SRC_DIR_SUB_PATH}/*.ui")

        FILE(GLOB ${_target_name}_TEMP_RCS 
      "${${_target_name}_SRC_DIR_SUB_PATH}/*.qrc")
        
        #Set The Param Val
        SET(${_target_name}_ALL_SUB_DIR_HDR 
      ${${_target_name}_ALL_SUB_DIR_HDR} 
      ${${_target_name}_TEMP_SOURCES_HDR})
        
    SET(${_target_name}_ALL_SUB_DIR_SRCS 
      ${${_target_name}_ALL_SUB_DIR_SRCS} 
      ${${_target_name}_TEMP_SOURCES_HDR} 
      ${${_target_name}_TEMP_SOURCES_SRC}) 
        
    SET(${_target_name}_ALL_SUB_DIR_UIS 
      ${${_target_name}_ALL_SUB_DIR_UIS} 
      ${${_target_name}_TEMP_UIS}) 
        
    SET(${_target_name}_ALL_SUB_DIR_RCS 
      ${${_target_name}_ALL_SUB_DIR_RCS} 
      ${${_target_name}_TEMP_RCS}) 
        
        #File Groups
        SOURCE_GROUP( "_${_dir_name}" FILES 
          ${${_target_name}_TEMP_SOURCES_HDR} 
          ${${_target_name}_TEMP_SOURCES_SRC}
          ${${_target_name}_TEMP_UIS}
          ${${_target_name}_TEMP_RCS}
        )
    ENDFOREACH()
    
    DEBUG_MESSAGE("   ${_target_name}_ALL_SUB_DIR_SRCS:${${_target_name}_ALL_SUB_DIR_SRCS}")
    DEBUG_MESSAGE("   ${_target_name}_ALL_SUB_DIR_UIS:${${_target_name}_ALL_SUB_DIR_UIS}")
    DEBUG_MESSAGE("   ${_target_name}_ALL_SUB_DIR_RCS:${${_target_name}_ALL_SUB_DIR_RCS}")
    
    SET(${_target_name}_HEADERS 
    ${${_target_name}_HEADERS} 
    ${${_target_name}_ALL_SUB_DIR_HDR})

    SET(${_target_name}_SRCS 
    ${${_target_name}_SRCS} 
    ${${_target_name}_ALL_SUB_DIR_SRCS})

    SET(${_target_name}_QT_UIS 
    ${${_target_name}_QT_UIS} 
    ${${_target_name}_ALL_SUB_DIR_UIS})
  
    SET(${_target_name}_QT_RCS 
    ${${_target_name}_QT_RCS} 
    ${${_target_name}_ALL_SUB_DIR_RCS})
    
ENDMACRO(TARGET_SERACH_SUB_DIRS_FILES _target_name)