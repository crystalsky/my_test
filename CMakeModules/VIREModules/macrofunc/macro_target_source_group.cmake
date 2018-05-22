MACRO(TARGET_SOURCE_GROUP target_name)
    SOURCE_GROUP(
    "Generated Files"
        FILES 
        ${LIB_RC_SRCS}
        ${LIB_UI_HDRS}
        ${LIB_UI_SRCS}
        ${LIB_MOC_SRCS}
        ${${target_name}_UI_HDRS}
        ${${target_name}_RC_SRCS}
        ${${target_name}_MOC_SRCS}
    )

    # Form Files
    SOURCE_GROUP(
        "Form Files"
        FILES  
        ${QT_UIS}
        ${LIB_QT_UIS} 
        ${${target_name}_UIS}
        ${${target_name}_QT_UIS}
    )
    
    #Resource Files
    SOURCE_GROUP(
        "Resource Files"
        FILES  
        ${VERSIONED_LIB_RC}
        ${${target_name}_QT_RCS}
        ${${target_name}_VERSIONED_LIB_RC}

        ${LIB_QT_RCS} 
        ${${target_name}_RCS}
        ${${target_name}_QT_RCS}
    )
ENDMACRO()