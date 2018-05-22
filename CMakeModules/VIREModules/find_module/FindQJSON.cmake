###############################################################################
# CMake module to search for QJSON library
# QJSON���������桪����Դ����һ��Java�����׼���JTS����C++��ֲ��
# ��ˣ�����Ŀ������C++�а���������JTS��ֲ������������е�
# OpenGIS����SQL���������ռ�Ԥ�⺯���Ϳռ����Ա��
# �Լ������JTS���˹���
# 
###############################################################################
SET(QJSON_NAME qjson)
SET(QJSON_DIR $ENV{THIRDPARTY_PATH}/qjson/0.7.1)
MESSAGE("******QJSON_DIR = ${QJSON_DIR}*****")


FIND_PATH(QJSON_INCLUDE_DIR parser.h
PATHS
    ${QJSON_DIR}/include
	${QJSON_DIR}/include/qjson
)

###### libraries ######

FIND_LIBRARY(QJSON_LIBRARY
  NAMES ${QJSON_NAME}
  PATHS
  "${QJSON_DIR}/lib/Release"
)

FIND_LIBRARY(QJSON_LIBRARY_DEBUG
  NAMES ${QJSON_NAME}
  PATHS
  "${QJSON_DIR}/lib/Debug"
)
	  
SET(QJSON_FOUND "NO")
IF(QJSON_LIBRARY AND QJSON_INCLUDE_DIR)
    SET(QJSON_FOUND "YES")
ENDIF(QJSON_LIBRARY AND QJSON_INCLUDE_DIR)

#���

	FILE(GLOB ZCHX_QJSON_DLL_DEBUG "${QJSON_DIR}/bin/debug/*.dll")
	INSTALL(FILES ${ZCHX_QJSON_DLL_DEBUG} DESTINATION bin/debug)
	MESSAGE("ZCHX_QJSON_DLL_DEBUG = ${ZCHX_QJSON_DLL_DEBUG}")
	

	FILE(GLOB ZCHX_QJSON_DLL_RELEASE "${QJSON_DIR}/bin/release/*.dll")
	INSTALL(FILES ${ZCHX_QJSON_DLL_RELEASE} DESTINATION bin/release)
	MESSAGE("ZCHX_QJSON_DLL_RELEASE = ${ZCHX_QJSON_DLL_RELEASE}")
	

MESSAGE("******Finish FOUND ********")