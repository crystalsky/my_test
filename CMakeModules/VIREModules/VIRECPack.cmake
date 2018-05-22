###############################################################################
# This script sets up packaging targets for each "COMPONENT" as specified in INSTALL commands.
#
# 
###############################################################################

MESSAGE("************************VIRECPack***************************")
SET(APPLICATION_NAME "scoms")    # 应用名称
MESSAGE("PROJECT: ${PROJECT_NAME}")
MESSAGE("APPLICATION: ${APPLICATION_NAME}")
MESSAGE("PROJECT_DESCRIPTION_SUMMARY: ${PROJECT_DESCRIPTION_SUMMARY}")

SET(CPACK_NSIS_DISPLAY_NAME ${PROJECT_DESCRIPTION_SUMMARY}) # 系统显示名称
SET(CPACK_NSIS_PACKAGE_NAME ${PROJECT_DESCRIPTION_SUMMARY}) # 系统包名称

SET(CPACK_PACKAGE_NAME ${APPLICATION_NAME})    # 包名称
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION_SUMMARY})  # 系统全称
SET(CPACK_PACKAGE_VENDOR ${PROJECT_VENDOR})	# 软件供应商
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/doc/License.txt")  # 授权文件
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")  # 系统介绍
SET(CPACK_PACKAGE_VERSION ${PACKAGE_VERSION} ) 	# 系统版本
SET(CPACK_PACKAGE_VERSION_MAJOR ${VIRE_MAJOR_VERSION} )  	# 主版本号
SET(CPACK_PACKAGE_VERSION_MINOR ${VIRE_MINOR_VERSION})	  	# 副版本号
SET(CPACK_PACKAGE_VERSION_PATCH ${VIRE_PATCH_VERSION})	  	# 修订号
SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.szcenterstar.com")		# 帮助链接
SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.szcenterstar.com")	# 关于链接
SET(CPACK_NSIS_CONTACT "lilu@zhichenhaixin.com")					# 联系链接

SET(CPACK_GENERATOR "NSIS")# 压缩格式
	   
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_NAME}\\\\${PROJECT_NAME}_${PACKAGE_VERSION}")	#安装目标文件夹
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY ${APPLICATION_NAME} ) #  Registry key used when installing this project
  
SET(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_CURRENT_BINARY_DIR};${APPLICATION_NAME};ALL;/")

SET(CPACK_IGNORE_FILES "/CVS/;/\\CMakeLists.txt/;/\\.svn/;\\.swp$;\\.#;/#")  # 打包忽略的文件正则表达式

SET(CPACK_PACKAGE_FILE_NAME  ${APPLICATION_NAME}-${CPACK_PACKAGE_VERSION}-setup ) #设置安装包文件名
  
IF(WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backslashes.
  
  SET(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}\\\\resources\\\\icons\\\\VIRE.ico")
  SET(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}\\\\resources\\\\icons\\\\uninstall.ico")
  SET(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}\\\\resources\\\\icons\\\\${PROJECT_NAME}.bmp") #  打包的ICON 
  SET(CPACK_NSIS_INSTALLED_ICON_NAME "${CMAKE_SOURCE_DIR}\\\\resources\\\\icons\\\\VIRE.ico")  #   打包安装程序ICON
  SET(CPACK_PACKAGE_EXECUTABLES "${APPLICATION_NAME};${PROJECT_DESCRIPTION_SUMMARY}")
  
  #SET(CPACK_NSIS_CREATE_ICONS_EXTRA "CreateShortCut \\\$DESKTOP\\\\${APPLICATION_NAME}.lnk\\\" \\\"$INSTDIR\\\\bin\\\\${APPLICATION_NAME}.exe\\\"")
   

   SET(CPACK_NSIS_CREATE_ICONS_EXTRA "
      CreateShortCut \\\"$DESKTOP\\\\${APPLICATION_NAME}.lnk\\\" \\\"$INSTDIR\\\\bin\\\\${APPLICATION_NAME}.exe\\\" \\\"\\\" \\\"$INSTDIR\\\\resources\\\\icons\\\\VIRE.ico\\\"
"
)
   
   
  # 打开修改安装路径
  SET(CPACK_NSIS_MODIFY_PATH OFF)

  # Use custom version of NSIS.InstallOptions.ini
  SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules/packaging"  ${CMAKE_MODULE_PATH})
	
  # 安装其它资源目录
  SET(CPACK_INSTALLED_DIRECTORIES 
								"${CMAKE_SOURCE_DIR}/bin;bin"
								"${CMAKE_SOURCE_DIR}/resources;resources"								
								"${CMAKE_SOURCE_DIR}/lib/plugins;lib\\\\plugins" 
								)
	
  SET(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "		
 		WriteRegStr HKCU \\\"Environment\\\" \\\"VIRE_HOME\\\" $INSTDIR\\\\bin\\\"
  	")

	

SET(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
  DeleteRegKey HKCU \\\"Software\\\\${PROJECT_NAME}\\\"
  DeleteRegKey HKCU \\\"Environment\\\\VIRE_HOME\\\"
  Delete \\\"$DESKTOP\\\\${PROJECT_NAME}.lnk\\\"
")
	

ENDIF(WIN32 AND NOT UNIX)

SET(CPACK_CMAKE_GENERATOR ${CMAKE_GENERATOR})
  
INCLUDE(CPack)

