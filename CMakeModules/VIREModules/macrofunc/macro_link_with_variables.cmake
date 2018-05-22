#@macro LINK_WITH_VARIABLES
#@brief 增加3方链接依赖库
#use :
  #   LINK_WITH_VARIABLES(${LIB_NAME}
  #       OSG_LIBRARY
  #       OSGEARTH_LIBRARY
  #    )
MACRO(LINK_WITH_VARIABLES TRGTNAME)
    FOREACH(varname ${ARGN})
      #message(STATUS "${${varname}_RELEASE}")
      #message(STATUS "${${varname}_DEBUG}")
      IF (WIN32)
        IF(${varname}_RELEASE)
           IF(${varname}_DEBUG)
               TARGET_LINK_LIBRARIES(${TRGTNAME} optimized "${${varname}_RELEASE}" debug "${${varname}_DEBUG}")
           ELSE(${varname}_DEBUG)
               TARGET_LINK_LIBRARIES(${TRGTNAME} optimized "${${varname}_RELEASE}" debug "${${varname}_RELEASE}" )
           ENDIF(${varname}_DEBUG)
        ELSE(${varname}_RELEASE)
           IF(${varname}_DEBUG)
               TARGET_LINK_LIBRARIES(${TRGTNAME} optimized "${${varname}}" debug "${${varname}_DEBUG}")
           ELSE(${varname}_DEBUG)
               TARGET_LINK_LIBRARIES(${TRGTNAME} optimized "${${varname}}" debug "${${varname}}" )
           ENDIF(${varname}_DEBUG)
        ENDIF(${varname}_RELEASE)
      ELSE (WIN32)
        IF(${varname}_RELEASE)
           TARGET_LINK_LIBRARIES(${TRGTNAME} "${${varname}_RELEASE}")
        ELSE(${varname}_RELEASE)
           TARGET_LINK_LIBRARIES(${TRGTNAME} "${${varname}}")
        ENDIF(${varname}_RELEASE)
      ENDIF (WIN32)
    ENDFOREACH(varname)
ENDMACRO(LINK_WITH_VARIABLES TRGTNAME)

#============================================
#@macro ADD_3RD_DEPENDENCIES
#@brief 增加3方链接依赖库名,并自动增加包含目录，不再需要单独去增加属性了
#@此宏的用法不同于LINK_WITH_VARIABLES，只需要指定名称就行，不需要再用完整的‘库变量’名称
#use 1:
    #   ADD_3RD_DEPENDENCIES(${LIB_NAME}
    #       OSG 或者 OSG_LIBRARY
    #       OSGEARTH 或者 OSGEARTH_LIBRARY
    #       ...
    #       ...
    #    )

#use 2:(暂时无用，供以后扩展处理)
    #ADDITION_LIBRARY 指定附加三方库，一般用于像OSG,OSGEARTH，等有多个库需要依赖的情况，而又不会增加引用头文件路径的情况，一般只有‘主库’一找到，头文件已经被找到了
    #eg: OSG_LIBRARY在找到的同时,OSG_INCLUDE_DIR也同时也会被找到，所以库目录只需要包含一次，其它的附加库像OSGUTIL_LIBRARY OSGDB_LIBRARY。。等库的引用头文件的目录不再需要再去被包含
    #use:
    #   ADD_3RD_DEPENDENCIES(${LIB_NAME}
    #       OSG 或者 OSG_LIBRARY
    #       OSGEARTH 或者 OSGEARTH_LIBRARY
    #       ...
    #       ....
    #       ADDITION_LIBRARY
    #       OSGDB 或者 OSGDB_LIBRARY
    #       ....
    #       ....
    #    )
#============================================
include(macro_cmake_parse_arguments)
include(macro_debug_message)
include(macro_remove_list_duplicates)
include(macro_adapter_matching_libname_includedir)

#remove the '_LIBRARY' substring
function(_resolve_has_library_postprifix _strIn _strOut)
    string(TOUPPER ${_strIn} _UpperString)
    string(FIND ${_UpperString} "_LIBRARY" _index)
    
    IF(NOT ${_index} STREQUAL "-1")
        #MESSAGE(STATUS "  --Has find '_LIBRARY' In String ${_UpperString} At Index ${_index}")
        string(REPLACE "_LIBRARY" "" _dest_string ${_UpperString})  
        set(${_strOut} ${_dest_string} PARENT_SCOPE)
    ELSE()
        set(${_strOut} ${_UpperString} PARENT_SCOPE)
    ENDIF()
endfunction()

#use to maching lib's include dir variable
#eg. DELTA3D_DTCORE_LIBRARY
#       adapter_matching_include_dir(DELTA3D_DTCORE_LIBRARY strincludedir isRightDir)
#       will get the strincludedir ${DELTA3D_INCLUDE_DIR} value,
#       isRightDir will be Ok if the ${DELTA3D_INCLUDE_DIR} dir is exist on disk
function(_adapter_matching_include_dir _lib_name _strDir _is_right_dir)
    string(TOUPPER ${_lib_name} _UpperString)
    string(FIND ${_UpperString} "_" _index)
    
    set(${_is_right_dir} FALSE PARENT_SCOPE)
    IF(NOT ${_index} STREQUAL "-1")
        #message(STATUS "  --Has find '_LIBRARY' In String ${_UpperString} At Index ${_index}")
        string(SUBSTRING ${_UpperString} 0 ${_index} headstr)  
        IF(EXISTS ${${headstr}_INCLUDE_DIR})
            #message(STATUS "  --${_UpperString} Has headstr: ${headstr}, include dir of:${${headstr}_INCLUDE_DIR}")
            set(${_strDir} ${${headstr}_INCLUDE_DIR} PARENT_SCOPE)
            set(${_is_right_dir} TRUE PARENT_SCOPE)
        ENDIF()
    ELSE()
        IF(EXISTS ${${_UpperString}_INCLUDE_DIR})
            set(${_strDir} ${${_UpperString}_INCLUDE_DIR} PARENT_SCOPE)
            set(${_is_right_dir} TRUE PARENT_SCOPE)
        ENDIF()
    ENDIF()
endfunction()

MACRO(ADD_3RD_DEPENDENCIES TRGTNAME)
    SET(options )
    SET(oneValueArgs )
    SET(multiValueArgs ADDITION_LIBRARY)
    cmake_parse_arguments(${TRGTNAME}
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    SET(_link_items_main ${${TRGTNAME}_UNPARSED_ARGUMENTS})
    SET(_link_items_addition ${${TRGTNAME}_ADDITION_LIBRARY})

    set(${TRGTNAME}_link_variables )
    set(${TRGTNAME}_include_variables )

    #mainproc
    FOREACH(varname ${_link_items_main})

        _resolve_has_library_postprifix(${varname} _dest_lib_name)
        #message(STATUS "   _dest_lib_name::${_dest_lib_name}")

        set(_is_library FALSE)
        IF(${_dest_lib_name}_LIBRARY)
            LIST(APPEND ${TRGTNAME}_link_variables ${_dest_lib_name}_LIBRARY)
            set(_is_library TRUE)
        ENDIF()

        #include resolve
        _adapter_matching_include_dir(${_dest_lib_name} _strOutDir _is_include_dir)
        if(_is_include_dir)
            LIST(APPEND ${TRGTNAME}_include_variables ${_strOutDir})
        endif()

        #is not lib and dir
        IF(NOT _is_library AND NOT _is_include_dir)
            message(WARNING "${varname} Is Not Exist!!!")
        ENDIF()     
    ENDFOREACH()

    #addition proc
    FOREACH(varname ${_link_items_addition})
        _resolve_has_library_postprifix(${varname} _dest_lib_name)
        IF(NOT ${_dest_lib_name}_LIBRARY)
          MESSAGE(WARNING "--Addition Library ${${TRGTNAME}_VAR_NAME}_LIBRARY not found, Please Check it First!!!")
        ELSE()
          LIST(APPEND ${TRGTNAME}_link_variables ${_dest_lib_name}_LIBRARY)  
        ENDIF()
    ENDFOREACH()

    remove_list_duplicates(${TRGTNAME}_link_variables)
    remove_list_duplicates(${TRGTNAME}_include_variables)

    #print
    DEBUG_MESSAGE("  -->1.${TRGTNAME} Link 3RD Party Variables:")
    FOREACH(_lib ${${TRGTNAME}_link_variables})
       DEBUG_MESSAGE("    -->: ${_lib} ")
    ENDFOREACH()

    #MESSAGE(STATUS "  -->2.${TRGTNAME} Include Directory:")
    #FOREACH(_inc ${${TRGTNAME}_include_variables})
        #MESSAGE(STATUS "    -->: ${_inc} ")
    #ENDFOREACH()
    
    #last do
    INCLUDE_DIRECTORIES(${${TRGTNAME}_include_variables})
    LINK_WITH_VARIABLES(${TRGTNAME} ${${TRGTNAME}_link_variables})
ENDMACRO(ADD_3RD_DEPENDENCIES TRGTNAME)

macro(USE_MODULE)
    
    
endmacro()