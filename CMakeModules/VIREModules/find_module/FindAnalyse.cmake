
FIND_PATH(ANALYSEL_INCLUDE_DIR AnalyseDLL.h
    $ENV{ANALYSE_DIR}/include
    $ENV{ANALYSE_DIR}
    $ENV{ANALYSELDIR}/include
    $ENV{ANALYSELDIR}
    $ENV{ANALYSEL_ROOT}/include  
    $ENV{ANALYSEL_ROOT}/include  
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/include
    /usr/include
    /sw/include # Fink
    /opt/local/include # DarwinPorts
    /opt/csw/include # Blastwave
    /opt/include
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;ANALYSEL_ROOT]/include
    /usr/freeware/include
)

MACRO(FIND_ANALYSEL_LIBRARY MYLIBRARY MYLIBRARYNAME)

    FIND_LIBRARY(${MYLIBRARY}
        NAMES ${MYLIBRARYNAME}
        PATHS
        $ENV{ANALYSE_DIR}/lib/win32/microsoft
		$ENV{ANALYSE_DIR}/lib/win64/microsoft
        $ENV{ANALYSE_DIR}/build/lib
        $ENV{ANALYSE_DIR}
        $ENV{ANALYSEDIR}/lib
        $ENV{ANALYSEDIR}
        $ENV{ANALYSE_ROOT}/lib
        $ENV{ANALYSE_ROOT}/build/lib       
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local/lib
        /usr/lib
        /sw/lib
        /opt/local/lib
        /opt/csw/lib
        /opt/lib
        [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;ANALYSEL_ROOT]/lib
        /usr/freeware/lib64
    )

ENDMACRO(FIND_ANALYSEL_LIBRARY LIBRARY LIBRARYNAME)

FIND_ANALYSEL_LIBRARY(ANALYSEL_LIBRARY AnalyseDLL)


SET(ANALYSEL_FOUND "NO")
IF(ANALYSEL_LIBRARY AND ANALYSEL_INCLUDE_DIR)
    SET(ANALYSEL_FOUND "YES")
ENDIF(ANALYSEL_LIBRARY AND ANALYSEL_INCLUDE_DIR)
