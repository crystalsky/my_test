MACRO(COMMON_GET_VERSION_LIB_DIR libdir)
    IF (WIN32)
        IF (MSVC)
            IF(MSVC12)
                SET(${libdir} "lib/vc120")
            ELSEIF(MSVC11)
                SET(${libdir} "lib/vc110")
            ELSEIF(MSVC10)
                SET(${libdir} "lib/vc100")
            ELSEIF(MSVC90)
                SET(${libdir} "lib/vc90")
            ELSEIF(MSVC80)
                SET(${libdir} "lib/vc80")
            ELSEIF(MSVC14)#ms2015
                SET(${libdir} "lib/vc140")
            ENDIF()
        ENDIF(MSVC)
    ELSE()
        SET(${libdir} "lib")
    ENDIF()
ENDMACRO()

MACRO(COMMON_GET_VERSION_BIN_DIR bindir)
    IF (WIN32)
        IF (MSVC)
            IF(MSVC12)
                SET(${bindir} "bin/vc120")
            ELSEIF(MSVC11)
                SET(${bindir} "bin/vc110")
            ELSEIF(MSVC10)
                SET(${bindir} "bin/vc100")
            ELSEIF(MSVC90)
                SET(${bindir} "bin/vc90")
            ELSEIF(MSVC80)
                SET(${bindir} "bin/vc80")
            ELSEIF(MSVC14)#ms2015
                SET(${bindir} "bin/vc140")
            ENDIF()
        ENDIF(MSVC)
    ELSE()
        SET(${bindir} "bin")
    ENDIF()
ENDMACRO()