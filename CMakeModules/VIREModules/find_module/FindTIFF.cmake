###############################################################################
# CMake macro to find TIFF library.
# Libtiff ��һ��������д��ǩͼ���ļ���ʽ����дΪTIFF���Ŀ⡣
# ����⻹����һЩ�����й�����������TIFF�ļ���
# ����Դ���뷽ʽ�ַ������ҿ����ڶ���ƽ̨���Զ����ƹ����ķ�ʽ���֡�
# libtiff�����Sam Leffler��Silicon Graphics�����ڼ��д��
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

#���
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
