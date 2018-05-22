MACRO(BEGIN_TARGET _target)
    MESSAGE("
-_-************************Setting ${_target}...**********************-_-")
ENDMACRO()

MACRO(END_TARGET _target)
    MESSAGE("^_^**********************Finish ${_target}...OK!**********************^_^
")
ENDMACRO()


MACRO(BEGIN_LIB libName)
  BEGIN_TARGET(${libName})
ENDMACRO(BEGIN_LIB libName)

MACRO(END_LIB libName)
  END_TARGET(${libName})
ENDMACRO(END_LIB libName)