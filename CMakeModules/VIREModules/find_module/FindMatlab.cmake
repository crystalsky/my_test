
FIND_PATH(MATLAB_INCLUDE_DIR blas.h
    $ENV{MATLAB_DIR}/include
    $ENV{MATLAB_DIR}
    $ENV{MATLABDIR}/include
    $ENV{MATLABDIR}
    $ENV{MATLAB_ROOT}/include  
    $ENV{MATLAB_ROOT}/include  
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/include
    /usr/include
    /sw/include # Fink
    /opt/local/include # DarwinPorts
    /opt/csw/include # Blastwave
    /opt/include
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;MATLAB_ROOT]/include
    /usr/freeware/include
)

MACRO(FIND_MATLAB_LIBRARY MYLIBRARY MYLIBRARYNAME)

    FIND_LIBRARY(${MYLIBRARY}
        NAMES ${MYLIBRARYNAME}
        PATHS
        $ENV{MATLAB_DIR}/lib/win32/microsoft
		$ENV{MATLAB_DIR}/lib/win64/microsoft
        $ENV{MATLAB_DIR}/build/lib
        $ENV{MATLAB_DIR}
        $ENV{MATLABDIR}/lib
        $ENV{MATLABDIR}
        $ENV{MATLAB_ROOT}/lib
        $ENV{MATLAB_ROOT}/build/lib
        ${DELTA3D_EXT_DIR}/lib
        ${DELTA3D_EXT_DIR}/lib64
        $ENV{DELTA_ROOT}/ext/lib
        $ENV{DELTA_ROOT}/ext/lib64
        ~/Library/Frameworks
        /Library/Frameworks
        /usr/local/lib
        /usr/lib
        /sw/lib
        /opt/local/lib
        /opt/csw/lib
        /opt/lib
        [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;MATLAB_ROOT]/lib
        /usr/freeware/lib64
    )

ENDMACRO(FIND_MATLAB_LIBRARY LIBRARY LIBRARYNAME)

# Find release (optimized) libs
#FIND_MATLAB_LIBRARY(CREATERADARECHO_LIBRARY CreateRadarEcho)
#FIND_MATLAB_LIBRARY(DETECTION_LIBRARY Detection)
#FIND_MATLAB_LIBRARY(LIBEMLRT_LIBRARY libemlrt)
#FIND_MATLAB_LIBRARY(LIBFIXEDPOINT_LIBRARY libfixedpoint)
#FIND_MATLAB_LIBRARY(LIBMWBLAS_LIBRARY libmwblas)
#FIND_MATLAB_LIBRARY(LIBMWBLASCOMPAT32_LIBRARY libmwblascompat32)
#FIND_MATLAB_LIBRARY(LIBMWLAPACK_LIBRARY libmwlapack)
#FIND_MATLAB_LIBRARY(LIBMWMATHUTIL_LIBRARY libmwmathutil)
#FIND_MATLAB_LIBRARY(LIBMWSERVICES_LIBRARY libmwservices)
#FIND_MATLAB_LIBRARY(LIBMWSL_SOLVER_RTW_LIBRARY libmwsl_solver_rtw)
#FIND_MATLAB_LIBRARY(LIBUT_LIBRARY libut)
#FIND_MATLAB_LIBRARY(MATCHEDFILTER_LIBRARY MatchedFilter)
#FIND_MATLAB_LIBRARY(MCLBASE_LIBRARY mclbase)
#FIND_MATLAB_LIBRARY(MCLCOMMAIN_LIBRARY mclcommain)
FIND_MATLAB_LIBRARY(MCLMCR_LIBRARY mclmcr)
FIND_MATLAB_LIBRARY(MCLMCRRT_LIBRARY mclmcrrt)
FIND_MATLAB_LIBRARY(RADARSIM_LIBRARY RadarSim)


SET(MATLAB_FOUND "NO")
IF(MATLAB_LIBRARY AND MATLAB_INCLUDE_DIR)
    SET(MATLAB_FOUND "YES")
ENDIF(MATLAB_LIBRARY AND MATLAB_INCLUDE_DIR)
