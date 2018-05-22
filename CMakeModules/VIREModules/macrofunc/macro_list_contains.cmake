######### LIST_CONTAINS usage
#SET(MYLIST hello world foo bar)

#LIST_CONTAINS(contains foo ${MYLIST})
#IF (contains)
#  MESSAGE("MYLIST contains foo")
#ENDIF (contains)

#LIST_CONTAINS(contains baz ${MYLIST})
#IF (NOT contains)
#  MESSAGE("MYLIST does not contain baz")
#ENDIF (NOT contains)


MACRO(LIST_CONTAINS var value)
  SET(${var})
  FOREACH (value2 ${ARGN})
    IF (${value} STREQUAL ${value2})
      SET(${var} TRUE)
    ENDIF ()
  ENDFOREACH ()
ENDMACRO()