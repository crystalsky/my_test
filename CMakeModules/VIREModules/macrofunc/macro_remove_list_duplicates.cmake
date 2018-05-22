function(remove_list_duplicates lst)
    set(_my_list ${${lst}})
    #MESSAGE(STATUS "  -->before:remove_list_duplicates:${_my_list}")

    list(LENGTH _my_list _lst_count)
    #MESSAGE(STATUS "  -->_lst_count ${_lst_count}")

    IF(${_lst_count} STRGREATER 0)
        LIST(REMOVE_DUPLICATES _my_list)
    ENDIF()

    #MESSAGE(STATUS "  -->after:remove_list_duplicates:${_my_list}")
    set(${lst} ${_my_list} PARENT_SCOPE)

endfunction(remove_list_duplicates)