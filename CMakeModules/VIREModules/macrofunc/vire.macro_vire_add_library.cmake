MACRO(VIRE_ADD_LIBRARY _libName)

SET(${_libName}_LIB_HEADER 
    ${${_libName}_UI_HDRS}
    ${${_libName}_QT_UIS}
    ${${_libName}_HEADERS}
)

SET(${_libName}_LIB_CPP        
    ${VERSIONED_LIB_RC} 
    ${${_libName}_SRCS}
    ${${_libName}_RC_SRCS}
    ${${_libName}_QT_RCS}
)

ADD_LIBRARY(${_libName} SHARED
    ${${_libName}_LIB_HEADER}
    ${${_libName}_LIB_CPP}
)
ENDMACRO()