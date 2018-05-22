MACRO(VERSIONED_TARGET_BASE _targetName _MajorVersion _MinorVersion _PatchVersion _SOVersion)
	SET(_Taget_ ${_targetName})
    SET(${_Taget_}_MajorVersion     ${_MajorVersion})
    SET(${_Taget_}_MinorVersion     ${_MinorVersion})
    SET(${_Taget_}_PatchVersion     ${_PatchVersion})
    SET(${_Taget_}_SOVersion        ${_SOVersion})

	#parse the arguments
	SET(options TARGET_VERSION)
    SET(oneValueArgs HeadName CompanyName FileDescription InternalName LegalCopyright OriginalFilename ProductName)
    SET(multiValueArgs )
    
    cmake_parse_arguments(${_Taget_}
        "${options}" 
        "${oneValueArgs}" 
        "${multiValueArgs}" 
        ${ARGN}
    )

    if(${_Taget_}_TARGET_VERSION)
        _add_target_version_properties(${_targetName} ${_MajorVersion} ${_MinorVersion} ${_PatchVersion} ${ARGN})
    endif()

    if(NOT ${_Taget_}_CompanyName)
        SET(${_Taget_}_CompanyName "Versioned ${_Taget_}")
    endif()

    if(NOT ${_Taget_}_FileDescription)
        SET(${_Taget_}_FileDescription "Versioned ${_Taget_}")
    endif()

    if(NOT ${_Taget_}_InternalName)
        SET(${_Taget_}_InternalName "Versioned ${_Taget_}")
    endif()

    if(NOT ${_Taget_}_LegalCopyright)
        SET(${_Taget_}_LegalCopyright "Copyright Versioned ${_Taget_}")
    endif()

    if(NOT ${_Taget_}_OriginalFilename)
        SET(${_Taget_}_OriginalFilename "Versioned ${_Taget_} Library")
    endif()

    if(NOT ${_Taget_}_ProductName)
        SET(${_Taget_}_ProductName "Versioned ${_Taget_}")
    endif()

    #version string
    SET(_TARGET_VERSION  
        ${${_Taget_}_MajorVersion}.${${_Taget_}_MinorVersion}.${${_Taget_}_PatchVersion}.${${_Taget_}_SOVersion})
    
    MESSAGE(STATUS "-->Versioned The Target:->${_Taget_}<-With Version->${_TARGET_VERSION}<--")
    SET(VERSIONED_LIB_RC "${CMAKE_CURRENT_BINARY_DIR}/${_Taget_}_Version.rc")
    
    #configure the version rc file to binary folder
    IF(WIN32)
        CONFIGURE_FILE("${THIS_MODULE_RESOURCE_PATH}/TargetVersionBase.rc.in" "${VERSIONED_LIB_RC}")
        #CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/CMakeModules/resource/TargetVersionBase.rc.in" "${VERSIONED_LIB_RC}")
    ELSE(WIN32)
        MESSAGE(WARNING "Not Support Besides W32, You Should Modify This Macro ByYourself!!")
    ENDIF(WIN32)

    DEBUG_MESSAGE("===VERSIONED_LIB_RC===(File : ${VERSIONED_LIB_RC})")
    SET(${_target_}_VERSIONED_LIB_RC ${VERSIONED_LIB_RC})


    COMMON_CHECK_DEBUG(_isDebug ${ARGN})
    if(_isDebug)
        COMMON_PRINT_PROPERTIES(
            TARGETS ${_targetName}::TARGET_VERSION 
            PROPERTIES
                TARGET_VERSION
                TARGET_VERSION_MAJOR
                TARGET_VERSION_MINOR
                TARGET_VERSION_PATCH
        )  
    endif()
ENDMACRO()


function(_add_target_version_properties target_name _MajorVersion _MinorVersion _PatchVersion)
    
    set(_version_target_name "${target_name}::TARGET_VERSION")
    
    if(NOT TARGET ${_version_target_name})
        add_library(${_version_target_name} SHARED IMPORTED)
    endif()

    set_target_properties(${_version_target_name} PROPERTIES
        "TARGET_VERSION" "${_MajorVersion}.${_MinorVersion}.${_PatchVersion}"
    ) 

    set_target_properties(${_version_target_name} PROPERTIES
        "TARGET_VERSION_MAJOR" ${_MajorVersion}
    )  
    set_target_properties(${_version_target_name} PROPERTIES
        "TARGET_VERSION_MINOR" ${_MinorVersion}
    ) 
    set_target_properties(${_version_target_name} PROPERTIES
        "TARGET_VERSION_PATCH" ${_PatchVersion}
    )
endfunction()
