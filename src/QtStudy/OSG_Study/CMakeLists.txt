SET(APPLICATION_NAME OSGQt)

#===================================================
BEGIN_TARGET(${APPLICATION_NAME})

#===================================================
# 定义项目版本
VIRE_VERSIONED_TARGET(${APPLICATION_NAME} 1 0 0 102)

disable_msvc_warnings(4819)
disable_msvc_warnings(4172)

#===================================================
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)

#===================================================
INCLUDE_DIRECTORIES(
	${Boost_INCLUDE_DIR}
	${VIRE_INCLUDE_DIR}
	${OPENTHREADS_INCLUDE_DIR}
	{PROJECT_INCLUDE_DIR}
	${PROJECT_SRC_DIR}/library_src/
)


VIRE_MAKE_CLASS_WITH_UI_WIDGET(${APPLICATION_NAME}
	#OSGViewTestWidget
	#OSG_Examples
	#OSG_Test
)

VIRE_MAKE_CLASS_WITH_UI_WIDGET(${APPLICATION_NAME} NO_UI_FILE
	#CFunctionOSGViewerWidget
)

#VIRE_MAKE_CLASS(${APPLICATION_NAME}
#	SUB_DIR_NAME OSGProgramingGuid
#	T03
#	T04
#	T05
#	T06
#	T07
#)

include(${CMAKE_CURRENT_LIST_DIR}/my_osg_template.cmake)
MAKE_OSG_TEMP_CLASS_FILES(${APPLICATION_NAME}
	SUB_DIR_NAME OSGProgramingGuid/T05
	T05_P119_ClipNode
)

#设置UI资源
FILE(GLOB_RECURSE ${APPLICATION_NAME}_QT_UIS "*.ui")

# 设置图片资源
FILE(GLOB_RECURSE ${APPLICATION_NAME}_QT_RCS "*.qrc")

file(GLOB_RECURSE ${APPLICATION_NAME}_HEADERS *.h)

file(GLOB_RECURSE ${APPLICATION_NAME}_SRCS *.cpp)

#===================================================
#Qt处理UI和QRC文件
VIRE_TARGET_PROCESS_QT_RESOURCES_UIS(${APPLICATION_NAME})

#===================================================
SET(_LIB_HEADER 
	${${APPLICATION_NAME}_UI_HDRS}
	${${APPLICATION_NAME}_QT_UIS}
	${${APPLICATION_NAME}_HEADERS}
)

SET(_LIB_CPP 		
	${VERSIONED_LIB_RC} 
	${${APPLICATION_NAME}_SRCS}
	${${APPLICATION_NAME}_RC_SRCS}
	${${APPLICATION_NAME}_QT_RCS}
)

#打包相关文件成可执行文件
ADD_EXECUTABLE(${APPLICATION_NAME} 
	${_LIB_HEADER}
	${_LIB_CPP}
)

# 设置Link依赖包
ADD_3RD_DEPENDENCIES(${APPLICATION_NAME}
	OSG
	QTUTILITY
	UTILITYKIT
	QTUI
	GLOG
	
	ADDITION_LIBRARY 
	OSGVIEWER 
	OSGDB
	OSGGA
	OSGSIM
	OSGUTIL
	OSGQT
	OSGTEXT
	OPENTHREADS
	)

 TARGET_LINK_LIBRARIES(${APPLICATION_NAME}	
	
)

IF ( Qt5Widgets_FOUND )
    qt5_use_modules( ${APPLICATION_NAME} Gui Widgets OpenGL Xml Svg Test Sql)
ELSE()   
TARGET_LINK_LIBRARIES(${APPLICATION_NAME}
${QT_LIBRARIES} 
	${QT_QTOPENGL_LIBRARY} 
	${QT_QTCORE_LIBRARY} 
	${QT_QTGUI_LIBRARY} 
	${QT_QTSVG_LIBRARY}
	${QT_QTTEST_LIBRARY}
	${QT_QTXML_LIBRARY}

)
ENDIF( Qt5Widgets_FOUND )

#configure_file(app.config ${PROJECT_SOURCE_DIR}/bin/Debug @ONLY) 
#configure_file(app.config ${PROJECT_SOURCE_DIR}/bin/Release @ONLY) 

#===================================================
VIRE_TARGET_SOURCE_GROUP(${APPLICATION_NAME})
SOURCE_GROUP(
	"Resource Files"
	FILES  
	AppFramework.rc
)

include(macro_source_group_by_dir)
set(all_files ${${APPLICATION_NAME}_HEADERS} ${${APPLICATION_NAME}_SRCS})
source_group_by_dir_ex(all_files)
#===================================================
# 设置工程的属性
VIRE_SET_TARGET_PROPERTIES_LABEL_FOLDER(${APPLICATION_NAME} "App" PROJECT_LABEL_PREFIX App)

#===================================================
IF(WIN32)
    SET_TARGET_PROPERTIES(${APPLICATION_NAME} PROPERTIES
        #LINK_FLAGS "/VERSION:${APPLICATION_VERSION}"
        LINK_FLAGS_RELEASE "/ENTRY:\"mainCRTStartup\" /SUBSYSTEM:WINDOWS"
        LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE" )
ENDIF(WIN32)
#===================================================  
END_TARGET(${APPLICATION_NAME})
#===================================================

# debug 安装
INSTALL(
TARGETS ${APPLICATION_NAME}
RUNTIME DESTINATION bin/Debug
)
	

# release 安装
INSTALL(
TARGETS ${APPLICATION_NAME}
RUNTIME DESTINATION bin/release
)
	
	
# present the packaging option only if we have the cpack command defined (effectively >= 2.6.0)
IF(CMAKE_CPACK_COMMAND)
    OPTION(BUILD_VIRE_PACKAGES "Set to ON to generate CPack configuration files and packaging targets" OFF)
    IF(BUILD_VIRE_PACKAGES)
      INCLUDE(VIRECPack)
    ENDIF(BUILD_VIRE_PACKAGES)
ENDIF(CMAKE_CPACK_COMMAND)

INSTALL(CODE "MESSAGE(\"Installing App:${APPLICATION_NAME}..\")")


