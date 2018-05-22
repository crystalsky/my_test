###############################################################################
#  <pre>
#  &lt;Date&gt;, &lt;Who&gt;, &lt;What&gt;
#  &#064;2010-05-01, 伏光宝, Initial
# 
###############################################################################
SET(SPARK_NAME Spark)
SET(SPARK_DIR $ENV{THIRDPARTY_PATH}/${SPARK_NAME})
MESSAGE("******SPARK_DIR = ${SPARK_DIR}*****")


FIND_PATH(SPARK_INCLUDE_DIR SPK.h
PATHS
    ${SPARK_DIR}/include
)

###### libraries ######

FIND_LIBRARY(SPARK_LIBRARY
  NAMES spark spark_release
  PATHS
  "${SPARK_DIR}/lib/Release"
)

FIND_LIBRARY(SPARK_LIBRARY_DEBUG
  NAMES spark_debug
  PATHS
  "${SPARK_DIR}/lib/Debug"
)

FIND_LIBRARY(SPARK_GL_LIBRARY
  NAMES ode spark_gl_release
  PATHS
  "${SPARK_DIR}/lib/Release"
)

FIND_LIBRARY(SPARK_GL_LIBRARY_DEBUG
  NAMES spark_gl_debug
  PATHS
  "${SPARK_DIR}/lib/Debug"
)     
      
SET(SPARK_FOUND "NO")
IF(SPARK_LIBRARY AND SPARK_INCLUDE_DIR)
    SET(SPARK_FOUND "YES")
ENDIF(SPARK_LIBRARY AND SPARK_INCLUDE_DIR)


MESSAGE("******Finish FOUND ********")