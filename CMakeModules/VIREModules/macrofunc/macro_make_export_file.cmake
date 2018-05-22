#产生库的导出头文件
MACRO(MAKE_EXPORT_FILE _lib_name _file_dir)

    IF(NOT EXISTS ${_file_dir})
        MESSAGE(STATUS "...Invalide Dir Path, Auto MakeDirecotry Of ${_file_dir}")
        FILE(MAKE_DIRECTORY ${_file_dir})
    ENDIF()

    SET(LIBRARY_NAME ${_lib_name})

    #MESSAGE(STATUS  "..........${${_lib_name}_USE_STATIC_LIBRARY}")
    SET(USE_STATIC_LIBRARY FALSE)
    if(${_lib_name}_USE_STATIC_LIBRARY)
        #IF(${${_lib_name}_USE_STATIC_LIBRARY})
            SET(USE_STATIC_LIBRARY TRUE)
        #ENDIF()
    ENDIF()

    SET(_EXPORT_FILE "${_file_dir}/${_lib_name}_Export.h")
    SET(_EXPORT_TEMP "${THIS_MODULE_TEMPLATES_PATH}/export_file.h.in")
    
    IF(NOT EXISTS ${_EXPORT_FILE})
        MESSAGE(STATUS "...Ready make file:-->${_EXPORT_TEMP}-->
                    ${_EXPORT_FILE}")
        
        CONFIGURE_FILE(${_EXPORT_TEMP} ${_EXPORT_FILE})
    ENDIF()

    #read the file replace the text condition by matched string....
    if(USE_STATIC_LIBRARY)
        MESSAGE(STATUS "${_lib_name} USE_STATIC_LIBRARY")
        FILE(READ ${_EXPORT_FILE} fileData)

        IF(${fileData} MATCHES "(#define)([ ]+)(USE_STATIC_LIBRARY)")
            STRING(REGEX REPLACE "(#define)([ ]+)(USE_STATIC_LIBRARY)"
                "\\1\\2${_lib_name}_LIBRARY_STATIC" _replaced
                ${fileData})
            MESSAGE(STATUS "After Replace: ${_replaced}")

            FILE(WRITE ${_EXPORT_FILE} ${_replaced})
        ELSEIF(${fileData} MATCHES "(/\\*[ ]+#undef.*\\*/)")
            STRING(REGEX REPLACE "(/\\*[ ]+#undef.*\\*/)"
                "#define ${_lib_name}_LIBRARY_STATIC" _replaced
                ${fileData})
            MESSAGE(STATUS "After Replace: ${_replaced}")

            FILE(WRITE ${_EXPORT_FILE} ${_replaced})
        ENDIF()
    ELSE()
        #read current export file and find the define string,
        #if find the xxx_LIBRARY_STATIC,
        #it should be restore the default....
        IF(EXISTS ${_EXPORT_FILE})
            FILE(READ ${_EXPORT_FILE} fileData)
            IF(${fileData} MATCHES "(#define)([ ]+)(${_lib_name}_LIBRARY_STATIC)")
                CONFIGURE_FILE(${_EXPORT_TEMP} ${_EXPORT_FILE})
            ENDIF()
        ENDIF()
    ENDIF()
ENDMACRO()