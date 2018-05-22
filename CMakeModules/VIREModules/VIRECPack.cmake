###############################################################################
# This script sets up packaging targets for each "COMPONENT" as specified in INSTALL commands.
#
# 
###############################################################################

MESSAGE("************************VIRECPack***************************")
SET(APPLICATION_NAME "scoms")    # Ӧ������
MESSAGE("PROJECT: ${PROJECT_NAME}")
MESSAGE("APPLICATION: ${APPLICATION_NAME}")
MESSAGE("PROJECT_DESCRIPTION_SUMMARY: ${PROJECT_DESCRIPTION_SUMMARY}")

SET(CPACK_NSIS_DISPLAY_NAME ${PROJECT_DESCRIPTION_SUMMARY}) # ϵͳ��ʾ����
SET(CPACK_NSIS_PACKAGE_NAME ${PROJECT_DESCRIPTION_SUMMARY}) # ϵͳ������

SET(CPACK_PACKAGE_NAME ${APPLICATION_NAME})    # ������
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION_SUMMARY})  # ϵͳȫ��
SET(CPACK_PACKAGE_VENDOR ${PROJECT_VENDOR})	# �����Ӧ��
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/doc/License.txt")  # ��Ȩ�ļ�
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")  # ϵͳ����
SET(CPACK_PACKAGE_VERSION ${PACKAGE_VERSION} ) 	# ϵͳ�汾
SET(CPACK_PACKAGE_VERSION_MAJOR ${VIRE_MAJOR_VERSION} )  	# ���汾��
SET(CPACK_PACKAGE_VERSION_MINOR ${VIRE_MINOR_VERSION})	  	# ���汾��
SET(CPACK_PACKAGE_VERSION_PATCH ${VIRE_PATCH_VERSION})	  	# �޶���
SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.szcenterstar.com")		# ��������
SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.szcenterstar.com")	# ��������
SET(CPACK_NSIS_CONTACT "lilu@zhichenhaixin.com")					# ��ϵ����

SET(CPACK_GENERATOR "NSIS")# ѹ����ʽ
	   
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_NAME}\\\\${PROJECT_NAME}_${PACKAGE_VERSION}")	#��װĿ���ļ���
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY ${APPLICATION_NAME} ) #  Registry key used when installing this project
  
SET(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_CURRENT_BINARY_DIR};${APPLICATION_NAME};ALL;/")

SET(CPACK_IGNORE_FILES "/CVS/;/\\CMakeLists.txt/;/\\.svn/;\\.swp$;\\.#;/#")  # ������Ե��ļ�������ʽ

SET(CPACK_PACKAGE_FILE_NAME  ${APPLICATION_NAME}-${CPACK_PACKAGE_VERSION}-setup ) #���ð�װ���ļ���
  
IF(WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backslashes.
  
  SET(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}\\\\resources\\\\icons\\\\VIRE.ico")
  SET(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}\\\\resources\\\\icons\\\\uninstall.ico")
  SET(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}\\\\resources\\\\icons\\\\${PROJECT_NAME}.bmp") #  �����ICON 
  SET(CPACK_NSIS_INSTALLED_ICON_NAME "${CMAKE_SOURCE_DIR}\\\\resources\\\\icons\\\\VIRE.ico")  #   �����װ����ICON
  SET(CPACK_PACKAGE_EXECUTABLES "${APPLICATION_NAME};${PROJECT_DESCRIPTION_SUMMARY}")
  
  #SET(CPACK_NSIS_CREATE_ICONS_EXTRA "CreateShortCut \\\$DESKTOP\\\\${APPLICATION_NAME}.lnk\\\" \\\"$INSTDIR\\\\bin\\\\${APPLICATION_NAME}.exe\\\"")
   

   SET(CPACK_NSIS_CREATE_ICONS_EXTRA "
      CreateShortCut \\\"$DESKTOP\\\\${APPLICATION_NAME}.lnk\\\" \\\"$INSTDIR\\\\bin\\\\${APPLICATION_NAME}.exe\\\" \\\"\\\" \\\"$INSTDIR\\\\resources\\\\icons\\\\VIRE.ico\\\"
"
)
   
   
  # ���޸İ�װ·��
  SET(CPACK_NSIS_MODIFY_PATH OFF)

  # Use custom version of NSIS.InstallOptions.ini
  SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules/packaging"  ${CMAKE_MODULE_PATH})
	
  # ��װ������ԴĿ¼
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

