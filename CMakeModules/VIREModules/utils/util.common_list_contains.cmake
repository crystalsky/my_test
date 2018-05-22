#check the argn contains the value, the output is ${val}
MACRO(COMMON_LIST_CONTAINS is_contain value)
  SET(${is_contain})
  FOREACH (temp ${ARGN})
    IF(${value} STREQUAL ${temp})
      SET(${is_contain} TRUE)
    ENDIF()
  ENDFOREACH ()
ENDMACRO()