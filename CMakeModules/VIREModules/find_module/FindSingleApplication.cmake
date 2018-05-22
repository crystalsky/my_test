###############################################################################
# CMake module to search for SINGLEAPPLICATION library
#  Open Dynamics Engine(SINGLEAPPLICATION)是一款免费的、具有工业质量的开发库，
# 它用于模拟 带关节的刚体动力学 。特点是效率高、灵活、健壮，
# 并有内置的碰撞检测（collision detection ），适于模拟地面交通工具（ ground vehicles ）、
# 带足的生物 (legged creatures) 等。 
# 
###############################################################################
SET(SINGLEAPPLICATION_NAME SingleApplication)
SET(SINGLEAPPLICATION_DIR $ENV{THIRDPARTY_PATH}/${SINGLEAPPLICATION_NAME})
MESSAGE("******SINGLEAPPLICATION_DIR = ${SINGLEAPPLICATION_DIR}*****")


FIND_PATH(SINGLEAPPLICATION_INCLUDE_DIR QtSingleApplication.h
PATHS
    ${SINGLEAPPLICATION_DIR}/include
)

###### libraries ######

FIND_LIBRARY(SINGLEAPPLICATION_LIBRARY
  NAMES SingleApplication
  PATHS
  "${SINGLEAPPLICATION_DIR}/lib/Release"
)

FIND_LIBRARY(SINGLEAPPLICATION_LIBRARY_DEBUG
  NAMES SingleApplicationd
  PATHS
  "${SINGLEAPPLICATION_DIR}/lib/Debug"
)
      
SET(SINGLEAPPLICATION_FOUND "NO")
IF(SINGLEAPPLICATION_LIBRARY AND SINGLEAPPLICATION_INCLUDE_DIR)
    SET(SINGLEAPPLICATION_FOUND "YES")
ENDIF(SINGLEAPPLICATION_LIBRARY AND SINGLEAPPLICATION_INCLUDE_DIR)
