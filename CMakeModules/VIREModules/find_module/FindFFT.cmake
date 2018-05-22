
FIND_PATH(FFT_INCLUDE_DIR FFT.h
    $ENV{FFT_DIR}/include
    $ENV{FFT_DIR}
    $ENV{FFTDIR}/include
    $ENV{FFTDIR}
    $ENV{FFT_ROOT}/include  
    $ENV{FFT_ROOT}/include  
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/include
    /usr/include
    /sw/include # Fink
    /opt/local/include # DarwinPorts
    /opt/csw/include # Blastwave
    /opt/include
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;FFT_ROOT]/include
    /usr/freeware/include
)

MACRO(FIND_FFT_LIBRARY MYLIBRARY MYLIBRARYNAME)

    FIND_LIBRARY(${MYLIBRARY}
        NAMES ${MYLIBRARYNAME}
        PATHS
        $ENV{FFT_DIR}/lib/win32/microsoft
		$ENV{FFT_DIR}/lib/win64/microsoft
        $ENV{FFT_DIR}/build/lib
        $ENV{FFT_DIR}
        $ENV{FFTDIR}/lib
        $ENV{FFTDIR}
        $ENV{FFT_ROOT}/lib
        $ENV{FFT_ROOT}/build/lib
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
        [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;FFT_ROOT]/lib
        /usr/freeware/lib64
    )

ENDMACRO(FIND_FFT_LIBRARY LIBRARY LIBRARYNAME)

FIND_FFT_LIBRARY(FFT_LIBRARY FFT)


SET(FFT_FOUND "NO")
IF(FFT_LIBRARY AND FFT_INCLUDE_DIR)
    SET(FFT_FOUND "YES")
ENDIF(FFT_LIBRARY AND FFT_INCLUDE_DIR)
