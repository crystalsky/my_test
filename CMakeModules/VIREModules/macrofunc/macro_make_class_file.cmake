# Where is this and what do we need it for?
#==============================
include(CMakePrintHelpers)
include(macro_debug_message)
include(macro_make_export_file)
#==============================
#==========================================================================
#获取Qt的父类型
MACRO(_get_Qt_parent_class_type input_type_name output_type_name)
    LIST(APPEND _Support_Qt_Parent_Class QObject QWidget QDialog)
    foreach(_type_ ${_Support_Qt_Parent_Class})
        STRING(TOUPPER ${_type_} _upper_type)
        LIST(APPEND _Upper_Support_Qt_Parent_Class ${_upper_type})
    endforeach()

    STRING(TOUPPER ${input_type_name} _upper_input_type_name)
    #DEBUG_MESSAGE("function _get_Qt_parent_class_type-->${_upper_input_type_name}")
    
    LIST(FIND _Upper_Support_Qt_Parent_Class ${_upper_input_type_name} _find_index)
    #DEBUG_MESSAGE("===Find Qt Parent Class Type Index:${_find_index}")
    
    if(_find_index EQUAL -1)
        DEBUG_MESSAGE("The Qt Parent Class Type Is One Of ${_Support_Qt_Parent_Class}, Your Param Is Invalidate, Set The Default ParentClass Name QObject")
        SET(_real_parent_class QObject)
    else()
        LIST(GET _Support_Qt_Parent_Class ${_find_index} _real_parent_class)
    endif()
    
    SET(${output_type_name}  ${_real_parent_class} )
ENDMACRO()
#==========================================================================
MACRO(__get_class_template_qt _Export O_parent_class O_Temp_H O_Temp_SRC O_IsGenUI O_UI_template)
    #NO_UI_FILE 不自动生成(*.ui),仅对QWidget QDialog类型的PARENT有效
    #PARENT Q父类(Q_CLASS为真时才有效) (QObject QWidget QDialog)
    SET(options NO_UI_FILE)
    SET(oneValueArgs PARENT)
    SET(multiValueArgs)
    cmake_parse_arguments(_Class
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    SET(_Q_DIR_ ${THIS_MODULE_TEMPLATES_PATH}/QClassFileTemplate)

    #判断父类
    if(NOT _Class_PARENT)
      SET(_Class_PARENT QObject)
    endif()
    _get_Qt_parent_class_type(${_Class_PARENT} _parent_class_name)
    DEBUG_MESSAGE("===111-Find Qt Parent Class Type Name:${_parent_class_name}")
    SET(${O_parent_class} ${_parent_class_name})
    
    SET(${O_IsGenUI} OFF)
    if(${_Export} STREQUAL "TRUE")
        #MESSAGE(STATUS "3 _Export=TRUE")
        if(${${O_parent_class}} STREQUAL "QObject")
            #MESSAGE(STATUS "4_1 ${O_parent_class}=${${O_parent_class}}")
            SET(${O_Temp_H}             ${_Q_DIR_}/Q_Class_file_export.h.in)
            SET(${O_Temp_SRC}           ${_Q_DIR_}/Q_Class_file.cpp.in)
        elseif(${${O_parent_class}} STREQUAL "QWidget" OR ${${O_parent_class}} STREQUAL "QDialog")
            #MESSAGE(STATUS "4_2 ${O_parent_class}=${${O_parent_class}}")
            if(NOT _Class_NO_UI_FILE)#要生成UI文件
                SET(${O_IsGenUI} ON)
                SET(${O_UI_template}    ${_Q_DIR_}/Q_UI_File.ui.in)
                SET(${O_Temp_H}         ${_Q_DIR_}/Q_UI_File_export.h.in)
                SET(${O_Temp_SRC}       ${_Q_DIR_}/Q_UI_File.cpp.in)
            else()#不用生成UI文件
                SET(${O_Temp_H}         ${_Q_DIR_}/Q_No_UI_export.h.in)
                SET(${O_Temp_SRC}       ${_Q_DIR_}/Q_No_UI.cpp.in)
            endif() 
        else()
            MESSAGE(FATAL_ERROR "No Template File Support Your Require!")
        endif()
    else()#非导出文件
        #MESSAGE(STATUS "3 _Export=FALSE")
      #继承于QObject
        if(${${O_parent_class}} STREQUAL "QObject")
            SET(${O_Temp_H}             ${_Q_DIR_}/Q_Class_file.h.in)
            SET(${O_Temp_SRC}           ${_Q_DIR_}/Q_Class_file.cpp.in)
        #继承于QWidget/QDialog
        elseif(${${O_parent_class}} STREQUAL "QWidget" OR ${${O_parent_class}} STREQUAL "QDialog")
            if(NOT _Class_NO_UI_FILE)#要生成UI文件
                SET(${O_IsGenUI} ON)
                SET(${O_UI_template}    ${_Q_DIR_}/Q_UI_File.ui.in)
                SET(${O_Temp_H}         ${_Q_DIR_}/Q_UI_File.h.in)
                SET(${O_Temp_SRC}       ${_Q_DIR_}/Q_UI_File.cpp.in)
            else()#不用生成UI文件
                SET(${O_Temp_H}         ${_Q_DIR_}/Q_No_UI.h.in)
                SET(${O_Temp_SRC}       ${_Q_DIR_}/Q_No_UI.cpp.in)
            endif() 
        else()
            MESSAGE(FATAL_ERROR "No Template File Support Your Require!")
        endif()
    endif()
ENDMACRO()
#==========================================================================
MACRO(__get_class_template _Export O_Temp_H O_Temp_SRC)
    
    SET(_DIR_ ${THIS_MODULE_TEMPLATES_PATH}/ClassFileTemplate)

    SET(_H_EXPORT   ${_DIR_}/Class_file_export.h.in)
    SET(_H          ${_DIR_}/Class_file.h.in)
    SET(_SRC        ${_DIR_}/Class_file.cpp.in)

    if(${_Export} STREQUAL "TRUE")
        #MESSAGE(STATUS "TRUE")
        SET(${O_Temp_H}         ${_H_EXPORT})
        SET(${O_Temp_SRC}       ${_SRC})
    else()
        #MESSAGE(STATUS "FALSE")
      #继承于QObject
        SET(${O_Temp_H}         ${_H})
        SET(${O_Temp_SRC}       ${_SRC})
    endif()
ENDMACRO()
#==========================================================================
#判断获取配置信息 
MACRO(__dertermine_the_make_class_params2 parent_class_name h_template_file src_template_file is_gen_ui ui_template_file)
  #EXPORT 是否是导出类头文件
  #Q_CLASS 是否是Qt类
  #NO_UI_FILE 不自动生成(*.ui),仅对QWidget QDialog类型的PARENT有效
  #HEADER_PATH 头文件的目录
  #PARENT Q父类(Q_CLASS为真时才有效) (QObject QWidget QDialog)
  #SUB_DIR_NAME 工程下子目录名称
  SET(options EXPORT Q_CLASS NO_UI_FILE)
  SET(oneValueArgs HEADER_DIR_PATH SUB_DIR_NAME PARENT)
  SET(multiValueArgs)
  cmake_parse_arguments(_Class
      "${options}" 
      "${oneValueArgs}" 
      "${multiValueArgs}" 
      ${ARGN}) 
    
  #判断获取各种类型的配置文件 
  #若是Qt类
    if(_Class_Q_CLASS)
        #判断父类
        __get_class_template_qt(
            ${_Class_EXPORT}
            ${parent_class_name}
            ${h_template_file}
            ${src_template_file}
            ${is_gen_ui}
            ${ui_template_file}
            ${ARGN}
        )
    else(_Class_Q_CLASS)
        __get_class_template(
            ${_Class_EXPORT} 
            ${h_template_file}
            ${src_template_file}
        )
    endif(_Class_Q_CLASS)

    IF(NOT EXISTS ${${h_template_file}})
        MESSAGE(FATAL_ERROR "Not Exsit File: ${${h_template_file}}")
    ENDIF()

    IF(NOT EXISTS ${${h_template_file}})
        MESSAGE(FATAL_ERROR "Not Exsit File: ${${h_template_file}}")
    ENDIF()

    IF(${is_gen_ui} STREQUAL "ON")
        IF(NOT EXISTS ${${ui_template_file}})
            MESSAGE(FATAL_ERROR "Not Exsit File UI: ${${ui_template_file}}")
        ENDIF()
    ENDIF()
ENDMACRO(__dertermine_the_make_class_params2)
#==========================================================================
function(_make_class_file_1 _lib_name)
    SET(LIBRARY_NAME ${_lib_name})

    #EXPORT 是否是导出类头文件
    #Q_CLASS 是否是Qt类
    #NO_UI_FILE 不自动生成(*.ui),仅对QWidget QDialog类型的PARENT有效
    #HEADER_PATH 头文件的目录
    #PARENT Q父类(Q_CLASS为真时才有效) (QObject QWidget QDialog)
    #SUB_DIR_NAME 工程下子目录名称
    SET(options EXPORT Q_CLASS NO_UI_FILE)
    SET(oneValueArgs HEADER_DIR_PATH SUB_DIR_NAME PARENT)
    SET(multiValueArgs)
    cmake_parse_arguments(${LIBRARY_NAME} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    set(_will_generate_class_files ${${LIBRARY_NAME}_UNPARSED_ARGUMENTS})

    list(LENGTH _will_generate_class_files _classlistCount)
    if(NOT ${_classlistCount} GREATER 0)
        #MESSAGE(STATUS "No Generate Class Defined In Macro Parameters....Returned!!")
        return()
    endif()
            
    if(NOT ${LIBRARY_NAME}_HEADER_DIR_PATH)
        SET(${LIBRARY_NAME}_HEADER_DIR_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    endif()
    if(${LIBRARY_NAME}_SUB_DIR_NAME)
        STRING(CONCAT ${LIBRARY_NAME}_HEADER_DIR_PATH ${${LIBRARY_NAME}_HEADER_DIR_PATH} "/" ${${LIBRARY_NAME}_SUB_DIR_NAME})
    endif()
    #MESSAGE(STATUS "HeaderFileDir: ${${LIBRARY_NAME}_HEADER_DIR_PATH}")
    
    #判断是否是导出库并且不是子文件夹创建导出文件
    if(${LIBRARY_NAME}_EXPORT AND NOT ${LIBRARY_NAME}_SUB_DIR_NAME)
        #导出头导出定义头文件
        MAKE_EXPORT_FILE(${LIBRARY_NAME} ${${LIBRARY_NAME}_HEADER_DIR_PATH})
        #SET(${LIBRARY_NAME}_EXPORT_FILE "${${LIBRARY_NAME}_HEADER_DIR_PATH}/${LIBRARY_NAME}_Export.h")
        #SET(_EXPORT_HDR_TEMP "${THIS_MODULE_TEMPLATES_PATH}/export_file.h.in")
        #IF(NOT EXISTS ${${LIBRARY_NAME}_EXPORT_FILE})
            #MESSAGE(STATUS "...Ready make file:-->${_EXPORT_HDR_TEMP}-->
                        #${${LIBRARY_NAME}_EXPORT_FILE}")
            #CONFIGURE_FILE(${_EXPORT_HDR_TEMP} ${${LIBRARY_NAME}_EXPORT_FILE})
        #ENDIF()
    endif()
    
    #判断获取配置信息 
    __dertermine_the_make_class_params2(Parent_Class 
        H_Template_File 
        SRC_Template_File 
        Is_Gen_UI 
        UI_Template_File 
        ${ARGN}
    )

    DEBUG_MESSAGE("Is_Gen_UI--: ${Is_Gen_UI}")
    DEBUG_MESSAGE("Begin Make Class Files: ${${LIBRARY_NAME}_UNPARSED_ARGUMENTS}")

    foreach(_class_file_name ${${LIBRARY_NAME}_UNPARSED_ARGUMENTS})
        SET(Class_File_Name ${_class_file_name})
        
        IF(${LIBRARY_NAME}_Q_CLASS)
            #生成*.ui文件
            IF(Is_Gen_UI)
                SET(_ui_path "${CMAKE_CURRENT_SOURCE_DIR}/${_class_file_name}.ui")
                IF(${LIBRARY_NAME}_SUB_DIR_NAME)
                    SET(_ui_path    "${CMAKE_CURRENT_SOURCE_DIR}/${${LIBRARY_NAME}_SUB_DIR_NAME}/${_class_file_name}.ui")
                ENDIF()
                IF(NOT EXISTS ${_ui_path})
                    MESSAGE(STATUS "    ...Ready make file:
        ${UI_Template_File}-->
            ${_ui_path}")
                    CONFIGURE_FILE(${UI_Template_File} ${_ui_path})
                ENDIF()
            ENDIF()
        ENDIF(${LIBRARY_NAME}_Q_CLASS)
        
        #生成目标文件
        #header file
        SET(${LIBRARY_NAME}_CLASS_FILE_HEADER_PATH  "${${LIBRARY_NAME}_HEADER_DIR_PATH}/${_class_file_name}.h")
        
        SET(HEADER_R_DIR_AND_FILE_NAME ${_class_file_name})
        GET_FILENAME_COMPONENT(PARENT_DIR ${${LIBRARY_NAME}_HEADER_DIR_PATH} PATH)
        IF(NOT ${PARENT_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
            IF(${LIBRARY_NAME}_SUB_DIR_NAME)
                STRING(CONCAT HEADER_R_DIR_AND_FILE_NAME ${${LIBRARY_NAME}_SUB_DIR_NAME} "/" ${_class_file_name})
            ENDIF()
        ENDIF()
        
        IF(NOT EXISTS ${${LIBRARY_NAME}_CLASS_FILE_HEADER_PATH})
            MESSAGE(STATUS "    ...Ready make file:
        ${H_Template_File}-->
        ${${LIBRARY_NAME}_CLASS_FILE_HEADER_PATH}")
            CONFIGURE_FILE(${H_Template_File} ${${LIBRARY_NAME}_CLASS_FILE_HEADER_PATH})
        ENDIF()
        
        #src file
        SET(${LIBRARY_NAME}_CLASS_FILE_SRC_PATH     "${CMAKE_CURRENT_SOURCE_DIR}/${_class_file_name}.cpp")
        IF(${LIBRARY_NAME}_SUB_DIR_NAME)
            SET(${LIBRARY_NAME}_CLASS_FILE_SRC_PATH     "${CMAKE_CURRENT_SOURCE_DIR}/${${LIBRARY_NAME}_SUB_DIR_NAME}/${_class_file_name}.cpp")
        ENDIF()
        IF(NOT EXISTS ${${LIBRARY_NAME}_CLASS_FILE_SRC_PATH})
            MESSAGE(STATUS "    ...Ready make file:
        ${SRC_Template_File}-->
        ${${LIBRARY_NAME}_CLASS_FILE_SRC_PATH}")
            CONFIGURE_FILE(${SRC_Template_File} ${${LIBRARY_NAME}_CLASS_FILE_SRC_PATH})
        ENDIF()
    endforeach()
endfunction(_make_class_file_1 _lib_name)

function(_make_class_file_core _lib_name)
    SET(LIBRARY_NAME ${_lib_name})

    #EXPORT 是否是导出类头文件
    #Q_CLASS 是否是Qt类
    #NO_UI_FILE 不自动生成(*.ui),仅对QWidget QDialog类型的PARENT有效
    #HEADER_PATH 头文件的目录
    #PARENT Q父类(Q_CLASS为真时才有效) (QObject QWidget QDialog)
    #TO_PATH 强行输出目录，所有的文件都会输出到目录，
    SET(options EXPORT Q_CLASS NO_UI_FILE)
    SET(oneValueArgs HEADER_DIR_PATH PARENT TO_PATH)
    SET(multiValueArgs)
    cmake_parse_arguments(${LIBRARY_NAME} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    set(_will_generate_class_files ${${LIBRARY_NAME}_UNPARSED_ARGUMENTS})

    list(LENGTH _will_generate_class_files _classlistCount)
    if(NOT ${_classlistCount} GREATER 0)
        #MESSAGE(STATUS "No Generate Class Defined In Macro Parameters....Returned!!")
        return()
    endif()

    #设置文件输出目录
    set(_gen_file_output_path ${${LIBRARY_NAME}_TO_PATH})
    if(NOT ${LIBRARY_NAME}_TO_PATH)
        set(_gen_file_output_path ${CMAKE_CURRENT_SOURCE_DIR})
    endif()
            
    if(NOT ${LIBRARY_NAME}_HEADER_DIR_PATH)
        SET(${LIBRARY_NAME}_HEADER_DIR_PATH ${_gen_file_output_path})
    endif()
    #MESSAGE(STATUS "HeaderFileDir: ${${LIBRARY_NAME}_HEADER_DIR_PATH}")
    
    #判断是否是导出库并且不是子文件夹创建导出文件
    if(${LIBRARY_NAME}_EXPORT)
        #导出头导出定义头文件
        MAKE_EXPORT_FILE(${LIBRARY_NAME} ${${LIBRARY_NAME}_HEADER_DIR_PATH})
        #SET(${LIBRARY_NAME}_EXPORT_FILE "${${LIBRARY_NAME}_HEADER_DIR_PATH}/${LIBRARY_NAME}_Export.h")
        #SET(_EXPORT_HDR_TEMP "${THIS_MODULE_TEMPLATES_PATH}/export_file.h.in")
        #IF(NOT EXISTS ${${LIBRARY_NAME}_EXPORT_FILE})
            #MESSAGE(STATUS "...Ready make file:-->${_EXPORT_HDR_TEMP}-->
                        #${${LIBRARY_NAME}_EXPORT_FILE}")
            #CONFIGURE_FILE(${_EXPORT_HDR_TEMP} ${${LIBRARY_NAME}_EXPORT_FILE})
        #ENDIF()
    endif()
    
    #判断获取配置信息 
    __dertermine_the_make_class_params2(Parent_Class 
        H_Template_File 
        SRC_Template_File 
        Is_Gen_UI 
        UI_Template_File 
        ${ARGN}
    )

    DEBUG_MESSAGE("Is_Gen_UI--: ${Is_Gen_UI}")
    DEBUG_MESSAGE("Begin Make Class Files: ${${LIBRARY_NAME}_UNPARSED_ARGUMENTS}")

    foreach(_class_file_name ${${LIBRARY_NAME}_UNPARSED_ARGUMENTS})
        SET(Class_File_Name ${_class_file_name})
        
        IF(${LIBRARY_NAME}_Q_CLASS)
            #生成*.ui文件
            IF(Is_Gen_UI)
                SET(_ui_path "${_gen_file_output_path}/${_class_file_name}.ui")
                IF(NOT EXISTS ${_ui_path})
                    MESSAGE(STATUS "    ...Ready make file:
        ${UI_Template_File}-->
            ${_ui_path}")
                    CONFIGURE_FILE(${UI_Template_File} ${_ui_path})
                ENDIF()
            ENDIF()
        ENDIF()
        
        #生成目标文件
        #header file
        SET(${LIBRARY_NAME}_CLASS_FILE_HEADER_PATH  "${${LIBRARY_NAME}_HEADER_DIR_PATH}/${_class_file_name}.h")

        #GET_FILENAME_COMPONENT(PARENT_DIR ${${LIBRARY_NAME}_HEADER_DIR_PATH} PATH)
        
        IF(NOT EXISTS ${${LIBRARY_NAME}_CLASS_FILE_HEADER_PATH})
            MESSAGE(STATUS "    ...Ready make file:
        ${H_Template_File}-->
        ${${LIBRARY_NAME}_CLASS_FILE_HEADER_PATH}")
            CONFIGURE_FILE(${H_Template_File} ${${LIBRARY_NAME}_CLASS_FILE_HEADER_PATH})
        ENDIF()
        
        #src file
        SET(${LIBRARY_NAME}_CLASS_FILE_SRC_PATH     "${_gen_file_output_path}/${_class_file_name}.cpp")
        IF(NOT EXISTS ${${LIBRARY_NAME}_CLASS_FILE_SRC_PATH})
            MESSAGE(STATUS "    ...Ready make file:
        ${SRC_Template_File}-->
        ${${LIBRARY_NAME}_CLASS_FILE_SRC_PATH}")
            CONFIGURE_FILE(${SRC_Template_File} ${${LIBRARY_NAME}_CLASS_FILE_SRC_PATH})
        ENDIF()
    endforeach()
endfunction(_make_class_file_core _lib_name)

function(MAKE_CLASS_FILES _lib_name)
    SET(LIBRARY_NAME ${_lib_name})
    #SUB_DIR_NAME 工程下子目录名称

    SET(options)
    SET(oneValueArgs SUB_DIR_NAME TO_PATH)
    SET(multiValueArgs)
    cmake_parse_arguments(${LIBRARY_NAME} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})
               
    #处理子目录，与原来的宏适配
    set(_to_path_dir ${CMAKE_CURRENT_LIST_DIR})
    if(${LIBRARY_NAME}_SUB_DIR_NAME AND NOT ${LIBRARY_NAME}_TO_PATH)
        STRING(CONCAT _to_path_dir ${_to_path_dir} "/" ${${LIBRARY_NAME}_SUB_DIR_NAME})
        _make_class_file_core(${_lib_name} ${${LIBRARY_NAME}_UNPARSED_ARGUMENTS} TO_PATH ${_to_path_dir})
    else()
        _make_class_file_core(${_lib_name} ${ARGN})
    endif()
endfunction()
#==========================================================================
#===================================特殊封装===========================
#产生QObject子类文件
MACRO(MAKE_CLASS_WITH_QOBJECT _lib_name)
    MAKE_CLASS_FILES(${_lib_name} Q_CLASS PARENT QObject ${ARGN})
ENDMACRO()

#产生带导出标志的QObject子类文件
MACRO(MAKE_EXPORT_CLASS_WITH_QOBJECT _lib_name _export_header_dir)
  MAKE_CLASS_FILES(${_lib_name} 
    EXPORT
    Q_CLASS 
    PARENT QObject 
    HEADER_DIR_PATH ${_export_header_dir}
    ${ARGN})
ENDMACRO()

#========================================================
#产生有UI文件QWidget子类文件
MACRO(MAKE_CLASS_WITH_UI_WIDGET _lib_name)
    MAKE_CLASS_FILES(
        ${_lib_name} 
        Q_CLASS 
        PARENT QWidget 
        ${ARGN}
    )
ENDMACRO()

#产生没有UI文件QWidget子类文件
MACRO(MAKE_CLASS_WIDGET _lib_name)
    MAKE_CLASS_FILES(
        ${_lib_name} 
        Q_CLASS 
        NO_UI_FILE 
        PARENT QWidget 
        ${ARGN}
    )
ENDMACRO()

#产生有UI文件QWidget子类导出文件
MACRO(MAKE_EXPORT_CLASS_WITH_UI_WIDGET _lib_name _export_header_dir)
  MAKE_CLASS_FILES(${_lib_name} 
    EXPORT
    Q_CLASS 
    PARENT QWidget 
    HEADER_DIR_PATH ${_export_header_dir}
    ${ARGN})
ENDMACRO()

#产生没有UI文件QWidget子类导出文件
MACRO(MAKE_EXPORT_CLASS_WIDGET _lib_name _export_header_dir)
  MAKE_CLASS_FILES(${_lib_name} 
    EXPORT
    Q_CLASS 
    NO_UI_FILE
    PARENT QWidget 
    HEADER_DIR_PATH ${_export_header_dir}
    ${ARGN})
ENDMACRO()
#========================================================
#产生有UI文件QDialog子类文件
MACRO(MAKE_CLASS_WITH_UI_DIALOG _lib_name)
    MAKE_CLASS_FILES(
        ${_lib_name} 
        Q_CLASS 
        PARENT QDialog 
        ${ARGN}
    )
ENDMACRO()

#产生有QDialog子类文件
MACRO(MAKE_CLASS_DIALOG _lib_name)
    MAKE_CLASS_FILES(
        ${_lib_name} 
        Q_CLASS 
        NO_UI_FILE
        PARENT QDialog 
        ${ARGN}
    )
ENDMACRO()

#产生有UI文件QDialog子类导出文件
MACRO(MAKE_EXPORT_CLASS_WITH_UI_DIALOG _lib_name _export_header_dir)
  MAKE_CLASS_FILES(${_lib_name} 
    EXPORT
    Q_CLASS 
    PARENT QDialog 
    HEADER_DIR_PATH ${_export_header_dir}
    ${ARGN})
ENDMACRO()

#产生有UI文件QDialog子类导出文件
MACRO(MAKE_EXPORT_CLASS_DIALOG _lib_name _export_header_dir)
  MAKE_CLASS_FILES(${_lib_name} 
    EXPORT
    Q_CLASS 
    NO_UI_FILE
    PARENT QDialog 
    HEADER_DIR_PATH ${_export_header_dir}
    ${ARGN})
ENDMACRO()
#========================================================
#产生普通类文件
MACRO(MAKE_CLASS _lib_name)
    MAKE_CLASS_FILES(${_lib_name} ${ARGN})
ENDMACRO()

MACRO(MAKE_EXPORT_CLASS _lib_name _export_header_dir)
  MAKE_CLASS_FILES(${_lib_name}
    EXPORT 
    HEADER_DIR_PATH ${_export_header_dir}
    ${ARGN})
ENDMACRO()



#==============================================================================================
#此函数用于产生指定模板类文件的处理
#==============================================================================================
function(MAKE_CLASS_FILES_BY_TEMPLATE_FILE _lib_name _h_template _src_template)
    SET(LIBRARY_NAME ${_lib_name})

    SET(options )
    SET(oneValueArgs SUB_DIR_NAME)
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

    SET(_DIR_ ${THIS_MODULE_TEMPLATES_PATH}/ClassFileTemplate)

    SET(${LIBRARY_NAME}_H_TEMPLATE ${_h_template})
    IF(NOT EXISTS ${_h_template})
        SET(${LIBRARY_NAME}_H_TEMPLATE ${_DIR_}/Class_file.h.in)
    ENDIF()

    SET(${LIBRARY_NAME}_SRC_TEMPLATE ${_src_template})
    IF(NOT EXISTS ${_src_template})
        SET(${LIBRARY_NAME}_SRC_TEMPLATE ${_DIR_}/Class_file.cpp.in)
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
#===============================================================================================