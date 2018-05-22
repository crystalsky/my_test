FIND_PATH(OSGQTQUICK_INCLUDE_DIR osgqtquick/Utility.hpp
    ${VIRE_DIR}/include
	 ${VROSGQTQUICK_DIR}/include
	 $ENV{VROSGQTQUICK_DIR}/include
    $ENV{VIRE_DIR}/include
    $ENV{VIRE_DIR}  
	${VIRE_INCLUDE_DIR}/VRCore
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/include
    /usr/include
    /usr/include/cal3d
    /sw/include # Fink
    /opt/local/include # DarwinPorts
    /opt/csw/include # Blastwave
    /opt/include
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OSG_ROOT]/include
    /usr/freeware/include
)


MACRO(FIND_OSGQTQUICK_LIBRARY MYLIBRARY MYLIBRARYNAME)

FIND_LIBRARY(${MYLIBRARY}
    NAMES ${MYLIBRARYNAME}
    PATHS
	${OUTPUT_LIBDIR}/Debug
	${OUTPUT_LIBDIR}/Release
    ${VIRE_DIR}/lib
	${VROSGQTQUICK_DIR}/lib
    $ENV{VIRE_DIR}/lib
    $ENV{VIRE_DIR}  
	$ENV{VROSGQTQUICK_DIR}/lib
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/lib
    /usr/lib
    /sw/lib
    /opt/local/lib
    /opt/csw/lib
    /opt/lib
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OSG_ROOT]/lib
    /usr/freeware/lib64
)

ENDMACRO(FIND_OSGQTQUICK_LIBRARY MYLIBRARY MYLIBRARYNAME)

SET(RELEASE_LIST osgqtquick osgqtquick)
FIND_OSGQTQUICK_LIBRARY(OSGQTQUICK_LIBRARY "${RELEASE_LIST}")

SET(DEBUG_LIST osgqtquickd osgqtquickd)
FIND_OSGQTQUICK_LIBRARY(OSGQTQUICK_LIBRARY_DEBUG "${DEBUG_LIST}")

SET(OSGQTQUICK_FOUND "NO")
IF(OSGQTQUICK_LIBRARY AND OSGQTQUICK_INCLUDE_DIR)
    SET(OSGQTQUICK_FOUND "YES")
ENDIF(OSGQTQUICK_LIBRARY AND OSGQTQUICK_INCLUDE_DIR)


