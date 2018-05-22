MACRO(TARGET_SERACH_SUB_DIR_FILES_FOR_INNER _target_name _sub_dirs)

    DEBUG_MESSAGE("MACRO SUB_DIR_SERACH_FILES_FOR_LIB_INNER:->${_target_name}<->${_sub_dirs}")
        
    SET(${_target_name}_ALL_SUB_DIR_HDR )
    SET(${_target_name}_ALL_SUB_DIR_SRCS )
    SET(${_target_name}_ALL_SUB_DIR_UIS )
    SET(${_target_name}_ALL_SUB_DIR_RCS )

    FOREACH(_dir_ ${_sub_dirs} )    
        #FIND Files In SubDir
        FILE(GLOB ${_target_name}_TEMP_SOURCES_HDR "${_dir_}/*.h" "${_dir_}/*.inl" "${_dir_}/*.hpp")
        FILE(GLOB ${_target_name}_TEMP_SOURCES_SRC "${_dir_}/*.cpp" "${_dir_}/*.cc")
        FILE(GLOB ${_target_name}_TEMP_UIS "${_dir_}/*.ui")
        FILE(GLOB ${_target_name}_TEMP_RCS "${_dir_}/*.qrc")
        
        #Set The Param Val
        SET(${_target_name}_ALL_SUB_DIR_HDR ${${_target_name}_ALL_SUB_DIR_HDR} ${${_target_name}_TEMP_SOURCES_HDR})
        SET(${_target_name}_ALL_SUB_DIR_SRCS ${${_target_name}_ALL_SUB_DIR_SRCS} ${${_target_name}_TEMP_SOURCES_HDR} ${${_target_name}_TEMP_SOURCES_SRC}) 
        SET(${_target_name}_ALL_SUB_DIR_UIS ${${_target_name}_ALL_SUB_DIR_UIS} ${${_target_name}_TEMP_UIS}) 
        SET(${_target_name}_ALL_SUB_DIR_RCS ${${_target_name}_ALL_SUB_DIR_RCS} ${${_target_name}_TEMP_RCS}) 
        
        #File Groups
        SOURCE_GROUP( "_${_dir_}" FILES 
        ${${_target_name}_TEMP_SOURCES_HDR} 
        ${${_target_name}_TEMP_SOURCES_SRC}
        ${${_target_name}_TEMP_UIS}
        ${${_target_name}_TEMP_RCS}
    )
    ENDFOREACH( _dir_ ${_sub_dirs} )
    
    DEBUG_MESSAGE("MACRO:ALL_SUB_DIR_SRCS:${${_target_name}_ALL_SUB_DIR_SRCS}")
    DEBUG_MESSAGE("MACRO:ALL_SUB_DIR_UIS:${${_target_name}_ALL_SUB_DIR_UIS}")
    DEBUG_MESSAGE("MACRO:ALL_SUB_DIR_RCS:${${_target_name}_ALL_SUB_DIR_RCS}")
    
    SET(${_target_name}_HEADERS ${${_target_name}_HEADERS} ${${_target_name}_ALL_SUB_DIR_HDR})
    SET(${_target_name}_SRCS ${${_target_name}_SRCS} ${${_target_name}_ALL_SUB_DIR_SRCS})
    SET(${_target_name}_QT_UIS ${${_target_name}_QT_UIS} ${${_target_name}_ALL_SUB_DIR_UIS})
    SET(${_target_name}_QT_RCS ${${_target_name}_QT_RCS} ${${_target_name}_ALL_SUB_DIR_RCS})
ENDMACRO(TARGET_SERACH_SUB_DIR_FILES_FOR_INNER _target_name _sub_dirs)