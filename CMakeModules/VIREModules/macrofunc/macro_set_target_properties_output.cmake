#====================================================
#运行时目标属性设置
#设置输出文件名
#设置输出目录
#扩展子目录属性 SUBDIR "xxx_drectory"(此条属性可有可无)
#eg.
#   SET_TARGET_PROPERTIES_OUTPUT(${_Target} "${PROJECT_SOURCE_DIR}/bin")
#   生成的目录库或程序在目录 
#       debug:  ${PROJECT_SOURCE_DIR}/bin/debug 
#       release:${PROJECT_SOURCE_DIR}/bin/release

#   SET_TARGET_PROPERTIES_OUTPUT(${_Target} "${PROJECT_SOURCE_DIR}/bin" SUBDIR "dir1/dir2")
#   生成的目录库或程序在目录 
#       debug:  ${PROJECT_SOURCE_DIR}/bin/debug/dir1/dir2 
MACRO(SET_TARGET_PROPERTIES_OUTPUT _Target _directory)
    SET(options TO_BIN_DIR TO_SAME_DIR)#TO_BIN_DIR:The variable decide the output dir same in ${_directory}
    SET(oneValueArgs SUBDIR)
    SET(multiValueArgs)
    
    cmake_parse_arguments(${_Target} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    COMMON_CHECK_DEBUG_MSG("Args SET_TARGET_PROPERTIES_OUTPUT:" ${ARGN} PRINT_ARGN)

    #MESSAGE(WARNING "CMAKE_ARCHIVE_OUTPUT_DIRECTORY=${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")    
    #MESSAGE(WARNING "CMAKE_RUNTIME_OUTPUT_DIRECTORY=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

    foreach(config DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)
        string(TOLOWER ${config} conDir)
        
        #======================Archive_Dir=====================
        SET(${_Target}_ARCHIVE_DIR_${config} "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${conDir}")
        #MESSAGE(FATAL_ERROR "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
        IF(CMAKE_CL_64)
            STRING(CONCAT ${_Target}_ARCHIVE_DIR_${config} ${${_Target}_ARCHIVE_DIR_${config}} "x64") 
        ENDIF()
        SET_TARGET_PROPERTIES(${_Target} PROPERTIES 
            ARCHIVE_OUTPUT_DIRECTORY_${config}
            ${${_Target}_ARCHIVE_DIR_${config}}
        ) 

        #======================Runtime Dir=====================
        SET(${_Target}_RUNTIME_DIR_${config} "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${conDir}")
        IF(CMAKE_CL_64)
            STRING(CONCAT ${_Target}_RUNTIME_DIR_${config} ${${_Target}_RUNTIME_DIR_${config}} "x64")
        ENDIF()

        if(${_Target}_SUBDIR)
            STRING(CONCAT ${_Target}_RUNTIME_DIR_${config} ${${_Target}_RUNTIME_DIR_${config}} "/" ${${_Target}_SUBDIR})
        endif()

        SET_TARGET_PROPERTIES(${_Target} PROPERTIES 
            RUNTIME_OUTPUT_DIRECTORY_${config} 
            ${${_Target}_RUNTIME_DIR_${config}}
        )
    endforeach()

    # SET_TARGET_PROPERTIES( ${_Target} PROPERTIES 
    #     RUNTIME_OUTPUT_DIRECTORY  
    #     "${_directory}" )
    COMMON_CHECK_DEBUG(debug_mode ${ARGN})
    IF(debug_mode)
        CMAKE_PRINT_PROPERTIES(TARGETS ${_Target} 
                    PROPERTIES 
                    RUNTIME_OUTPUT_DIRECTORY 
                    RUNTIME_OUTPUT_DIRECTORY_DEBUG 
                    RUNTIME_OUTPUT_DIRECTORY_RELEASE
                    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO
                    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL
            )
    ENDIF()
ENDMACRO()

MACRO(SET_TARGET_PROPERTIES_LIB_DEBUG_RELEASE _Target)
    SET_TARGET_PROPERTIES_OUTPUT(${_Target} 
        "${PROJECT_SOURCE_DIR}/bin"
    )
ENDMACRO()

MACRO(SET_TARGET_PROPERTIES_OUT_PUT_TO_BIN_DIR _Target)
    SET_TARGET_PROPERTIES_OUTPUT(${_Target} 
        "${PROJECT_SOURCE_DIR}/bin"
        TO_BIN_DIR
    )
ENDMACRO()