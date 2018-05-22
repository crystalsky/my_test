#搜索可能的三方库目录
include(macro_debug_message)
include(macro_upper_list_string)
include(macro_remove_list_duplicates)
include(macro_find_boost)

function(_get_local_3rd_dir_in In_Path Out_Path)
	if(NOT EXISTS ${In_Path})
		MESSAGE(FATAL_ERROR "The Invalide Path ${In_Path}")
	endif()

	#要搜索的目录
	SET(_local_3rd_dirs_name 3rdPart 3rdParty ThirdPart ThirdParty)
	
	#分别搜当前目录和上一层的目录下的可能的三方库目录
	foreach(_dirname_ ${_local_3rd_dirs_name})
		#当前目录
		DEBUG_MESSAGE("  -->Find 3rdparth at: " \"${In_Path}/${_dirname_}\")
		IF(EXISTS ${In_Path}/${_dirname_})
			SET(${Out_Path} ${In_Path}/${_dirname_} PARENT_SCOPE)
			return()
		else()
			#上一层的目录
			GET_FILENAME_COMPONENT(_parent_dir ${In_Path} PATH)
			IF(EXISTS ${_parent_dir}/${_dirname_})
				SET(${Out_Path} ${_parent_dir}/${_dirname_} PARENT_SCOPE)
				return()
			ENDIF()
		ENDIF()
	endforeach()
endfunction(_get_local_3rd_dir_in)

#获取本地三方库目录
function(GET_LOCAL_THRIDPART_ROOT_DIR _dir)
	_get_local_3rd_dir_in(${PROJECT_SOURCE_DIR} _tmpDir)

	SET(${_dir} ${_tmpDir} PARENT_SCOPE)
endfunction()

function(_Defualt_Search_3rdParty_Process _out_dir)
	
	#MESSAGE( STATUS "Will Be Searching Dirctory By Defualt Process..." )
	_get_local_3rd_dir_in(${PROJECT_SOURCE_DIR} _3rdPartyDir_)
	
	IF(NOT EXISTS ${_3rdPartyDir_})
		#先查找当前工程 ${PROJECT_SOURCE_DIR}上一级目录下ThirdPart
		MESSAGE(STATUS "  -->Step1 : It Will Be Searching ThirdPart Dirctory In Environment Variable..." )
		IF(EXISTS $ENV{THIRD_PARTY_ROOT})
			SET(_3rdPartyDir_ $ENV{THIRD_PARTY_ROOT})		
			MESSAGE( STATUS "  -->Step2 : ThirdPart Dirctory In Eevironment THIRD_PARTY_ROOT: Yes!!!" )
		ELSE()
			MESSAGE( STATUS "  -->Step2 : ThirdPart Dirctory In Eevironment THIRD_PARTY_ROOT: NO!!!" )
		ENDIF()
	ELSE()
		MESSAGE( STATUS "  -->By Defualt Process...Find The ThirdPart Dirctory ${_3rdPartyDir_}" )
	ENDIF()
	
	SET(${_out_dir} ${_3rdPartyDir_} PARENT_SCOPE)
endfunction(_Defualt_Search_3rdParty_Process)



#判断有没有提提前预设定Direcory路径
MACRO(_CONFIRM_THIRD_PART_PATH _path)
	IF(NOT EXISTS ${_path})
		MESSAGE( STATUS "  -->You Hasn't Set The PATH Value, Will Be Searching Dirctory By Defualt Process..." )
	
		_Defualt_Search_3rdParty_Process(_findpath)

		#UNSET(_3RDPARTY_DIR CACHE)
		SET(_3RDPARTY_DIR ${_findpath})
		
		IF(NOT EXISTS ${_3RDPARTY_DIR})
			SET(_3RDPARTY_DIR ${_3RDPARTY_DIR} CACHE PATH "Seting The 3RD_Party Dir Of The Project By Yourself!!!")
		ENDIF()

		IF(NOT EXISTS ${_3RDPARTY_DIR})
			MESSAGE(FATAL_ERROR "There Is No _3RDPARTY_DIR With : ${_3RDPARTY_DIR}, You Must Set The _3RDPARTY_DIR On CMake UI By Yourself!!!!")
		ENDIF()
	ELSE()
		#UNSET(_3RDPARTY_DIR CACHE)
		SET(_3RDPARTY_DIR ${_path})
		
		IF(NOT EXISTS ${_3RDPARTY_DIR})
			SET(_3RDPARTY_DIR ${_3RDPARTY_DIR} CACHE PATH "Seting The 3RD_Party Dir Of The Project By Yourself!!!")
		ENDIF()

		IF(NOT EXISTS ${_3RDPARTY_DIR})
			MESSAGE(FATAL_ERROR "There Is No _3RDPARTY_DIR With : ${_3RDPARTY_DIR}, You Must Set The _3RDPARTY_DIR On CMake UI By Yourself!!!!")
		ENDIF()	
	ENDIF()

	SET(ACTUAL_3DPARTY_DIR "${_3RDPARTY_DIR}")
	SET(THIRD_PART_PATH ${ACTUAL_3DPARTY_DIR})
ENDMACRO()
#=========================三方依赖路径===========================
MACRO(OPTION_DEPENDS_NAME name on_off)
	OPTION(AFIND_Depends_${name} "Enalbe Find Depends of ${name}" ${on_off})
ENDMACRO()

MACRO(_FIND_PACKAGE_DEPENDS _in_depends)
	
	set(_this_list_depends ${${_in_depends}})
	#MESSAGE(STATUS "  -->SETTING_UP_DEPENDS:->${_this_list_depends}<-")
	
	MESSAGE( STATUS "-->==============================Begin FindPackage=============================<--" )
	
	foreach(_Depends_Lib_Name ${_this_list_depends})
		#OPTION_DEPENDS_NAME(${_Depends_Lib_Name} ON)
		
	#if(DIR3RD_${_Depends_Lib_Name})
		SET(3RDDependDirOf_${_Depends_Lib_Name}_ROOT $ENV{${_Depends_Lib_Name}_ROOT} CACHE STRING "Dir of the depends!")
		mark_as_advanced(3RDDependDir_OF_${_Depends_Lib_Name})
		mark_as_advanced(3RDDependDir_OF_${_Depends_Lib_Name}_ROOT)
	
		MESSAGE(STATUS "  @FIND_PACKAGE [${_Depends_Lib_Name}] In Dir [${${_Depends_Lib_Name}_ROOT}]...")	
		IF(NOT EXISTS ${${_Depends_Lib_Name}_ROOT})
			MESSAGE(FATAL_ERROR "  No 3RD Depends Directory Of ${_Depends_Lib_Name}")
		ENDIF()
		
		FIND_PACKAGE(${_Depends_Lib_Name} REQUIRED)
		#endif()
	endforeach()
	
	MESSAGE( STATUS "-->===============================End FindPackage==============================<--" )
ENDMACRO()

