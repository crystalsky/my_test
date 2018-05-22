include(util.common_source_group)

macro(source_group_ex groupname)
    common_source_group_by_file_base_name(
        ${groupname} 
        ${ARGN}
    )
endmacro()

macro(source_group_ex_headerdir groupname header_dir)
    common_source_group_by_file_base_name_headerdir(
        ${groupname} 
        ${header_dir} 
        ${ARGN}
    )
endmacro()