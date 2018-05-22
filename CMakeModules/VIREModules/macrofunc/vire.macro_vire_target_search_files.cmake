macro(VIRE_TARGET_SEARCH_FILES_QT target_name)
    COMMON_SEARCH_TARGET_FILES_QT(${target_name} 
        ${ARGN}
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
endmacro()

macro(VIRE_TARGET_SEARCH_FILES_CPP target_name)
    COMMON_SEARCH_TARGET_FILES_CPP(${target_name} 
        ${ARGN}
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
endmacro()