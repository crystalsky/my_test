###############################################################################
# CMake module to search for JPEG library
# libjpeg 是一个完全用C语言编写的库，包含了被广泛使用的JPEG解码、JPEG编码和其他的JPEG功能的实现。这个库由独立JPEG工作组维护。最新版本号是6b，于1998年发布。
# 和libjpeg一起工作的程序还有：
#    * cjpeg and djpeg，用于JPEG和一些其他流行图形文件格式之间的转换。
#    * rdjpgcom and wrjpgcom，用于在JFIF文件中插入和提取文字信息。
#    * jpegtran – 一个用于在不同的JPEG格式之间进行无损转换的工具。
# 
###############################################################################
SET(JPEG_HOME $ENV{THIRDPARTY_PATH}/libjpeg)


IF(WIN32)

  IF (MSVC)
    FIND_PATH(JPEG_INCLUDE_DIR jpeglib.h
      "${JPEG_HOME}/include"
      NO_DEFAULT_PATH
      )
    FIND_LIBRARY(JPEG_LIBRARY NAMES libjpeg
    PATHS    
    "${JPEG_HOME}/lib/release/"
      NO_DEFAULT_PATH
      )


  ENDIF (MSVC)


ENDIF(WIN32)


IF (JPEG_INCLUDE_DIR AND JPEG_LIBRARY)
   SET(JPEG_FOUND TRUE)
ENDIF (JPEG_INCLUDE_DIR AND JPEG_LIBRARY)

IF (JPEG_FOUND)

   IF (NOT JPEG_FIND_QUIETLY)
      MESSAGE(STATUS "Found JPEG: ${JPEG_LIBRARY}")
   ENDIF (NOT JPEG_FIND_QUIETLY)
    
  SET(JPEG_LIBRARIES ${JPEG_LIBRARY})
ELSE (JPEG_FOUND)

   MESSAGE(JPEG_INCLUDE_DIR=${JPEG_INCLUDE_DIR})
   MESSAGE(JPEG_LIBRARY=${JPEG_LIBRARY})
   MESSAGE(FATAL_ERROR "Could not find JPEG")

ENDIF (JPEG_FOUND)
