function(MAKE_CLASS_TEMP_CLASS_TEST_WIDGET _lib_name)
    MAKE_CLASS_FILES_BY_TEMPLATE_FILE(
        ${_lib_name} 
        ${CMAKE_CURRENT_LIST_DIR}/Base/class_temp_widget_base.h.in
        ${CMAKE_CURRENT_LIST_DIR}/Base/class_temp_widget_base.cpp.in
        ${ARGN}
        )
endfunction()

function(MAKE_BUTTONFUNCTIONWIDGTH_SUB_CLASS_FILE _lib_name)
    MAKE_CLASS_FILES_BY_TEMPLATE_FILE(
        ${_lib_name} 
        ${CMAKE_CURRENT_LIST_DIR}/Base/class_temp_QtUICButtonFunctionWidget.h.in
        ${CMAKE_CURRENT_LIST_DIR}/Base/class_temp_QtUICButtonFunctionWidget.cpp.in
        ${ARGN}
        )
endfunction()

#=======================================================================
#=======================================================================
#用于产生一个带有左边是按钮列，右边是一个StackWidget的类模板
function(MAKE_STEPBASE_SUB_CLASS_FILE _lib_name)
    MAKE_CLASS_FILES_BY_TEMPLATE_FILE(
        ${_lib_name} 
        ${CMAKE_CURRENT_LIST_DIR}/Base/class_temp_stepBase.h.in
        ${CMAKE_CURRENT_LIST_DIR}/Base/class_temp_stepBase.cpp.in
        ${ARGN}
        )
endfunction()
#=======================================================================
#用于产生一个带有反射处理的按钮对话框,按扭的点击具有反射处理的基处理
function(MAKE_REFLECT_BUTTONFUNCTIONWIDGET_SUB_CLASS_FILE _lib_name)
    MAKE_CLASS_FILES_BY_TEMPLATE_FILE(
        ${_lib_name} 
        ${CMAKE_CURRENT_LIST_DIR}/Base/class_temp_reflectButtonFunctionWidget.h.in
        ${CMAKE_CURRENT_LIST_DIR}/Base/class_temp_reflectButtonFunctionWidget.cpp.in
        ${ARGN}
        )
endfunction()
#用于产生一个带有反射处理的类，
#和MAKE_REFLECT_BUTTONFUNCTIONWIDGET_SUB_CLASS_FILE宏配和使用
function(MAKE_REFLECT_CLASS_FILE _lib_name)
    MAKE_CLASS_FILES_BY_TEMPLATE_FILE(
        ${_lib_name} 
        ${CMAKE_CURRENT_LIST_DIR}/Base/class_temp_1.h.in
        ${CMAKE_CURRENT_LIST_DIR}/Base/class_temp_1.cpp.in
        ${ARGN}
        )
endfunction()
#=======================================================================
#=======================================================================