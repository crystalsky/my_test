# Where is this and what do we need it for?
#############################################################
include(macro_make_class_file)
#############################################################

#产生QObject子类文件
MACRO(VIRE_MAKE_CLASS_WITH_QOBJECT _lib_name)
    MAKE_CLASS_WITH_QOBJECT(${_lib_name} ${ARGN})
ENDMACRO()

#产生带导出标志的QObject子类文件
MACRO(VIRE_MAKE_EXPORT_CLASS_WITH_QOBJECT _lib_name _export_header_dir)
    MAKE_EXPORT_CLASS_WITH_QOBJECT(
        ${_lib_name} 
        ${_export_header_dir}
        ${ARGN}
    )
ENDMACRO()

#========================================================
#产生有UI文件QWidget子类文件
MACRO(VIRE_MAKE_CLASS_WITH_UI_WIDGET _lib_name)
    MAKE_CLASS_WITH_UI_WIDGET(${_lib_name} ${ARGN})
ENDMACRO()

#产生没有UI文件QWidget子类文件
MACRO(VIRE_MAKE_CLASS_WIDGET _lib_name)
    MAKE_CLASS_WIDGET(${_lib_name} ${ARGN})
ENDMACRO()

#产生有UI文件QWidget子类导出文件
MACRO(VIRE_MAKE_EXPORT_CLASS_WITH_UI_WIDGET _lib_name _export_header_dir)
    MAKE_EXPORT_CLASS_WITH_UI_WIDGET(
        ${_lib_name} 
        ${_export_header_dir}
        ${ARGN}
    )
ENDMACRO()

#产生没有UI文件QWidget子类导出文件
MACRO(VIRE_MAKE_EXPORT_CLASS_WIDGET _lib_name _export_header_dir)
    MAKE_EXPORT_CLASS_WIDGET(
        ${_lib_name} 
        ${_export_header_dir}
        ${ARGN}
    )
ENDMACRO()
#========================================================
#产生有UI文件QDialog子类文件
MACRO(VIRE_MAKE_CLASS_WITH_UI_DIALOG _lib_name)
    MAKE_CLASS_WITH_UI_DIALOG(${_lib_name} ${ARGN})
ENDMACRO()

#产生有QDialog子类文件
MACRO(VIRE_MAKE_CLASS_DIALOG _lib_name)
    MAKE_CLASS_DIALOG(${_lib_name} ${ARGN})
ENDMACRO()

#产生有UI文件QDialog子类导出文件
MACRO(VIRE_MAKE_EXPORT_CLASS_WITH_UI_DIALOG _lib_name _export_header_dir)
    MAKE_EXPORT_CLASS_WITH_UI_DIALOG(
        ${_lib_name} 
        ${_export_header_dir}
        ${ARGN}
    )
ENDMACRO()

#产生有UI文件QDialog子类导出文件
MACRO(VIRE_MAKE_EXPORT_CLASS_DIALOG _lib_name _export_header_dir)
    MAKE_EXPORT_CLASS_DIALOG(
        ${_lib_name} 
        ${_export_header_dir}
        ${ARGN}
    )
ENDMACRO()
#========================================================
#产生普通类文件
MACRO(VIRE_MAKE_CLASS _lib_name)
    MAKE_CLASS(${_lib_name} ${ARGN})
ENDMACRO()

MACRO(VIRE_MAKE_EXPORT_CLASS _lib_name _export_header_dir)
    MAKE_EXPORT_CLASS(
        ${_lib_name}
        ${_export_header_dir}
        ${ARGN}
    )
ENDMACRO()
#############################################################

#以下的宏是为匹配以前工程用的宏使用
MACRO(VIRE_MAKE_CLASS_FILE_WITH_QOBJECT_EX _lib_name)
    VIRE_MAKE_CLASS_WITH_QOBJECT(${_lib_name} ${ARGN})
ENDMACRO()

MACRO(VIRE_MAKE_CLASS_FILE_WITH_UI_WIDGET_EX _lib_name)
    VIRE_MAKE_CLASS_WITH_UI_WIDGET(${_lib_name} ${ARGN})
ENDMACRO()

MACRO(VIRE_MAKE_CLASS_FILE_WITH_UI_DIALOG_EX _lib_name)
    VIRE_MAKE_CLASS_WITH_UI_DIALOG(${_lib_name} ${ARGN})
ENDMACRO()

MACRO(VIRE_MAKE_CLASS_FILE_EX _lib_name)
    VIRE_MAKE_CLASS(${_lib_name} ${ARGN})
ENDMACRO(VIRE_MAKE_CLASS_FILE_EX _lib_name)

#############################################################