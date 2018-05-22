

macro(find_libaray_standard libName curdir return_relative)
    STRING(TOUPPER ${_target} _UpperTarget)
    IF (MSVC10)s
        IF (CMAKE_CL_64)
            SET(${THIS_LIB_DEPEND_NAME}_ARCH "vc100/x64")
        ELSE (CMAKE_CL_64)
            SET(${THIS_LIB_DEPEND_NAME}_ARCH "vc100")
        ENDIF (CMAKE_CL_64)
    ENDIF (MSVC10)

    IF (MSVC11)
        IF (CMAKE_CL_64)
            SET(${THIS_LIB_DEPEND_NAME}_ARCH "vc110/x64")
        ELSE (CMAKE_CL_64)
            SET(${THIS_LIB_DEPEND_NAME}_ARCH "vc110")
        ENDIF (CMAKE_CL_64)
    ENDIF (MSVC11)


    IF (UNIX)
        SET(${THIS_LIB_DEPEND_NAME}_ARCH "linux")
    ENDIF (UNIX)

endmacro()

