#此宏自动处理Qt的中间文件生成
#NOTE:
#1. QT_CPP_MOC_FILE
#   用于代码的CPP文件中含有Q_OBJECT的类，代码的CPP文件最下面要包含xxx.moc文件

MACRO(TARGET_PROCESS_QT_RESOURCES_UIS target_name)
    DEBUG_MESSAGE("MACRO TARGET_PROCESS_QT_RESOURCES_UIS:->${target_name}<-")

    SET(options QT_AUTO_GEN)
    SET(oneValueArgs)
    SET(multiValueArgs PATHS)
    
    cmake_parse_arguments(${target_name} 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})
    
    IF(${target_name}_QT_AUTO_GEN)
        #set(CMAKE_AUTORCC ON)
        set(CMAKE_AUTOUIC ON)
        set(CMAKE_AUTOMOC ON)
        set(CMAKE_INCLUDE_CURRENT_DIR ON)
        #set(CMAKE_AUTOMOC_RELAXED_MODE ON)
    
        SET(_${target_name}_rcs 
            ${${target_name}_RCS}
            ${${target_name}_QT_RCS}
        )

        IF(QT5_FOUND)
            QT5_ADD_RESOURCES( ${target_name}_RC_SRCS ${_${target_name}_rcs})
        ELSE()
            QT4_ADD_RESOURCES( ${target_name}_RC_SRCS ${_${target_name}_rcs})
        ENDIF()
        
        set(${target_name}_UI_RC_SRC
                ${${target_name}_QT_UIS} 
                ${${target_name}_RC_SRCS}
                ${VERSIONED_LIB_RC}     #version.rc
            )
    ELSE()
        #这里是为了匹配QT4的处理而存在
        #在QT5环境中
        if(QT4_FOUND AND CMAKE_AUTOMOC)
            SET(CMAKE_AUTOMOC OFF)
            INCLUDE(${QT_USE_FILE})
        elseif(QT5_FOUND)
            SET(CMAKE_INCLUDE_CURRENT_DIR ON)
            SET(CMAKE_AUTOMOC OFF)
            if(QT_CPP_MOC_FILE)
                MESSAGE(STATUS "QT5_FOUND...QT_CPP_MOC_FILE Is On, Set CMAKE_AUTOMOC True....")
                SET(CMAKE_AUTOMOC ON)
            endif()
        endif()
        
        SET(_${target_name}_uis 
            ${QT_UIS}
            ${LIB_QT_UIS} 
            ${${target_name}_UIS}
            ${${target_name}_QT_UIS}
        )
        SET(_${target_name}_rcs 
            ${LIB_QT_RCS} 
            ${${target_name}_RCS}
            ${${target_name}_QT_RCS}
        )
        SET(_${target_name}_headers 
            ${LIB_HDRS} 
            ${${target_name}_HDRS}
            ${${target_name}_HEADERS}
        )

        IF(QT5_FOUND)
            SET(CMAKE_INCLUDE_CURRENT_DIR ON)

            QT5_ADD_RESOURCES( ${target_name}_RC_SRCS ${_${target_name}_rcs})
            QT5_WRAP_UI( ${target_name}_UI_HDRS ${_${target_name}_uis})
            IF(Qt5Widgets_VERSION VERSION_LESS 5.2.0)
                QT5_WRAP_CPP(${target_name}_UI_SRCS ${${target_name}_UI_HDRS} OPTIONS "-f" )
                QT5_WRAP_CPP(${target_name}_MOC_SRCS ${_${target_name}_headers} OPTIONS "-f")
            ELSE()
                QT5_WRAP_CPP(${target_name}_UI_SRCS ${${target_name}_UI_HDRS})
                QT5_WRAP_CPP(${target_name}_MOC_SRCS ${_${target_name}_headers})
            ENDIF()
        ELSE()
            QT4_ADD_RESOURCES( ${target_name}_RC_SRCS ${_${target_name}_rcs} )
            QT4_WRAP_UI( ${target_name}_UI_HDRS ${_${target_name}_uis})
            QT4_WRAP_CPP(${target_name}_UI_SRCS ${${target_name}_UI_HDRS})
            QT4_WRAP_CPP(${target_name}_MOC_SRCS ${_${target_name}_headers})
        ENDIF()
        
        set(${target_name}_UI_RC_SRC 
                ${${target_name}_RC_SRCS}
                ${${target_name}_UI_HDRS}
                ${${target_name}_UI_SRCS}
                ${VERSIONED_LIB_RC}     #version.rc
            )

        #combine the variable
        if(QT_CPP_MOC_FILE)
            set(${target_name}_MOC_SRCS ${${target_name}_UI_RC_SRC})
        else()
            SET(${target_name}_MOC_SRCS 
                ${${target_name}_MOC_SRCS} 
                ${${target_name}_UI_RC_SRC}
            )
        endif()
    ENDIF()
    #MESSAGE(STATUS "${target_name}_RC_SRCS:${${target_name}_MOC_SRCS}")
    #MESSAGE(STATUS "${target_name}_UI_HDRS:${${target_name}_UI_HDRS}")
    #MESSAGE(STATUS "${target_name}_UI_SRCS:${${target_name}_UI_SRCS}")
    #MESSAGE(STATUS "${target_name}_MOC_SRCS:${${target_name}_MOC_SRCS}")
ENDMACRO()

#此宏自动处理Qt的中间文件生成
#NOTE:
#1. QT_CPP_MOC_FILE
#   用于代码的CPP文件中含有Q_OBJECT的类，代码的CPP文件最下面要包含xxx.moc文件

MACRO(TARGET_PROCESS_QT_RESOURCES_UIS1 target_name)
    
    
ENDMACRO()