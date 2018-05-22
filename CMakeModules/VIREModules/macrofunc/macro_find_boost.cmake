MACRO(Find_Boost)
    #===================================================================
    SET(options USE_STATIC_LIBS USE_MULTITHREADED USE_STATIC_RUNTIME DEBUG_OUTPUT)
    SET(oneValueArgs BOOST_PATH)
    SET(multiValueArgs BOOST_COMPONENTS)
    
    cmake_parse_arguments(_boost_arg 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})
    MESSAGE(STATUS "  -->Prepare Boost Depends...")
    if(EXISTS ${_boost_arg_BOOST_PATH})
        SET_DEPENDS_DIR(BOOST   ${_boost_arg_BOOST_PATH})
        MESSAGE(STATUS "    -->BOOST_PATH: ${_boost_arg_BOOST_PATH}")
    else()
        if(EXISTS $ENV{BOOST_ROOT})
            COMMON_GET_ENV(_BOOST_ROOT BOOST_ROOT)
            MESSAGE(STATUS "    -->Default Boost Path In SystemEnv: $ENV{BOOST_ROOT}")
            SET(BOOST_ROOT ${_BOOST_ROOT})
        elseif(EXISTS "${THIRD_PART_ROOT}/boost_1_57_0")
            MESSAGE(STATUS "    -->Default Boost Path: ${THIRD_PART_ROOT}/boost_1_57_0")
            SET_DEPENDS_DIR(BOOST   "${THIRD_PART_ROOT}/boost_1_57_0") 
        else()
            MESSAGE(FATAL_ERROR "    -->No Boost Path Find, You Must Assign The BOOST_PATH Param By YourSelf!")        
        endif()
    endif()
    
    #use static lib
    if(NOT _boost_arg_USE_STATIC_LIBS)
        MESSAGE(STATUS "    -->Defautl Boost_USE_STATIC_LIBS: ON")
        SET(Boost_USE_STATIC_LIBS        ON)
    else()
        MESSAGE(STATUS "    -->Set Boost_USE_STATIC_LIBS: ${_boost_arg_USE_STATIC_LIBS}")
        SET(Boost_USE_STATIC_LIBS        ${_boost_arg_USE_STATIC_LIBS})
    endif()

    #multithreaded
    if(NOT _boost_arg_USE_MULTITHREADED)
        MESSAGE(STATUS "    -->Defautl Boost_USE_MULTITHREADED: ON")
        SET(Boost_USE_MULTITHREADED        ON)
    else()
        MESSAGE(STATUS "    -->Set Boost_USE_MULTITHREADED: ${_boost_arg_USE_MULTITHREADED}")
        SET(Boost_USE_MULTITHREADED        ${_boost_arg_USE_MULTITHREADED})
    endif()

    #use_static_runtime
    if(NOT _boost_arg_USE_STATIC_RUNTIME)
        MESSAGE(STATUS "    -->Defautl Boost_USE_STATIC_RUNTIME: ON")
        SET(Boost_USE_STATIC_RUNTIME       OFF)
    else()
        MESSAGE(STATUS "    -->Set Boost_USE_STATIC_RUNTIME: ${_boost_arg_USE_STATIC_RUNTIME}")
        SET(Boost_USE_STATIC_RUNTIME        ${_boost_arg_USE_STATIC_RUNTIME})
    endif()

    #debug_output
    if(NOT _boost_arg_DEBUG_OUTPUT)
        MESSAGE(STATUS "    -->Defautl Boost_DEBUG: OFF")
        SET(Boost_DEBUG       OFF)
    else()
        MESSAGE(STATUS "    -->Set Boost_DEBUG: ${_boost_arg_DEBUG_OUTPUT}")
        SET(Boost_DEBUG        ${_boost_arg_DEBUG_OUTPUT})
    endif()
    #===================================================================
    SET(Boost_NO_BOOST_CMAKE        OFF)
    #SET(Boost_DEBUG TRUE)

    SET(BOOST_INCLUDEDIR ${BOOST_ROOT}/include)
    # IF(MSVC11)
    #     SET(BOOST_LIBRARYDIR "$ENV{BOOST_ROOT}/lib32-msvc-11.0")
    # ELSE(MSVC11)
    #     SET(BOOST_LIBRARYDIR "$ENV{BOOST_ROOT}/lib32-msvc-12.0")
    # ENDIF(MSVC11)
    
    #MESSAGE("-------BOOST_ROOT===$ENV{BOOST_ROOT}")
    #MESSAGE("-------BOOST_LIBRARYDIR===${BOOST_LIBRARYDIR}")


    FIND_PACKAGE(Boost 1.57.0 REQUIRED COMPONENTS ${_boost_arg_BOOST_COMPONENTS})


    if(EXISTS ${Boost_INCLUDE_DIR})
        set(BOOST_INCLUDE_DIR ${Boost_INCLUDE_DIR})
    endif()
ENDMACRO()

MACRO(Boost_Support)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
ENDMACRO()