macro(common_append_target_property TARGET KEY)
    get_target_property(_TARGET_PROPERTY_VALUE ${TARGET} ${KEY})
    if(NOT _TARGET_PROPERTY_VALUE)
        set(_TARGET_PROPERTY_VALUE)
    endif()
    
    list(APPEND _TARGET_PROPERTY_VALUE ${ARGN})
    set_target_properties(
        ${TARGET}
        PROPERTIES
        ${KEY} "${_TARGET_PROPERTY_VALUE}"
    )
endmacro()
