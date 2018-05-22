###############################################################################
#  <pre>
#  &lt;Date&gt;, &lt;Who&gt;, &lt;What&gt;
#  &#064;2010-05-01, 伏光宝, Initial
# 
###############################################################################
SET(SPARK_GL_NAME Spark)
SET(SPARK_GL_DIR $ENV{THIRDPARTY_PATH}/${SPARK_GL_NAME})
MESSAGE("******SPARK_GL_DIR = ${SPARK_GL_DIR}*****")


FIND_PATH(SPARK_GL_INCLUDE_DIR SPK.h
PATHS
    ${SPARK_GL_DIR}/include
)

###### libraries ######


FIND_LIBRARY(SPARK_GL_LIBRARY
  NAMES spark SPARK_gl_release
  PATHS
  "${SPARK_GL_DIR}/lib/Release"
)

FIND_LIBRARY(SPARK_GL_LIBRARY_DEBUG
  NAMES SPARK_gl_debug
  PATHS
  "${SPARK_GL_DIR}/lib/Debug"
)     
      
SET(SPARK_GL_FOUND "NO")
IF(SPARK_GL_LIBRARY AND SPARK_GL_INCLUDE_DIR)
    SET(SPARK_GL_FOUND "YES")
ENDIF(SPARK_GL_LIBRARY AND SPARK_GL_INCLUDE_DIR)


MESSAGE("******Finish FOUND ********")