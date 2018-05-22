###############################################################################
# CMake module to search for QJSON library
# QJSON（几何引擎——开源）是一个Java拓扑套件（JTS）的C++移植。
# 因此，它的目的是在C++中包含完整的JTS移植。这包括了所有的
# OpenGIS“简单SQL特征”：空间预测函数和空间操作员，
# 以及具体的JTS拓扑功能
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

#打包

	FILE(GLOB ZCHX_QJSON_DLL_DEBUG "${QJSON_DIR}/bin/debug/*.dll")
	INSTALL(FILES ${ZCHX_QJSON_DLL_DEBUG} DESTINATION bin/debug)
	MESSAGE("ZCHX_QJSON_DLL_DEBUG = ${ZCHX_QJSON_DLL_DEBUG}")
	

	FILE(GLOB ZCHX_QJSON_DLL_RELEASE "${QJSON_DIR}/bin/release/*.dll")
	INSTALL(FILES ${ZCHX_QJSON_DLL_RELEASE} DESTINATION bin/release)
	MESSAGE("ZCHX_QJSON_DLL_RELEASE = ${ZCHX_QJSON_DLL_RELEASE}")
	

MESSAGE("******Finish FOUND ********")