# warning: use `acmake_group_source` instead, this file may be removed in the
#   future
include(util.common_source_group)

macro(source_group_by_dir_ex)
    common_source_group_by_subdir(${ARGN})
endmacro()

