SET(GTEST_LIBRARY       gtest)
SET(GTEST_MAIN_LIBRARY  gtest_main)
SET(GTEST_BOTH_LIBRARIES  gtest gtest_main)

SET(GTEST_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/gtest/include)
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})

SET( LIB_SOURCES_GTEST
    src/gtest-all.cc
)

SET( LIB_SOURCES_GTEST_MAIN
    src/gtest_main.cc
)
   
SET( LIB_PUBLIC_HEADERS
    include/gtest/gtest.h
   )
  

ADD_LIBRARY(${GTEST_LIBRARY} STATIC
    ${LIB_PUBLIC_HEADERS} 
    ${LIB_SOURCES_GTEST}
)

ADD_LIBRARY(${GTEST_MAIN_LIBRARY} STATIC
    ${LIB_PUBLIC_HEADERS} 
    ${LIB_SOURCES_GTEST_MAIN}
)

