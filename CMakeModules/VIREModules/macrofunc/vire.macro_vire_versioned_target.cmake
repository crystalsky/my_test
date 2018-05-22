include(macro_versioned_target_base)

MACRO(VIRE_VERSIONED_TARGET _targetName _MajorVersion _MinorVersion _PatchVersion _SOVersion)
    VERSIONED_TARGET_BASE(${_targetName}
        ${_MajorVersion}
        ${_MinorVersion}
        ${_PatchVersion}
        ${_SOVersion}
        CompanyName "Vire Technology"
        FileDescription "Vire ${_targetName} Binary"
        InternalName "Vire ${_targetName} Binary"
        LegalCopyright "Copyright Vire Technology"
        OriginalFilename "${_targetName} Library"
        ProductName "${_targetName}"
        TARGET_VERSION #defautl set target version ${_targetName}::TARGET_VERSION
        ${ARGN}
    )
ENDMACRO()

MACRO(VIRE_VERSIONED_LIB _targetName _MajorVersion _MinorVersion _PatchVersion _SOVersion)
    VIRE_VERSIONED_TARGET(
        ${_targetName}
        ${_MajorVersion}
        ${_MinorVersion}
        ${_PatchVersion}
        ${_SOVersion}
        ${ARGN}
    )
ENDMACRO()

MACRO(VERSIONED_LIB _targetName _MajorVersion _MinorVersion _PatchVersion _SOVersion)
    VIRE_VERSIONED_TARGET(
        ${_targetName}
        ${_MajorVersion}
        ${_MinorVersion}
        ${_PatchVersion}
        ${_SOVersion}
        ${ARGN}
    )
ENDMACRO()

MACRO(VERSIONED_TARGET _targetName _MajorVersion _MinorVersion _PatchVersion _SOVersion)

    SET(_Taget_ ${_targetName})
    SET(${_Taget_}_MajorVersion     ${_MajorVersion})
    SET(${_Taget_}_MinorVersion     ${_MinorVersion})
    SET(${_Taget_}_PatchVersion     ${_PatchVersion})
    SET(${_Taget_}_SOVersion        ${_SOVersion})
    
    SET(_TARGET_VERSION  
        ${${_Taget_}_MajorVersion}.${${_Taget_}_MinorVersion}.${${_Taget_}_PatchVersion}.${${_Taget_}_SOVersion})
    MESSAGE(STATUS "-->Versioned The Target:->${_Taget_}<-With Version->${_TARGET_VERSION}<--")
    SET(VERSIONED_LIB_RC "${CMAKE_CURRENT_BINARY_DIR}/${_Taget_}_Version.rc")
    
    IF(WIN32)
        CONFIGURE_FILE("${THIS_MODULE_RESOURCE_PATH}/TargetVersion.rc.in" "${VERSIONED_LIB_RC}")
    ELSE(WIN32)
        MESSAGE(WARNING "Not Support Besides W32, You Should Modify This Macro Byyouself!!")
    ENDIF(WIN32)

    DEBUG_MESSAGE("===VERSIONED_LIB_RC===(File : ${VERSIONED_LIB_RC})")
    
ENDMACRO()