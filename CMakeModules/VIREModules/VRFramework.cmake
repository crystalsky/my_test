MACRO(_use_module_libs target_name module_type)
    SET(list_moudoules ${ARGN})
    #message(STATUS "      ${target_name} Use ${module_type}: ${list_moudoules}")
    
    list(LENGTH list_moudoules _lstLen)
    IF(_lstLen)
        message(STATUS "      ${target_name} Include Dir: ${VRFRAMEWORK_${module_type}_INCLUDE_DIR}")
        INCLUDE_DIRECTORIES(${VRFRAMEWORK_${module_type}_INCLUDE_DIR})
    ENDIF()

    foreach(val ${list_moudoules})
        string(TOUPPER ${val} m_name)
        INCLUDE_DIRECTORIES(${VRFRAMEWORK_${module_type}_${m_name}_INCLUDE_DIR})

        IF(VRFRAMEWORK_${module_type}_${m_name}_LIBRARY AND 
            VRFRAMEWORK_${module_type}_${m_name}_LIBRARY_DEBUG)
            #message(STATUS "        ${target_name} ${module_type} Has ${m_name} Debug And Release")
            #message(STATUS "          Rel:${VRFRAMEWORK_${module_type}_${m_name}_LIBRARY}  ")
            #message(STATUS "          Dbg:${VRFRAMEWORK_${module_type}_${m_name}_LIBRARY_DEBUG}")
           
            TARGET_LINK_LIBRARIES(${target_name} 
                optimized "${VRFRAMEWORK_${module_type}_${m_name}_LIBRARY}" 
                debug "${VRFRAMEWORK_${module_type}_${m_name}_LIBRARY_DEBUG}"
            )
        ELSEIF(VRFRAMEWORK_${module_type}_${m_name}_LIBRARY AND 
            NOT VRFRAMEWORK_${module_type}_${m_name}_LIBRARY_DEBUG)
            message(STATUS "        ${target_name} ${module_type} No Debug Lib ${m_name},Use Release Lib!")
            TARGET_LINK_LIBRARIES(${target_name} 
                optimized "${VRFRAMEWORK_${module_type}_${m_name}_LIBRARY}" 
                debug "${VRFRAMEWORK_${module_type}_${m_name}_LIBRARY_DEBUG}"
            )
        ELSE()
            message(FATAL_ERROR "      ${target_name} ${module_type} No Libs ${m_name} To Use!")  
        ENDIF()
    endforeach()
ENDMACRO()
#============================================================================================
MACRO(VRFramework_Init)
    MESSAGE(STATUS "\n======>Use VRFramework_Init Begin...")
    #===================================================================
    SET(options )
    SET(oneValueArgs PATH)
    SET(multiValueArgs)
    
    cmake_parse_arguments(VRFRAMEWORK
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    #===================================================================
    IF(NOT EXISTS ${VRFRAMEWORK_PATH})
        SET(_VR_DIR $ENV{VRFRAMEWORK_ROOT})
    ELSE()
        MESSAGE(STATUS "The VRFramework Dir: ${VRFRAMEWORK_PATH}")
        SET(_VR_DIR ${VRFRAMEWORK_PATH})
    ENDIF()
    
    MESSAGE(STATUS "_VR_DIR: ${_VR_DIR}")
    UNSET(VRFRAMEWORK_DIR CACHE)
    SET(VRFRAMEWORK_DIR ${_VR_DIR} CACHE PATH "Setting The VRFRAMEWORK Dir Of The Project By Yourself!!!" FORCE)
	
    IF(NOT EXISTS ${VRFRAMEWORK_DIR})
        MESSAGE(FATAL_ERROR "You Must Config ENV VRFRAMEWORK_ROOT Where The VRFramework Dir...")
    ELSE()
        MESSAGE(STATUS "  The VRFramework Dir At: ${VRFRAMEWORK_DIR}")
    ENDIF()
   
    #===================================================================
    FIND_PACKAGE(VRFramework REQUIRED)
    #===================================================================
    MESSAGE(STATUS "======>VRFramework_Init Finish!\n")
ENDMACRO()

MACRO(VRFramework_Use_Modules target_name)
    MESSAGE(STATUS "  ======>${target_name} VRFramework_Use_Modules Begin....")
    #===================================================================
    SET(options )
    SET(oneValueArgs)
    SET(multiValueArgs VRBASE VRCORE VRTOOLS)
    
    cmake_parse_arguments(USE
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})

    #===================================================================
    IF(USE_VRBASE)
        message(STATUS "    ${target_name} Use VRBASE Modouls: ${USE_VRBASE}...")
        _use_module_libs(${target_name} VRBASE ${USE_VRBASE})
    ENDIF()

    IF(USE_VRCORE)
        message(STATUS "    ${target_name} Use VRCORE Modouls: ${USE_VRCORE}...")
        _use_module_libs(${target_name} VRCORE ${USE_VRCORE})
    ENDIF()

    IF(USE_VRTOOLS)
        message(STATUS "    ${target_name} Use VRTOOLS Modouls: ${USE_VRTOOLS}...")
        _use_module_libs(${target_name} VRTOOLS ${USE_VRTOOLS})
    ENDIF()
    #===================================================================
    MESSAGE(STATUS "  ======>${target_name} VRFramework_Use_Modules Finish!")
ENDMACRO()