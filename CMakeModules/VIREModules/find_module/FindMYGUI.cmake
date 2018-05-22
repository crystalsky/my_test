###############################################################################
# CMake module to search for MYGUI library
#
# If it's found it sets MYGUI_FOUND to TRUE
# and following variables are set:
#    MYGUI_INCLUDE_DIR
#    MYGUI_LIBRARY
#  @author 伏光宝
#  
#  @Revision History
#  
#  <pre>
#  &lt;Date&gt;, &lt;Who&gt;, &lt;What&gt;
#  &#064;2010-05-01, 伏光宝, Initial
# 
###############################################################################
SET(MYGUI_NAME MYGUI)
SET(MYGUI_DIR $ENV{ZCHX_3RDPARTY_PATH}/${MYGUI_NAME})
MESSAGE("******MYGUI_DIR = ${MYGUI_DIR}*****")


FIND_PATH(MYGUI_INCLUDE_DIR MYGUI/MyGUI.h
PATHS
    ${MYGUI_DIR}/include
)

###### libraries ######

FIND_LIBRARY(MYGUIENGINE_LIBRARY
  NAMES MyGUIEngine
  PATHS
  "${MYGUI_DIR}/lib"
)

FIND_LIBRARY(MYGUIENGINE_LIBRARY_DEBUG
  NAMES MyGUIEngine_d
  PATHS
  "${MYGUI_DIR}/lib"
)

FIND_LIBRARY(MYGUIOPENGL_LIBRARY
  NAMES MyGUI.OpenGLPlatform
  PATHS
  "${MYGUI_DIR}/lib"
)

FIND_LIBRARY(MYGUIOPENGL_LIBRARY_DEBUG
  NAMES MyGUI.OpenGLPlatform_d
  PATHS
  "${MYGUI_DIR}/lib"
)
	  
SET(MYGUI_FOUND "NO")
IF(MYGUI_LIBRARY AND MYGUI_INCLUDE_DIR)
    SET(MYGUI_FOUND "YES")
ENDIF(MYGUI_LIBRARY AND MYGUI_INCLUDE_DIR)

#打包

	FILE(GLOB ZCHX_MYGUI_DLL_DEBUG "${MYGUI_DIR}/bin/*.dll")
	INSTALL(FILES ${ZCHX_MYGUI_DLL_DEBUG} DESTINATION bin)
	MESSAGE("ZCHX_MYGUI_DLL_DEBUG = ${ZCHX_MYGUI_DLL_DEBUG}")
	
	
	
	FILE(GLOB ZCHX_MYGUI_DLL_RELEASE "${MYGUI_DIR}/bin/*.dll")
	INSTALL(FILES ${ZCHX_MYGUI_DLL_RELEASE} DESTINATION bin)
	MESSAGE("ZCHX_MYGUI_DLL_RELEASE = ${ZCHX_MYGUI_DLL_RELEASE}")
	

MESSAGE("******Finish FOUND ********")