SET(APPLICATION_NAME QtExe)

#===================================================

BEGIN_TARGET(${APPLICATION_NAME})

#===================================================
# ¶¨ÒåÏîÄ¿°æ±¾
VIRE_VERSIONED_TARGET(${APPLICATION_NAME} 1 0 0 102)

# Note the version no is Mmmpp for Major/minor/patch, 0-padded, thus '10100' for 1.1.0

SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /NODEFAULTLIB:LIBCMTD")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON) 

ADD_DEFINITIONS(-DCONSOLE)
#===================================================
INCLUDE_DIRECTORIES(${RIBBON_INCLUDE_DIR}
	${Boost_INCLUDE_DIR}
	${TINYXML_INCLUDE_DIR}
	${DEFAULT_INPROJECT_INCLUDE_DIRCLUDE_SUBDIR}
	${PROJECT_SRC_DIR}/library_src/color_picker
	./Base
)

include(${CMAKE_CURRENT_LIST_DIR}/Base/make_class_temp_files.cmake)
#===================================================
VIRE_MAKE_CLASS(${APPLICATION_NAME} 
	#Q_CLASS 
	#PARENT QWidget
	#QStyleSheetWidget1
	data_gen_functions
)

MAKE_CLASS_TEMP_CLASS_TEST_WIDGET(${APPLICATION_NAME}
	SUB_DIR_NAME QtCoreStudy
	Page_QTextCodec
)

MAKE_REFLECT_CLASS_FILE(${APPLICATION_NAME}
	SUB_DIR_NAME)
#===================================================
#BOOST
MAKE_STEPBASE_SUB_CLASS_FILE(${APPLICATION_NAME}
	SUB_DIR_NAME BoostStudy
	#widget_boost_root
)

MAKE_REFLECT_BUTTONFUNCTIONWIDGET_SUB_CLASS_FILE(${APPLICATION_NAME}
	SUB_DIR_NAME BoostStudy
	boost_memory_manage	#�ڴ����
)

MAKE_REFLECT_CLASS_FILE(${APPLICATION_NAME}
	SUB_DIR_NAME BoostStudy/_memory_manage
	boost_pool	#pool
)

MAKE_REFLECT_CLASS_FILE(${APPLICATION_NAME}
	SUB_DIR_NAME BoostStudy
	#SUB_DIR_NAME BoostStudy/_func_test
	#_base64
	_circle_buffer
)

MAKE_REFLECT_CLASS_FILE(${APPLICATION_NAME}
	SUB_DIR_NAME BoostStudy/_ptree
	boost_ptree_xml
	boost_ptree_json
	boost_ptree_ini
)

#==================================================
#XmlSerialize test
MAKE_CLASS_TEMP_CLASS_TEST_WIDGET(${APPLICATION_NAME}
	SUB_DIR_NAME XmlSerialize
	XmlSerialize_Test_Widget
)

MAKE_REFLECT_CLASS_FILE(${APPLICATION_NAME}
	SUB_DIR_NAME XmlSerialize
	XmlSerialize_Base_Test
)

#==================================================
#template test
MAKE_CLASS_TEMP_CLASS_TEST_WIDGET(${APPLICATION_NAME}
	SUB_DIR_NAME template
	template_test_widget
)

MAKE_REFLECT_CLASS_FILE(${APPLICATION_NAME}
	SUB_DIR_NAME template
	template_test_1
)
#=================================================

MAKE_REFLECT_CLASS_FILE(${APPLICATION_NAME}
	SUB_DIR_NAME _xerces-c
	xerces_dom_test
)

#===================================================
MAKE_BUTTONFUNCTIONWIDGTH_SUB_CLASS_FILE(${APPLICATION_NAME}
	SUB_DIR_NAME DesignPatternStudy
		DesignPatternWidget
	)
VIRE_MAKE_CLASS(${APPLICATION_NAME} 
	SUB_DIR_NAME DesignPatternStudy
		LiskovSubstitutionPrinciple
	)
#===================================================
#ÉèÖÃUI×ÊÔ´
FILE(GLOB_RECURSE ${APPLICATION_NAME}_QT_UIS "*.ui")

# ÉèÖÃÍ¼Æ¬×ÊÔ´
FILE(GLOB_RECURSE ${APPLICATION_NAME}_QT_RCS "*.qrc")

# ÉèÖÃh´úÂë
FILE(GLOB_RECURSE ${APPLICATION_NAME}_HEADERS "*.h")

# ÉèÖÃcpp´úÂë
FILE(GLOB_RECURSE ${APPLICATION_NAME}_SRCS "*.cpp")
#===================================================
#Qt´¦ÀíUIºÍQRCÎÄ¼þ
#VIRE_TARGET_PROCESS_QT_RESOURCES_UIS(${APPLICATION_NAME})
VIRE_TARGET_PROCESS_QT_RESOURCES_UIS_AUTO_GEN(${APPLICATION_NAME})

#file(TIMESTAMP ./main.cpp TT)
#MESSAGE("File TIMESTAMP: ${TT}")
#STRING(TIMESTAMP "%Y-%m-%dT%H:%M:%S" FS)
#MESSAGE("File TIMESTAMP: ${FS}")
#===================================================
SET(_${APPLICATION_NAME}_HEADER
	${${APPLICATION_NAME}_UI_HDRS}
	${${APPLICATION_NAME}_QT_UIS}
	${${APPLICATION_NAME}_HEADERS}
)

SET(_${APPLICATION_NAME}_CPP 		
	${VERSIONED_LIB_RC} 
	${${APPLICATION_NAME}_SRCS}
	${${APPLICATION_NAME}_RC_SRCS}
	${${APPLICATION_NAME}_QT_RCS}
	${${APPLICATION_NAME}_MOC_SRCS}
)

#´ò°üÏà¹ØÎÄ¼þ³É¿ÉÖ´ÐÐÎÄ¼þ
ADD_EXECUTABLE(${APPLICATION_NAME} 
	${_${APPLICATION_NAME}_HEADER}
	${_${APPLICATION_NAME}_CPP}
)

#===================================================
#ÉèÖÃLinkÒÀÀµ°ü
TARGET_LINK_LIBRARIES(${APPLICATION_NAME}
	${XMLFOUNDATION_LIBRARIES}
	QtColorPickerLib
	
	${Boost_TIMER_LIBRARY}
	${Boost_DATE_TIME_LIBRARY}
	${Boost_SIGNALS_LIBRARY}
	${Boost_THREAD_LIBRARY}
	${Boost_SYSTEM_LIBRARY}
	${Boost_CHRONO_LIBRARY}
	${Boost_FILESYSTEM_LIBRARY}
	${Boost_SERIALIZATION_LIBRARY}
	${Boost_PROGRAM_OPTIONS_LIBRARY}
	
)

ADD_3RD_DEPENDENCIES(${APPLICATION_NAME} 
		#QTUTILITY_LIBRARY
		#GLOG_LIBRARY
		#UTILITYKIT_LIBRARY
		#TINYXML_LIBRARY
		#QTUI_LIBRARY
		
)

target_link_libraries(${APPLICATION_NAME} 
	QTUTILITY::QTUTILITY
	GLOG::GLOG
	TINYXML::TINYXML
	XERCES-C::XERCES-C
	QTUI::QTUI
	UTILITYKIT::UTILITYKIT
	QTXMLSERIALIZE::QTXMLSERIALIZE
)

IF ( Qt5Widgets_FOUND )
    qt5_use_modules( ${APPLICATION_NAME} Gui Widgets OpenGL Xml Test Quick Concurrent Multimedia MultimediaWidgets)
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
#===================================================
#configure_file(app.config ${PROJECT_SOURCE_DIR}/bin/Debug @ONLY) 
#configure_file(app.config ${PROJECT_SOURCE_DIR}/bin/Release @ONLY) 

# ÉèÖÃ¹¤³ÌµÄÊôÐÔ
SET (TARGET_OUTPUT_NAME ${APPLICATION_NAME} )
SET_TARGET_PROPERTIES( ${APPLICATION_NAME} PROPERTIES OUTPUT_NAME ${TARGET_OUTPUT_NAME} )
SET_TARGET_PROPERTIES(${APPLICATION_NAME} PROPERTIES DEBUG_OUTPUT_NAME "${TARGET_OUTPUT_NAME}${CMAKE_DEBUG_POSTFIX}")
SET_TARGET_PROPERTIES(${APPLICATION_NAME} PROPERTIES RELEASE_OUTPUT_NAME "${TARGET_OUTPUT_NAME}${CMAKE_RELEASE_POSTFIX}")

# ÉèÖÃÓëQT designer ¼¯³É
SET_TARGET_PROPERTIES(${APPLICATION_NAME} PROPERTIES VS_KEYWORD "Qt4VSv1.0")

# ÉèÖÃÏîÄ¿±êÇ©.
SET_TARGET_PROPERTIES(${APPLICATION_NAME} PROPERTIES PROJECT_LABEL "App ${APPLICATION_NAME}")
SET_TARGET_PROPERTIES(${APPLICATION_NAME} PROPERTIES FOLDER "App") 
 
#===================================================
#test source_group_by_dir_ex
set(all_files 
	${${APPLICATION_NAME}_HEADERS} 
	${${APPLICATION_NAME}_SRCS} 
	${${APPLICATION_NAME}_QT_UIS} 
	${${APPLICATION_NAME}_QT_RCS})

#MESSAGE("${all_files}")
#source_group_by_dir_ex(all_files)
common_source_group_by_subdir(all_files)


#SOURCE_GROUP(FormFiles REGULAR_EXPRESSION "\\w+\\.ui")
SOURCE_GROUP(ResourceFiles FILES 
	${${APPLICATION_NAME}_QT_UIS}
	${${APPLICATION_NAME}_QT_QRC}
)
#===================================================
#VIRE_TARGET_SOURCE_GROUP(${APPLICATION_NAME})
#===================================================

#Êä³öµ½ÉÏ¼¶Ä¿Â¼£¬È¡Ïûdebug, release Ä¿Â¼
IF (MSVC_IDE) 
	SET_TARGET_PROPERTIES( ${APPLICATION_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin )
	SET_TARGET_PROPERTIES( ${APPLICATION_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin/Debug )
	SET_TARGET_PROPERTIES( ${APPLICATION_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/Release)
ENDIF() 
 
END_TARGET(${APPLICATION_NAME})


