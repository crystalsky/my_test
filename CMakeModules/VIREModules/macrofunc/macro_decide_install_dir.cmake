function(_DECIDE_DIR _libName _out_lib_dir _out_bin_dir)
    SET(options )
    SET(oneValueArgs )
    SET(multiValueArgs )
        
    cmake_parse_arguments(${_libName} 
      "${options}" 
      "${oneValueArgs}" 
      "${multiValueArgs}" 
      ${ARGN})

    SET(_dir_name_lib lib)
    SET(_dir_name_bin bin)
    IF(MSVC)
        IF(MSVC80)#vs2005
            SET(_dir_name_lib lib/vc80)
            SET(_dir_name_bin bin/vc80)
        ELSEIF(MSVC90)#vs2008
            SET(_dir_name_lib lib/vc90)
            SET(_dir_name_bin bin/vc90)
        ELSEIF(MSVC10)#vs2010
            SET(_dir_name_lib lib/vc100)
            SET(_dir_name_bin bin/vc100)
        ELSEIF(MSVC12)#vs2013
            SET(_dir_name_lib lib/vc120)
            SET(_dir_name_bin bin/vc120)
        ELSEIF(MSVC14)#vs2015
            SET(_dir_name_lib lib/vc140)
            SET(_dir_name_bin bin/vc140)
        ELSE()#vs2012
          #default MSVC11 Is In Lib Folder
            SET(_dir_name_lib lib)
            SET(_dir_name_bin bin)
        ENDIF()
    ELSE()

    ENDIF()

    IF(CMAKE_CL_64)
        SET(${_out_lib_dir} ${_dir_name_lib}/x64 PARENT_SCOPE)
        SET(${_out_bin_dir} ${_dir_name_bin}/x64 PARENT_SCOPE)
    ELSE(CMAKE_CL_64)
        SET(${_out_lib_dir} ${_dir_name_lib} PARENT_SCOPE)
        SET(${_out_bin_dir} ${_dir_name_bin} PARENT_SCOPE)
    ENDIF(CMAKE_CL_64)
endfunction()

MACRO(BEGIN_INSTALL _libname)
    INSTALL(CODE "MESSAGE(\"====Installing Lib ${_libname} To ${CMAKE_INSTALL_PREFIX}/${_libname}====\")")
ENDMACRO()

MACRO(END_INSTALL _libname)
    INSTALL(CODE "MESSAGE(\"==========Installing Lib ${_libname} Finish==========\")")
ENDMACRO()

MACRO(DECIDE_INSTALL_DIR _libName)
    set(options FRAMEWORK_MODE)#是否是框架安装,如果不是框架的安装方式，就以独立库的方式安装处理
    set(oneValueArgs INCLUDE_ADD_DIR)#增加的包含目录处理 ： include/${dir}/&{libname}
    set(multiValueArgs PATHS)
      
    cmake_parse_arguments(${_libName} 
        "${options}" 
        "${oneValueArgs}" 
        "${multiValueArgs}" 
        ${ARGN})

    if(NOT ${_libName}_FRAMEWORK_MODE)
        MESSAGE(STATUS "Install The ${_libName}, SingleInstall Mode...")
        set(${_libName}_lib_dir )
        set(${_libName}_bin_dir )
        _DECIDE_DIR(
            ${_libName} 
            ${_libName}_lib_dir
            ${_libName}_bin_dir
        )
        set(${_libName}_INSTALL_HEADER  ${_libName}/include)
        set(${_libName}_INSTALL_RUNTIME ${_libName}/${${_libName}_bin_dir})
        set(${_libName}_INSTALL_LIBRARY ${_libName}/${${_libName}_lib_dir})
        set(${_libName}_INSTALL_ARCHIVE ${_libName}/${${_libName}_lib_dir})
    else()
        MESSAGE(STATUS "Install The ${_libName}, Framework Install Mode...")
        if(NOT ${_libName}_INCLUDE_ADD_DIR)
            message(FATAL_ERROR "   You Must Input The INCLUDE_ADD_DIR Val in Framework Install Mode...")
        endif()
        set(${_libName}_lib_dir )
        set(${_libName}_bin_dir )
        _DECIDE_DIR(
            ${_libName} 
            ${_libName}_lib_dir
            ${_libName}_bin_dir
        )
        set(${_libName}_INSTALL_HEADER  include/${${_libName}_INCLUDE_ADD_DIR}/${_libName})
        set(${_libName}_INSTALL_RUNTIME ${${_libName}_bin_dir})
        set(${_libName}_INSTALL_LIBRARY ${${_libName}_lib_dir})
        set(${_libName}_INSTALL_ARCHIVE ${${_libName}_lib_dir})
    endif()

    MESSAGE(STATUS "${_libName}_INSTALL_HEADER = ${${_libName}_INSTALL_HEADER}")
    MESSAGE(STATUS "${_libName}_INSTALL_RUNTIME = ${${_libName}_INSTALL_RUNTIME}")
    MESSAGE(STATUS "${_libName}_INSTALL_LIBRARY = ${${_libName}_INSTALL_LIBRARY}")
    MESSAGE(STATUS "${_libName}_INSTALL_ARCHIVE = ${${_libName}_INSTALL_ARCHIVE}")
ENDMACRO()

macro(INSTALL_WITH_PDB_FILE target_name)
    IF(CMAKE_C_FLAGS_DEBUG AND VRFramework_Install_With_PDB_File)
      GET_PROPERTY(${target_name}_OUT_PUT_DIR TARGET ${target_name} PROPERTY RUNTIME_OUTPUT_DIRECTORY_DEBUG)
        SET(${target_name}_PDB_FILE ${${target_name}_OUT_PUT_DIR}/${target_name}${CMAKE_DEBUG_POSTFIX}.pdb)
        IF(EXISTS ${${target_name}_PDB_FILE})
            MESSAGE(STATUS "Find ${target_name} PDB File: ${${target_name}_PDB_FILE}")
            INSTALL(
                FILES ${${target_name}_PDB_FILE} 
                DESTINATION ${${target_name}_INSTALL_RUNTIME} 
                COMPONENT Development
            )
        ELSE()
            MESSAGE(WARNING "No Find ${target_name} PDB File...")
        ENDIF()
    ENDIF()
endmacro()

macro(PACKAGE_WITH_PDB_FILE target_name)
    INSTALL_WITH_PDB_FILE(${target_name})
endmacro()