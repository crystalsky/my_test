get_filename_component(THIS_DIR_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
SET(THIS_FOLDER_NAME ${THIS_FOLDER_NAME}/${THIS_DIR_NAME})

_ADD_SUBDIR_IN_FOLDER(${CMAKE_CURRENT_LIST_DIR})
