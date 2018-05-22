function(adapter_matching_library_variable new_libName _headname _outSubName)
    #MESSAGE(STATUS "${new_libName} ___ ${_headname}")
    string(TOUPPER ${new_libName} _UpperlibName)
    string(TOUPPER ${_headname} _UpperHeadName)

    #find the first index of _headname
    string(FIND ${_UpperlibName} ${_UpperHeadName} _indexofHead)

    IF(NOT ${_indexofHead} STREQUAL "-1")
        string(LENGTH ${_UpperlibName} _TotalLength)
        string(LENGTH ${_UpperHeadName} _headLenght)
        math(EXPR  _leftLenght "${_TotalLength} - ${_headLenght} + 1")
        math(EXPR  _headLenght "${_headLenght} + 1")
        #MESSAGE(STATUS "${_leftLenght}")
        string(SUBSTRING ${_UpperlibName} ${_headLenght} ${_leftLenght} _destVariable)  
        MESSAGE(STATUS "SUBSTRING===${_destVariable}")
        SET(${_outSubName} ${_destVariable} PARENT_SCOPE)
        set(${${_outSubName}} ${${_UpperlibName}} PARENT_SCOPE)   
       
    ENDIF()
endfunction()

