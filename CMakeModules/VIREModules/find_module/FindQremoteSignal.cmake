
SET(QREMOTESIGNAL_NAME QRemoteSignal)
SET(QREMOTESIGNAL_DIR $ENV{QREMOTESIGNAL_DIR})
MESSAGE("******QREMOTESIGNAL_DIR = ${QREMOTESIGNAL_DIR}*****")


FIND_PATH(QREMOTESIGNAL_INCLUDE_DIR baseconverters.h
PATHS
    ${QREMOTESIGNAL_DIR}/include
)

###### libraries ######

FIND_LIBRARY(QREMOTESIGNAL_LIBRARY
  NAMES ${QREMOTESIGNAL_NAME}
  PATHS
  "${QREMOTESIGNAL_DIR}/lib"
)

FIND_LIBRARY(QREMOTESIGNAL_LIBRARY_DEBUG
  NAMES ${QREMOTESIGNAL_NAME}d
  PATHS
  "${QREMOTESIGNAL_DIR}/lib"
)
	  
SET(QREMOTESIGNAL_FOUND "NO")
IF(QREMOTESIGNAL_LIBRARY AND QREMOTESIGNAL_INCLUDE_DIR)
    SET(QREMOTESIGNAL_FOUND "YES")
ENDIF(QREMOTESIGNAL_LIBRARY AND QREMOTESIGNAL_INCLUDE_DIR)
