###############################################################################
# This script sets up packaging targets for each "COMPONENT" as specified in INSTALL commands.
###############################################################################

MESSAGE(STATUS "************************VRCPack***************************")
#==========================PackageResource=========================
set(PKG_RES_RAPIDEE ${CMAKE_SOURCE_DIR}/PackageResource/rapidee.exe)
MESSAGE(STATUS "PKG_RES_RAPIDEE = ${PKG_RES_RAPIDEE}")
INSTALL(
  FILES ${PKG_RES_RAPIDEE}
  DESTINATION bin
  COMPONENT Toos)
#==========================PackageResource=========================


SET(CPACK_NSIS_DISPLAY_NAME ${PROJECT_DESCRIPTION_SUMMARY}) # ÏµÍ³ÏÔÊ¾Ãû³Æ
SET(CPACK_NSIS_PACKAGE_NAME ${PROJECT_DESCRIPTION_SUMMARY}) # ÏµÍ³°üÃû³Æ

SET(CPACK_PACKAGE_NAME "VRFrameWork")    # °üÃû³Æ
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION_SUMMARY})  # ÏµÍ³È«³Æ
SET(CPACK_PACKAGE_VENDOR "Vire")	# Èí¼þ¹©Ó¦ÉÌ

SET(CPACK_GENERATOR "NSIS")# Ñ¹Ëõ¸ñÊ½

SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/doc/License.txt")  # ÊÚÈ¨ÎÄ¼þ
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/doc/README.txt")  # ÏµÍ³½éÉÜ

SET(CPACK_PACKAGE_VERSION "1_0_0" ) 	# ÏµÍ³°æ±¾
SET(CPACK_PACKAGE_VERSION_MAJOR 1)  	# Ö÷°æ±¾ºÅ
SET(CPACK_PACKAGE_VERSION_MINOR 0)	  # ¸±°æ±¾ºÅ
SET(CPACK_PACKAGE_VERSION_PATCH 0)	  # ÐÞ¶©ºÅ

SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.vire.cn")		  # °ïÖúÁ´½Ó
SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.vire.cn")	# ¹ØÓÚÁ´½Ó
SET(CPACK_NSIS_CONTACT "vire@vire.cn")					# ÁªÏµÁ´½Ó

SET(CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_NAME}")	#°²×°Ä¿±êÎÄ¼þ¼Ð
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY ${CPACK_PACKAGE_NAME} ) #  Registry key used when installing this project
SET(CPACK_PACKAGE_FILE_NAME  ${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION} ) #ÉèÖÃ°²×°°üÎÄ¼þÃû

#SET(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_CURRENT_BINARY_DIR};${CPACK_PACKAGE_NAME};ALL;/")
#SET(CPACK_IGNORE_FILES "/CVS/;/\\CMakeLists.txt/;/\\.svn/;\\.swp$;\\.#;/#")  # ´ò°üºöÂÔµÄÎÄ¼þÕýÔò±í´ïÊ½
  # °²×°ÆäËü×ÊÔ´Ä¿Â¼
SET(CPACK_INSTALLED_DIRECTORIES 
        "${CMAKE_INSTALL_PREFIX}/bin;bin"
        "${CMAKE_INSTALL_PREFIX}/include;include"               
        "${CMAKE_INSTALL_PREFIX}/lib;lib" 
)

IF(WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backslashes.
  SET(CPACK_GENERATOR "NSIS")# Ñ¹Ëõ¸ñÊ½
  SET(CPACK_NSIS_COMPRESSOR "/SOLID zlib")
  SET(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}\\\\PackageResource\\\\icons\\\\application_icon.ico")
  SET(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}\\\\PackageResource\\\\icons\\\\modern-uninstall.ico")
  SET(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}\\\\PackageResource\\\\icons\\\\application_icon.ico") #  ´ò°üµÄICON 
  SET(CPACK_NSIS_INSTALLED_ICON_NAME "${CMAKE_SOURCE_DIR}\\\\PackageResource\\\\icons\\\\application_icon.ico")  #   ´ò°ü°²×°³ÌÐòICON
  SET(CPACK_PACKAGE_EXECUTABLES "${APPLICATION_NAME};${PROJECT_DESCRIPTION_SUMMARY}")
  
  #SET(CPACK_NSIS_CREATE_ICONS_EXTRA "CreateShortCut \\\$DESKTOP\\\\${APPLICATION_NAME}.lnk\\\" \\\"$INSTDIR\\\\bin\\\\${APPLICATION_NAME}.exe\\\"")
   
   SET(CPACK_NSIS_CREATE_ICONS_EXTRA "
      CreateShortCut \\\"$DESKTOP\\\\${APPLICATION_NAME}.lnk\\\" \\\"$INSTDIR\\\\bin\\\\${APPLICATION_NAME}.exe\\\" \\\"\\\" \\\"$INSTDIR\\\\resources\\\\icons\\\\VIRE.ico\\\"
"
)
   
# ´ò¿ªÐÞ¸Ä°²×°Â·¾¶
SET(CPACK_NSIS_MODIFY_PATH OFF)

# Use custom version of NSIS.InstallOptions.ini
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules/packaging"  ${CMAKE_MODULE_PATH})

# °²×°ÆäËü×ÊÔ´Ä¿Â¼
#SET(CPACK_INSTALLED_DIRECTORIES 
							#"${CMAKE_SOURCE_DIR}/bin;bin"
							#"${CMAKE_SOURCE_DIR}/resources;resources"								
							#"${CMAKE_SOURCE_DIR}/lib/plugins;lib\\\\plugins" 
							#)

#SET(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "   
    #WriteRegStr '\\\HKCU \\\"Environment\\\"\\\"VRFRAMEWORK_ROOT\\\" $INSTDIR\\\'
#")
SET(CPACK_NSIS_EXTRA_INSTALL_COMMANDS ${CPACK_NSIS_EXTRA_INSTALL_COMMANDS}
"
    ExecWait '\\\"$INSTDIR\\\\bin\\\\rapidee.exe\\\" -S VRFRAMEWORK_ROOT $INSTDIR'
    ExecWait '\\\"$INSTDIR\\\\bin\\\\rapidee.exe\\\" -S VRFRAMEWORK_BIN $INSTDIR\\\\bin'
    ExecWait '\\\"$INSTDIR\\\\bin\\\\rapidee.exe\\\" -S -E -A Path %VRFRAMEWORK_BIN%'
")

SET(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS ${CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS}
"
      #DeleteRegKey HKCU \\\"Environment\\\\VRFRAMEWORK_ROOT\\\"
      ExecWait '\\\"$INSTDIR\\\\bin\\\\rapidee.exe\\\" -R path %VRFRAMEWORK_BIN%'
      ExecWait '\\\"$INSTDIR\\\\bin\\\\rapidee.exe\\\" -D VRFRAMEWORK_ROOT'
      ExecWait '\\\"$INSTDIR\\\\bin\\\\rapidee.exe\\\" -D VRFRAMEWORK_BIN'
")

ENDIF(WIN32 AND NOT UNIX)

SET(CPACK_CMAKE_GENERATOR ${CMAKE_GENERATOR})
  
# Include CPack to introduce the appropriate targets
#include(CPack)

# Installation types
#cpack_add_install_type(Full
#  DISPLAY_NAME "Everything")
#cpack_add_install_type(Developer)

# Component groups
#cpack_add_component_group(Runtime)
#cpack_add_component_group(Development
#  EXPANDED
#  DESCRIPTION "All of the tools you'll ever need to develop software")

# Components
#cpack_add_component(applications
#  DISPLAY_NAME "MyLib Application"
#  DESCRIPTION "An extremely useful application that makes use of MyLib"
#  GROUP Runtime
#  INSTALL_TYPES Full)
##cpack_add_component(documentation
#  #DISPLAY_NAME "MyLib Documentation"
#  #DESCRIPTION "The extensive suite of MyLib Application documentation files"
#  ##GROUP Runtime
# # INSTALL_TYPES Full)
#cpack_add_component(libraries
#  DISPLAY_NAME "Libraries"
#  DESCRIPTION "Static libraries used to build programs with MyLib"
#  GROUP Development
#  INSTALL_TYPES Developer Full)
#cpack_add_component(headers
#  DISPLAY_NAME "C++ Headers"
#  DESCRIPTION "C/C++ header files for use with MyLib"
#  GROUP Development
#  DEPENDS libraries
#  INSTALL_TYPES Developer Full)

#if(mylib_install_to_absolute_path)
  #cpack_add_component(source
   # DISPLAY_NAME "C++ Source Files"
    #DESCRIPTION "C/C++ source files to build MyLib"
    #GROUP Development
    #DEPENDS libraries
    #INSTALL_TYPES Developer Full)
#endif()

#cpack_add_component(Tools
#  DISPLAY_NAME "VRFramework Tools"
#  DESCRIPTION "An extremely useful VRFramework Tools application"
#  GROUP Runtime
#  INSTALL_TYPES Full)


