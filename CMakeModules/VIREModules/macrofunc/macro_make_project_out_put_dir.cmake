MACRO(MAKE_PROJECT_OUT_PUT_DIR path)
  IF(NOT EXISTS ${path})
    SET(path ${PROJECT_SOURCE_DIR})
    MAKE_DIRECTORY(${path})
  ENDIF()
  
  OPTION(${ProjectVal_PREFIX_OUT_PUT}_Binary_Dir OFF "Make The Output Dir in CMake Binary Dir.")

  if(NOT ${ProjectVal_PREFIX_OUT_PUT}_Binary_Dir)
    SET(${ProjectVal_PREFIX_OUT_PUT}_ROOT_DIR ${path} 
      CACHE PATH 
        "The Default OutPutDir Root,The Binaray Files Will In The Dir/Bin/Debug Or Relase Dir....")
  else()
    SET(${ProjectVal_PREFIX_OUT_PUT}_ROOT_DIR ${CMAKE_BINARY_DIR} 
      CACHE PATH 
      "The Default OutPutDir Root,The Binaray Files Will In The Dir/Bin/Debug Or Relase Dir....")
  endif()
  mark_as_advanced(${ProjectVal_PREFIX_OUT_PUT}_ROOT_DIR)

  #make the same output directory of debug and release,
  OPTION(${ProjectVal_PREFIX_OUT_PUT}_Binary_Same_Dir OFF 
  "Make the same output directory of debug and release.")
  unset(_Binary_In_Same_Dir)
  SET(_Binary_In_Same_Dir ${${ProjectVal_PREFIX_OUT_PUT}_Binary_Same_Dir})

  #bin(*.dll)
  unset(${ProjectVal_PREFIX_OUT_PUT}_BIN_DIR)
  SET(${ProjectVal_PREFIX_OUT_PUT}_BIN_DIR ${${ProjectVal_PREFIX_OUT_PUT}_ROOT_DIR}/bin)
  
  string(REPLACE "//" "/" 
      ${ProjectVal_PREFIX_OUT_PUT}_BIN_DIR
      ${${ProjectVal_PREFIX_OUT_PUT}_BIN_DIR}
  )
  message(STATUS ${ProjectVal_PREFIX_OUT_PUT}_BIN_DIR = ${${ProjectVal_PREFIX_OUT_PUT}_BIN_DIR})
  MAKE_DIRECTORY(${${ProjectVal_PREFIX_OUT_PUT}_BIN_DIR})
  mark_as_advanced(${ProjectVal_PREFIX_OUT_PUT}_BIN_DIR)

  #lib
  unset(${ProjectVal_PREFIX_OUT_PUT}_LIB_DIR)
  SET(${ProjectVal_PREFIX_OUT_PUT}_LIB_DIR ${${ProjectVal_PREFIX_OUT_PUT}_ROOT_DIR}/lib)
  string(REPLACE "//" "/" 
      ${ProjectVal_PREFIX_OUT_PUT}_LIB_DIR
      ${${ProjectVal_PREFIX_OUT_PUT}_LIB_DIR}
  )
  message(STATUS ${ProjectVal_PREFIX_OUT_PUT}_LIB_DIR = ${${ProjectVal_PREFIX_OUT_PUT}_LIB_DIR})
  MAKE_DIRECTORY(${${ProjectVal_PREFIX_OUT_PUT}_LIB_DIR})
  mark_as_advanced(${ProjectVal_PREFIX_OUT_PUT}_LIB_DIR)


  #Here to set the default runtime out put dir.....
  SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${${ProjectVal_PREFIX_OUT_PUT}_LIB_DIR})
  SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${${ProjectVal_PREFIX_OUT_PUT}_BIN_DIR})
  SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${${ProjectVal_PREFIX_OUT_PUT}_BIN_DIR})

  #MESSAGE(FATAL_ERROR "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
ENDMACRO()