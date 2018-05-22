FUNCTION(CONFIG_RUN_BATCH_FILE targetName)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs PATHS)
    cmake_parse_arguments(ConfigRunBat "${options}" "${oneValueArgs}"
                        "${multiValueArgs}" ${ARGN} )

    set(_path_lists "")

    MESSAGE(STATUS "============ConfigRunBat START============")

    set(outputDirPostFix "")
    if(EXISTS ${VRFRAMEWORK_DIR})
        if(CMAKE_CL_64)
            list(APPEND _path_lists ${VRFRAMEWORK_DIR}/bin/x64)
            set(outputDirPostFix "x64")
        elseif()
            list(APPEND _path_lists ${VRFRAMEWORK_DIR}/bin)
        endif()
    endif()

    if(EXISTS ${QT_DIR})
        list(APPEND _path_lists ${QT_DIR}/bin)
    endif()

    set(_extenal_paths ${ConfigRunBat_PATHS} ${ConfigRunBat_UNPARSED_ARGUMENTS})
    FOREACH(varname ${_extenal_paths})
        list(APPEND _path_lists ${varname})
    ENDFOREACH()

    set(_path_lists_str "")
    list(LENGTH _path_lists _path_lists_length)
    if(${_path_lists_length} EQUAL 0)
    else()
        foreach(path_elem IN LISTS  _path_lists)
            string(APPEND _path_lists_str "${path_elem}\\\;")
        endforeach()
    endif()

    if(NOT ${_path_lists_str} STREQUAL "")
        SET(_template_runbat_file ${THIS_MODULE_TEMPLATES_PATH}/ConfigRunBatchFile.in)
        if(EXISTS ${_template_runbat_file})
            SET(ADDON_PATH ${_path_lists_str})
            SET(RUN_EXE ${targetName})

            foreach(config DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)
                get_target_property(${targetName}_RUNTIME_DIR_${config} ${targetName} 
                    RUNTIME_OUTPUT_DIRECTORY_${config} 
                )
                IF(EXISTS ${${targetName}_RUNTIME_DIR_${config}})
                    CONFIGURE_FILE(${_template_runbat_file} ${${targetName}_RUNTIME_DIR_${config}}/${targetName}.bat)
                ENDIF()
            endforeach()
        endif()
    endif()

    MESSAGE(STATUS "============ConfigRunBat FINISH============")
ENDFUNCTION()
