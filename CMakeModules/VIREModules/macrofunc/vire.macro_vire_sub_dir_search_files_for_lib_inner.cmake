
MACRO(VIRE_SUB_DIR_SEARCH_FILES_FOR_LIB_INNER lib_name)
    
    SET(sub_dirs ${ARGN})
    
    DEBUG_MESSAGE( "MACRO SUB_DIR_SERACH_FILES_FOR_LIB_INNER:->${lib_name}<->${sub_dirs}")
        
    SET(ALL_SUB_DIR_HDR )
    SET(ALL_SUB_DIR_SRCS )
    SET(ALL_SUB_DIR_UIS )
    SET(ALL_SUB_DIR_RCS )

    FOREACH(_dir_ ${sub_dirs} ) 
        #FIND Files In SubDir
        FILE(GLOB TEMP_SOURCES_HDR "${_dir_}/*.h" "${_dir_}/*.inl" "${_dir_}/*.hpp")
        FILE(GLOB TEMP_SOURCES_SRC "${_dir_}/*.cpp" "${_dir_}/*.cc")
        FILE(GLOB TEMP_UIS "${_dir_}/*.ui")
        FILE(GLOB TEMP_RCS "${_dir_}/*.qrc")
        
        #Set The Param Val
        SET(ALL_SUB_DIR_HDR ${ALL_SUB_DIR_HDR} ${TEMP_SOURCES_HDR})
        SET(ALL_SUB_DIR_SRCS ${ALL_SUB_DIR_SRCS} ${TEMP_SOURCES_HDR} ${TEMP_SOURCES_SRC}) 
        SET(ALL_SUB_DIR_UIS ${ALL_SUB_DIR_UIS} ${TEMP_UIS}) 
        SET(ALL_SUB_DIR_RCS ${ALL_SUB_DIR_RCS} ${TEMP_RCS}) 
        
        #File Groups
        SOURCE_GROUP( "_${_dir_}" FILES 
        ${TEMP_SOURCES_HDR} 
        ${TEMP_SOURCES_SRC}
        ${TEMP_UIS}
        ${TEMP_RCS}
    )
    ENDFOREACH( _dir_ ${sub_dirs} )
    
    DEBUG_MESSAGE( "MACRO:ALL_SUB_DIR_SRCS:${ALL_SUB_DIR_SRCS}")
    DEBUG_MESSAGE( "MACRO:ALL_SUB_DIR_UIS:${ALL_SUB_DIR_UIS}")
    DEBUG_MESSAGE( "MACRO:ALL_SUB_DIR_RCS:${ALL_SUB_DIR_RCS}")
    
    SET(${lib_name}_LIB_HEADERS ${${lib_name}_LIB_HEADERS} ${ALL_SUB_DIR_HDR})
    SET(${lib_name}_LIB_SRCS ${${lib_name}_LIB_SRCS} ${ALL_SUB_DIR_SRCS})
    SET(LIB_QT_UIS ${LIB_QT_UIS} ${ALL_SUB_DIR_UIS})
    SET(LIB_QT_RCS ${LIB_QT_RCS} ${ALL_SUB_DIR_RCS})
ENDMACRO(VIRE_SUB_DIR_SEARCH_FILES_FOR_LIB_INNER lib_name)
