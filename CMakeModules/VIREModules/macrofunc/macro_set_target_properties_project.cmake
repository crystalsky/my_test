#设置工程属性 'PROJECT_LABEL' 'FOLDER' 'VS_KEYWORD'
MACRO(SET_TARGET_PROPERTIES_PROJECT _Target)
  SET(options)
  SET(oneValueArgs PROJECT_LABEL_PREFIX QT_VS_KEYWORD PROJECT_FOLDER)
  SET(multiValueArgs)
  
  cmake_parse_arguments(${_Target} 
      "${options}" 
      "${oneValueArgs}" 
      "${multiValueArgs}" 
      ${ARGN})

  SET(${_Target}_LABLE ${_Target})
  IF(${_Target}_PROJECT_LABEL_PREFIX)
    STRING(CONCAT ${_Target}_LABLE ${${_Target}_PROJECT_LABEL_PREFIX} " " ${${_Target}_LABLE})
  ENDIF()

  #标签名
  SET_TARGET_PROPERTIES(${_Target} PROPERTIES PROJECT_LABEL ${${_Target}_LABLE})

  #解决方案目录
  IF(${_Target}_PROJECT_FOLDER)
    SET_TARGET_PROPERTIES(${_Target} PROPERTIES FOLDER ${${_Target}_PROJECT_FOLDER}) 
  ENDIF()

  IF(${_Target}_QT_VS_KEYWORD)
    # 设置与QT designer 集成
    SET_TARGET_PROPERTIES(${_Target} PROPERTIES VS_KEYWORD ${${_Target}_QT_VS_KEYWORD})
  ENDIF()

ENDMACRO(SET_TARGET_PROPERTIES_PROJECT _Target)