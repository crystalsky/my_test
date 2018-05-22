FIND_PATH(VRMAINFRAME_INCLUDE_DIR VRMainFrame/MainWindow.h
    ${VRMAINFRAME_DIR}/include
	${VRMAINFRAME_DIR}/include
	$ENV{VRMAINFRAME_DIR}/include
    $ENV{VRMAINFRAME_DIR}/include
    $ENV{VRMAINFRAME_DIR}
    $ENV{DELTA3D_EXT_DIR}/include
    $ENV{DELTA_ROOT}/ext/inc
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


MACRO(FIND_VRMAINFRAME_LIBRARY MYLIBRARY MYLIBRARYNAME)

FIND_LIBRARY(${MYLIBRARY}
    NAMES ${MYLIBRARYNAME}
    PATHS
    ${VRMAINFRAME_DIR}/lib
	${VRFRAME_DIR}/lib
	$ENV{VRMAINFRAME_DIR}/lib
    $ENV{VRMAINFRAME_DIR}/lib
    $ENV{VRMAINFRAME_DIR}
    ${DELTA3D_EXT_DIR}/lib
    $ENV{DELTA_ROOT}/ext/lib
	${OUTPUT_LIBDIR}/Debug
	${OUTPUT_LIBDIR}/Release
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

ENDMACRO(FIND_VRMAINFRAME_LIBRARY MYLIBRARY MYLIBRARYNAME)

FIND_VRMAINFRAME_LIBRARY(VRMAINFRAME_LIBRARY VRMainFrame)
FIND_VRMAINFRAME_LIBRARY(VRMAINFRAME_LIBRARY_DEBUG VRMainFramed)

include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(VRMAINFRAME VRMAINFRAME_INCLUDE_DIR VRMAINFRAME_LIBRARY VRMAINFRAME_LIBRARY_DEBUG)



