include(UtilityMacros)
include(util.common_check_debug)
#=====================================================================================
MACRO(VIRE_SET_TARGET_PROPERTIES_LABEL_FOLDER _Target _Folder)
  SET_TARGET_PROPERTIES_PROJECT(${_Target} 
    PROJECT_FOLDER ${_Folder} 
    QT_VS_KEYWORD "Qt4VSv1.0" 
    ${ARGN}
  )
ENDMACRO()
#=====================================================================================
MACRO(VIRE_SET_TARGET_PROPERTIES_LIB_DEBUG_RELEASE _Target)
    SET_TARGET_PROPERTIES_OUTPUT(${_Target} 
        "${${ProjectVal_PREFIX_OUT_PUT}_BIN_DIR}"
        TO_SAME_DIR ${_Binary_In_Same_Dir}
        ${ARGN}
    )
ENDMACRO()

MACRO(VIRE_SET_TARGET_PROPERTIES_OUTPUT_FOR_BSPLUGIN _Target)
    SET_TARGET_PROPERTIES_OUTPUT(${_Target} 
        "${${ProjectVal_PREFIX_OUT_PUT}_BIN_DIR}"
        TO_SAME_DIR ${_Binary_In_Same_Dir}
        SUBDIR "VRPlugins/BSPlugins"
        ${ARGN}
    )
ENDMACRO()

MACRO(VIRE_SET_TARGET_PROPERTIES_OUTPUT_FOR_ACTORPLUGIN _Target)
    SET_TARGET_PROPERTIES_OUTPUT(${_Target} 
        "${${ProjectVal_PREFIX_OUT_PUT}_BIN_DIR}"
        TO_SAME_DIR ${_Binary_In_Same_Dir}
        SUBDIR "VRPlugins/ActorPlugins"
        ${ARGN}
    )
ENDMACRO()

MACRO(VIRE_SET_TARGET_PROPERTIES_OUTPUT_NORMAL _Target)
    VIRE_SET_TARGET_PROPERTIES_LIB_DEBUG_RELEASE(${_Target})
ENDMACRO()

MACRO(VIRE_SET_TARGET_PROPERTIES_OUTPUT_FOR_LIB _Target)
    VIRE_SET_TARGET_PROPERTIES_LIB_DEBUG_RELEASE(${_Target})
ENDMACRO()
#=====================================================================================
MACRO(VIRE_POST_BUILD_COPY target_name)
    POST_BUILD_COPY(${target_name} ${ARGN})
ENDMACRO()

MACRO(VIRE_POST_BUILD_COPY_BSPLUGINS target_name)
    POST_BUILD_COPY(${target_name} 
      SUBDIR VRPlugins/BSPlugins 
      ${ARGN})
ENDMACRO()

MACRO(VIRE_POST_BUILD_COPY_ACTORPLUGINS target_name)
  POST_BUILD_COPY(${target_name} 
        SUBDIR VRPlugins/ActorPlugins 
        ${ARGN})
ENDMACRO()
#=====================================================================================
#
#
#
#
#TARGET_TYPE 代表以输出目录为类型（BIN ACTORPLUGIN BSPLUGIN）
#
#
#
#
#=====================================================================================
MACRO(VIRE_SET_TARGET_V1 target_name)
    set(options)
    set(oneValueArgs TARGET_TYPE PRJ_DIR)
    set(multiValueArgs )

    cmake_parse_arguments(${target_name} 
        "${options}" 
        "${oneValueArgs}" 
        "${multiValueArgs}" 
        ${ARGN})

    #======================设置解决方案工程属性===========================
    IF(x${${target_name}_PRJ_DIR} STREQUAL "x")
        SET(${target_name}_PRJ_DIR "_NoGroupProj")
    ENDIF()
    VIRE_SET_TARGET_PROPERTIES_LABEL_FOLDER(${target_name} ${${target_name}_PRJ_DIR} ${ARGN})

    COMMON_CHECK_DEBUG_MSG(
        "  -->${target_name} Call Macro Set Target Properties With Target Type = ${${target_name}_TARGET_TYPE}"
        ${ARGN})

    SET(_bMatched FALSE)
    #======================BIN=============================
    IF(x${${target_name}_TARGET_TYPE} STREQUAL "xBIN")
        #输出到上级目录，取消debug, release 目录
        VIRE_SET_TARGET_PROPERTIES_OUTPUT_NORMAL(${target_name})

        #Release自动拷贝文件到目录
        VIRE_POST_BUILD_COPY(${target_name} ${ARGN})

        SET(_bMatched TRUE)
    ENDIF()

    #======================BSPLUGIN=============================
    IF(x${${target_name}_TARGET_TYPE} STREQUAL "xBSPLUGIN")
        #输出到上级目录，取消debug, release 目录
        VIRE_SET_TARGET_PROPERTIES_OUTPUT_FOR_BSPLUGIN(${target_name})

        #Release自动拷贝文件到目录
        VIRE_POST_BUILD_COPY_BSPLUGINS(${target_name})

        SET(_bMatched TRUE)
    ENDIF()

    #======================ACTORPLUGIN=============================
    IF(x${${target_name}_TARGET_TYPE} STREQUAL "xACTORPLUGIN")
        #输出到上级目录，取消debug, release 目录
        VIRE_SET_TARGET_PROPERTIES_OUTPUT_FOR_ACTORPLUGIN(${target_name})

        #Release自动拷贝文件到目录
        VIRE_POST_BUILD_COPY_ACTORPLUGINS(${target_name})

        SET(_bMatched TRUE)
    ENDIF()

    IF(NOT _bMatched)
        MESSAGE(FATAL_ERROR "Not Support Other Type Of ${${target_name}_TARGET_TYPE}...")
    ENDIF()
ENDMACRO()

MACRO(VIRE_SET_TARGET target_name)
    set(options)
    set(oneValueArgs VERSION)
    set(multiValueArgs )

    cmake_parse_arguments(${target_name} 
        "${options}" 
        "${oneValueArgs}" 
        "${multiValueArgs}" 
        ${ARGN})


    IF(x${${target_name}_VERSION} STREQUAL "xV1")
        #MESSAGE(STATUS "VIRE_SET_TARGET_V1...")
        VIRE_SET_TARGET_V1(${target_name} ${ARGN})
    ENDIF()
   
ENDMACRO()



#=====================================================================================
#*****************************************************************************
#此宏集合主要用于设计工程属性和输出属性、POST_BUILD属性
#     eg.VIRE_SET_TARGET_BIN(${target_name})
#     eg.VIRE_SET_TARGET_BIN(${target_name} PRJ_DIR "_app")
#以下的几个宏使用都可以以上用法使用
#*****************************************************************************
MACRO(VIRE_SET_TARGET_BIN target_name proj_folder)
    VIRE_SET_TARGET(
      ${target_name} 
      PRJ_DIR ${proj_folder} 
      VERSION V1 
      TARGET_TYPE BIN  
      ${ARGN}
    )
ENDMACRO()

MACRO(VIRE_SET_TARGET_BIN_EXE target_name proj_folder)
    VIRE_SET_TARGET(
      ${target_name} 
      PRJ_DIR ${proj_folder} 
      VERSION V1 
      TARGET_TYPE BIN  
      EXE
      ${ARGN}
    )
ENDMACRO()

MACRO(VIRE_SET_TARGET_BSPLUGIN target_name proj_folder)
    VIRE_SET_TARGET(
      ${target_name} 
      PRJ_DIR ${proj_folder} 
      VERSION V1 
      TARGET_TYPE BSPLUGIN 
      ${ARGN}
    )
ENDMACRO()

MACRO(VIRE_SET_TARGET_ACTORPLUGIN target_name proj_folder)
    VIRE_SET_TARGET(
      ${target_name} 
      PRJ_DIR ${proj_folder}
      VERSION V1 
      TARGET_TYPE ACTORPLUGIN
      ${ARGN}
    )
ENDMACRO()
#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================#=======================================================================================


