cmake_minimum_required(VERSION 2.8.12)

#set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC_RELAXED_MODE ON)

macro(generate_main_file VERSION)
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/main.cpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/main_qt.cpp" COPYONLY)
  file(APPEND "${CMAKE_CURRENT_SOURCE_DIR}/main_qt.cpp"
    "#include \"main_qt.moc\"\n"
  )
endmacro()

#generate_main_file(4)
generate_main_file(5)

SET(LIB_NAME qt_exe)

FILE(GLOB ${LIB_NAME}_QT_UIS "*.ui")

# 设置图片资源
FILE(GLOB ${LIB_NAME}_QT_RCS "*.qrc")

# 设置h代码
FILE(GLOB ${LIB_NAME}_HEADERS "*.h")

# 设置cpp代码
FILE(GLOB ${LIB_NAME}_SRCS "*.cpp")

###########################################################################################
MACRO(TARGET_PROCESS_QT_RESOURCES_UIS_1 target_name)
    SET(_${target_name}_uis 
        ${QT_UIS}
        ${${target_name}_UIS}
        ${${target_name}_QT_UIS}
    )
    SET(_${target_name}_rcs 
        ${${target_name}_RCS}
        ${${target_name}_QT_RCS}
    )
    
    MESSAGE(STATUS "111")
    IF(QT5_FOUND)
        MESSAGE(STATUS "222")
        SET(CMAKE_INCLUDE_CURRENT_DIR ON)
        #MESSAGE(STATUS "Qt5 UI/h/cpp Process....")
        QT5_ADD_RESOURCES( ${target_name}_RC_SRCS ${_${target_name}_rcs})
        #QT5_WRAP_UI( ${target_name}_UI_HDRS ${_${target_name}_uis})
    ELSE()
        #MESSAGE(STATUS "Qt4 UI/h/cpp Process....")
        QT4_ADD_RESOURCES( ${target_name}_RC_SRCS ${_${target_name}_rcs} )
        #QT4_WRAP_UI( ${target_name}_UI_HDRS ${_${target_name}_uis})
        #QT4_WRAP_CPP(${target_name}_UI_SRCS ${${target_name}_UI_HDRS})
        #QT4_WRAP_CPP(${target_name}_MOC_SRCS ${_${target_name}_headers})
    ENDIF()
ENDMACRO()
TARGET_PROCESS_QT_RESOURCES_UIS_1(${LIB_NAME})
###########################################################################################

#add_executable(qt4_exe "${CMAKE_CURRENT_SOURCE_DIR}/main_qt4.cpp")
#target_link_libraries(qt4_exe Qt4::QtCore)
add_executable(${LIB_NAME} 
    ${${LIB_NAME}_HEADERS}
    ${${LIB_NAME}_SRCS}
    #${${LIB_NAME}_QT_RCS}
	${${LIB_NAME}_RC_SRCS}
    ${${LIB_NAME}_QT_UIS}
    )
IF(QT5_FOUND)
target_link_libraries(${LIB_NAME} Qt5::Core Qt5::Widgets)
ELSE()

TARGET_LINK_LIBRARIES(${LIB_NAME}
    ${QT_LIBRARIES} 
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTOPENGL_LIBRARY}
    ${QT_QTXML_LIBRARY})
ENDIF()

# 设置项目标签.
VIRE_SET_TARGET_PROPERTIES_LABEL_FOLDER(${LIB_NAME} "CMake_Test")
