function(common_upper_list_string lst)
    set(_my_list ${${lst}})
    #MESSAGE(STATUS "  -->before:upper_list_string:${_my_list}")

    set(_upper_list)
    foreach(_name ${_my_list})
        string(TOUPPER ${_name} _uppered_name)
        list(APPEND _upper_list ${_uppered_name})
    endforeach()

    #MESSAGE(STATUS "  -->after:upper_list_string:${_my_list}")
    set(${lst} ${_upper_list} PARENT_SCOPE)
endfunction()