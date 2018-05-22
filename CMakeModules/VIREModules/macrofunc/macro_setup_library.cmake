MACRO(SETUP_VERSION_LIBRARY LIB_NAME)
	#===================================================
	SET(CMAKE_INCLUDE_CURRENT_DIR ON)
	SET(CMAKE_AUTOMOC ON)
	SET(CMAKE_INCLUDE_CURRENT_DIR ON)
	#===================================================
	#设置UI资源
	FILE(GLOB LIB_QT_UIS "*.ui")
	MESSAGE("LIB_QT_UIS.......${LIB_QT_UIS}")

	# 设置图片资源
	FILE(GLOB LIB_QT_RCS "*.qrc")
	MESSAGE("LIB_QT_RCS.......${LIB_QT_RCS}")

	IF(Qt5Widgets_FOUND)
		QT5_ADD_RESOURCES( LIB_RC_SRCS ${LIB_QT_RCS} )
		QT5_WRAP_UI( LIB_UI_HDRS ${LIB_QT_UIS} )
		IF(Qt5Widgets_VERSION VERSION_LESS 5.2.0)
		   QT5_WRAP_CPP( LIB_UI_SRCS ${LIB_UI_HDRS} OPTIONS "-f" )
		ELSE()
			QT5_WRAP_CPP( LIB_UI_SRCS ${LIB_UI_HDRS} )
		ENDIF()
	ELSE(Qt5Widgets_FOUND)
		INCLUDE( ${QT_USE_FILE} )
		QT4_ADD_RESOURCES( LIB_RC_SRCS ${LIB_QT_RCS} )
		QT4_WRAP_UI( LIB_UI_HDRS ${LIB_QT_UIS} )
		QT4_WRAP_CPP( LIB_UI_SRCS ${LIB_UI_HDRS} OPTIONS "-f" )
	ENDIF(Qt5Widgets_FOUND)
	#===================================================
	SET(LIB_H
		${${LIB_NAME}_LIB_HEADERS}
		${LIB_UI_HDRS}
		${LIB_QT_UIS}
		${LIB_QT_RCS}
	)

	SET(LIB_SRC 
		${${LIB_NAME}_LIB_SRCS} 
		${LIB_RC_SRCS}
		${VERSIONED_LIB_RC}
	)
	MESSAGE("LIB_SRC.......${LIB_SRC}")
		
	ADD_LIBRARY(${LIB_NAME} SHARED
		${LIB_H}
		${LIB_SRC}
	)
	#===================================================
	# Generated Files
	SOURCE_GROUP(
		"Generated Files"
		FILES 
			${LIB_RC_SRCS}
			${LIB_UI_HDRS}
	)
	
	# Form Files
	SOURCE_GROUP(
		"Form Files"
		FILES  
		${LIB_QT_UIS}
	)

	#Resources Files
	SOURCE_GROUP(
		"Resource Files"
		FILES  
		${LIB_QT_RCS}
		${VERSIONED_LIB_RC} 
	)
	#===================================================
ENDMACRO(SETUP_VERSION_LIBRARY LIB_NAME )
