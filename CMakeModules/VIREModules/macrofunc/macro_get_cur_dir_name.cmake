MACRO(GET_CUR_DIR_NAME full_path _dir_name)
    get_filename_component(tmp 
        ${full_path} 
        NAME_WE
    )
    SET(${_dir_name} ${tmp})
    #MESSAGE(WARNING "${full_path} Has Dir ${tmp}")
ENDMACRO()