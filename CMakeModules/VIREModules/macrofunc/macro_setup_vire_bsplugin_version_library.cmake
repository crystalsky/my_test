MACRO(SETUP_VIRE_BSPLUGIN_VERSION_LIBRARY libName)
	SET(_LIB_NAME 		${libName})

	#===================================================
	SET(CMAKE_INCLUDE_CURRENT_DIR ON)
	SET(CMAKE_AUTOMOC ON)
	#===================================================
	INCLUDE_DIRECTORIES(
		${VIRE_INCLUDE_DIR}
		${VIRE_BSPLUGIN_INCLUDE_DIR}/${LIB_NAME}
	)
	#===================================================
	SET(CMAKE_INCLUDE_CURRENT_DIR ON)
	SET(CMAKE_AUTOMOC ON)
	#===================================================
	#设置UI资源
	FILE(GLOB LIB_QT_UIS "*.ui")

	# 设置图片资源
	SET(GLOB LIB_QT_RCS "*.qrc")
	
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

	# 设置h代码
	FILE(GLOB ${LIB_NAME}_LIB_HEADERS "*.h" "${VIRE_BSPLUGIN_INCLUDE_DIR}/${LIB_NAME}/*.h")
	
	# 设置cpp代码
	FILE(GLOB ${LIB_NAME}_LIB_SRCS "*.cpp")
	
	SET(_LIB_HEADER 
		${LIB_UI_HDRS}
		${LIB_QT_UIS}
		${${LIB_NAME}_LIB_HEADERS}
		${MAKE_BSPLUGIN_FILE_HEADER}
	)
	MESSAGE("---${_LIB_NAME} Headers:" ${_LIB_HEADER})	
	
	SET(_LIB_CPP 		
		${VERSIONED_LIB_RC} 
		${MAKE_BSPLUGIN_FILE_SRC}
		${${LIB_NAME}_LIB_SRCS}
		${LIB_RC_SRCS}
		${LIB_QT_RCS}
	)
	MESSAGE("---${_LIB_NAME} cpps:" ${_LIB_CPP})	
	
	ADD_LIBRARY(${_LIB_NAME} SHARED
		${_LIB_HEADER}
		${_LIB_CPP})
		
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
ENDMACRO(SETUP_VIRE_BSPLUGIN_VERSION_LIBRARY libName)