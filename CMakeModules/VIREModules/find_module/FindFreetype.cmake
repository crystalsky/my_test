###############################################################################
# CMake module to search for FREETYPE library
# freetype是一种字体服务而没有提供为实现文字布局或图形化处理这样高阶的功能使用的API（比
#如带色文字渲染之类的）。
#
#  @Copyright: Copyright (c) 2010
#  @Company: 深圳置辰海信科技有限公司
#  @WebSite: http://www.zhichenhaixin.com/
#  @author 叶君
#  
#  @Revision History
#  
#  <pre>
#  &lt;Date&gt;, &lt;Who&gt;, &lt;What&gt;
#  &#064;2011-02-20, 叶君, Initial.
# 
###############################################################################
SET(FREETYPE_DIR $ENV{ZCHX_3RDPARTY_PATH}/freetype/2.4.9)

SET(FREETYPE_BIN_PATH ${FREETYPE_DIR}/bin)
MACRO( FIND_FREETYPE_INCLUDE THIS_FREETYPE_INCLUDE_DIR THIS_FREETYPE_INCLUDE_FILE )

FIND_PATH( ${THIS_FREETYPE_INCLUDE_DIR} ${THIS_FREETYPE_INCLUDE_FILE}
    PATHS
        ${FREETYPE_DIR}
    PATH_SUFFIXES
        /include/
)

ENDMACRO( FIND_FREETYPE_INCLUDE THIS_FREETYPE_INCLUDE_DIR THIS_FREETYPE_INCLUDE_FILE )

FIND_FREETYPE_INCLUDE( FREETYPE_INCLUDE_DIR freetype/freetype.h)

###### libraries ######

MACRO( FIND_FREETYPE_LIBRARY MYLIBRARY MYLIBRARYNAME )

FIND_LIBRARY(${MYLIBRARY}
    NAMES
        ${MYLIBRARYNAME}
    PATHS
        ${FREETYPE_DIR}
    PATH_SUFFIXES
        /lib/release
     )

ENDMACRO(FIND_FREETYPE_LIBRARY LIBRARY LIBRARYNAME)
     
FIND_FREETYPE_LIBRARY( FREETYPE_LIBRARY freetype249)


SET( FREETYPE_FOUND "NO" )
IF( FREETYPE239_LIBRARY AND FREETYPE_INCLUDE_DIR )
    SET( FREETYPE_FOUND "YES" )
    SET( FREETYPE_INCLUDE_DIRS ${FREETYPE_INCLUDE_DIR} )
    GET_FILENAME_COMPONENT( FREETYPE_LIBRARIES_DIR ${FREETYPE239_LIBRARY} PATH )
ENDIF( FREETYPE239_LIBRARY AND FREETYPE_INCLUDE_DIR )

IF(CMAKE_BUILD_TYPE MATCHES Debug)

    INSTALL(FILES ${FREETYPE_DIR}/bin/debug/freetype249_D.dll
        DESTINATION bin
    )
    
    INSTALL(FILES ${FREETYPE_DIR}/bin/debug/libfreetype-6.dll
        DESTINATION bin
    )
    
ELSE(CMAKE_BUILD_TYPE MATCHES Debug)

    INSTALL(FILES ${FREETYPE_DIR}/bin/release/freetype249.dll
        DESTINATION bin
    )
    
    INSTALL(FILES ${FREETYPE_DIR}/bin/release/libfreetype-6.dll
        DESTINATION bin
    )
    
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)
