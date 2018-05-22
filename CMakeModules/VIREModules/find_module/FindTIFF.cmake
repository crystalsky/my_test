###############################################################################
# CMake macro to find TIFF library.
# Libtiff 是一个用来读写标签图像文件格式（简写为TIFF）的库。
# 这个库还包含一些命令行工具用来处理TIFF文件。
# 它以源代码方式分发，并且可以在多种平台上以二进制构建的方式出现。
# libtiff软件由Sam Leffler在Silicon Graphics工作期间编写。
# 
###############################################################################
SET(TIFF_NAME libtiff)
SET(TIFF_DIR $ENV{THIRDPARTY_PATH}/${TIFF_NAME})
MESSAGE("******TIFF_DIR = ${TIFF_DIR}*****")

FIND_PATH(TIFF_INCLUDE_DIR tiff.h      
	PATHS
    "${TIFF_DIR}/include"
)
	
###### libraries ######
SET(TIFF_NAMES ${TIFF_NAME} tiff libtiff libtiff3)
FIND_LIBRARY(TIFF_LIBRARY 
	NAMES ${TIFF_NAMES}	
	PATHS
    "${TIFF_DIR}/lib/Release"
)

FIND_LIBRARY(TIFF_LIBRARY_DEBUG
  NAMES libtiffd
  PATHS
  "${TIFF_DIR}/lib/Debug"
)
SET(TIFF_FOUND "NO")
IF(TIFF_FOUND)
  SET(TIFF_FOUND "YES")
  SET(TIFF_LIBRARIES ${TIFF_LIBRARY} )
  SET(TIFF_LIBRARIES_DEBUG ${TIFF_LIBRARY_DEBUG} )
ENDIF(TIFF_FOUND)

#打包
IF(CMAKE_BUILD_TYPE MATCHES Debug)
	FILE(GLOB ZCHX_TIFF_DLL_DEBUG "${TIFF_DIR}/bin/debug/*.dll")
	INSTALL(FILES ${ZCHX_TIFF_DLL_DEBUG} DESTINATION bin)
	MESSAGE("ZCHX_TIFF_DLL_DEBUG = ${ZCHX_TIFF_DLL_DEBUG}")
	
ELSE(CMAKE_BUILD_TYPE MATCHES Debug)
	FILE(GLOB ZCHX_TIFF_DLL_RELEASE "${TIFF_DIR}/bin/release/*.dll")
	INSTALL(FILES ${ZCHX_TIFF_DLL_RELEASE} DESTINATION bin)
	MESSAGE("ZCHX_TIFF_DLL_RELEASE = ${ZCHX_TIFF_DLL_RELEASE}")
	
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

MESSAGE("******Finish FOUND ********")
