
FIND_PATH(PLOTLAB_INCLUDE_DIR CLPDrawLayers.h
    $ENV{ANALYSE_DIR}/include
    $ENV{ANALYSE_DIR}
    $ENV{PLOTLABDIR}/include
    $ENV{PLOTLABDIR}
    $ENV{PLOTLAB_ROOT}/include  
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/include
    /usr/include
    /sw/include # Fink
    /opt/local/include # DarwinPorts
    /opt/csw/include # Blastwave
    /opt/include
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;PLOTLAB_ROOT]/include
    /usr/freeware/include
)

MACRO(FIND_PLOTLAB_LIBRARY MYLIBRARY MYLIBRARYNAME)

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
		$ENV{PLOTLAB_ROOT}/lib       
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local/lib
        /usr/lib
        /sw/lib
        /opt/local/lib
        /opt/csw/lib
        /opt/lib
        [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;PLOTLAB_ROOT]/lib
        /usr/freeware/lib64
    )

ENDMACRO(FIND_PLOTLAB_LIBRARY LIBRARY LIBRARYNAME)

FIND_PLOTLAB_LIBRARY( VCLOADERMS_LIBRARY VCLLoaderMS )

FIND_PLOTLAB_LIBRARY( VCSINGALLABLIB_LIBRARY VCSignalLabLib )
FIND_PLOTLAB_LIBRARY( VCSINGALLABLIB_LIBRARY_DEBUG VCSignalLabLib_Debug)

FIND_PLOTLAB_LIBRARY( VCSIGNALLABLIB_DLL_LIBRARY VCSignalLabLib_DLL )
FIND_PLOTLAB_LIBRARY( VCSIGNALLABLIB_DLL_LIBRARY_DEBUG VCSignalLabLib_DLL_Debug)

SET(PLOTLAB_FOUND "NO")
IF(PLOTLAB_LIBRARY AND PLOTLAB_INCLUDE_DIR)
    SET(PLOTLAB_FOUND "YES")
ENDIF(PLOTLAB_LIBRARY AND PLOTLAB_INCLUDE_DIR)
