include(macro_target_search_sub_dirs_files)
#############################################################
#VIRE_TARGET_SERACH_SUB_DIRS_FILES
#此宏主要是查找子目录，将查找到的头文件、源文件、UI文件、QRC文件分别依附到“处理树上”，并将以在公程中以子目录分类显示
#
MACRO(VIRE_TARGET_SERACH_SUB_DIRS_FILES target_name)
    TARGET_SERACH_SUB_DIRS_FILES(${target_name} ${ARGN})
ENDMACRO(VIRE_TARGET_SERACH_SUB_DIRS_FILES target_name)

#############################################################
#VIRE_SERACH_LIB_SUB_DIRS_FILES
#此宏主要是查找子目录，将查找到的头文件、源文件、UI文件、QRC文件分别依附到“处理树上”，并将以在公程中以子目录分类显示
#
MACRO(VIRE_SERACH_LIB_SUB_DIRS_FILES lib_name)
    SET(sub_dirs ${ARGN})
    VIRE_TARGET_SERACH_SUB_DIRS_FILES(${lib_name} ${sub_dirs})
ENDMACRO(VIRE_SERACH_LIB_SUB_DIRS_FILES lib_name)