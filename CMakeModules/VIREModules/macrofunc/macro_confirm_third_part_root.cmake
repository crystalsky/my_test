function(_get_local_3rd_dir_in In_Path Out_Path)
	if(NOT EXISTS ${In_Path})
		MESSAGE(FATAL_ERROR "The Invalide Path ${In_Path}")
	endif()

	#要搜索的目录
	SET(_local_3rd_dirs_name 3rdPart 3rdParty ThirdPart ThirdParty)
	
	#分别搜当前目录和上一层的目录下的可能的三方库目录
	foreach(_dirname_ ${_local_3rd_dirs_name})
		#当前目录
		DEBUG_MESSAGE("    -->Find 3rdparth at: ${In_Path}/${_dirname_}")
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

function(_Defualt_Search_3rdParty_Process _out_dir)
	
	#MESSAGE( STATUS "Will Be Searching Dirctory By Defualt Process..." )
	_get_local_3rd_dir_in(${PROJECT_SOURCE_DIR} _3rdPartyDir_)
	
	IF(NOT EXISTS ${_3rdPartyDir_})
		#先查找当前工程 ${PROJECT_SOURCE_DIR}上一级目录下ThirdPart
		MESSAGE(STATUS "  -->Step1 : It Will Be Searching ThirdPart Dirctory In Environment Variable..." )
		IF(EXISTS $ENV{THIRD_PARTY_ROOT})
			COMMON_GET_ENV(_THIRD_PARTY_ROOT THIRD_PARTY_ROOT)
			SET(_3rdPartyDir_ ${_THIRD_PARTY_ROOT})		
			MESSAGE( STATUS "  -->Step2 : ThirdPart Dirctory In Eevironment THIRD_PARTY_ROOT: Yes!!!" )
		ELSE(EXISTS $ENV{VRTHIRDPART_ROOT})
			COMMON_GET_ENV(_VRTHIRDPART_ROOT VRTHIRDPART_ROOT)
			SET(_3rdPartyDir_ ${_VRTHIRDPART_ROOT})		
			MESSAGE( STATUS "  -->Step2 : ThirdPart Dirctory In Eevironment VRTHIRDPART_ROOT: Yes!!!" )
		ELSE()
			MESSAGE( STATUS "  -->Step2 : ThirdPart Dirctory In Eevironment THIRD_PARTY_ROOT: NO!!!" )
		ENDIF()
	ELSE()
		MESSAGE( STATUS "  -->By Defualt Process...Find The ThirdPart Dirctory ${_3rdPartyDir_}" )
	ENDIF()
	
	SET(${_out_dir} ${_3rdPartyDir_} PARENT_SCOPE)
endfunction(_Defualt_Search_3rdParty_Process)

#判断有没有提提前预设定Direcory路径
MACRO(CONFIRM_THIRD_PART_ROOT)
	MESSAGE(STATUS "========CONFIRM_THIRD_PART_ROOT--Seraching The 3rdPartyDirs...========" )
  
    SET(options )
    SET(oneValueArgs PATH)
    SET(multiValueArgs )
    
    cmake_parse_arguments(_THIRD_PART 
            "${options}" 
            "${oneValueArgs}" 
            "${multiValueArgs}" 
            ${ARGN})
	
    if(NOT _THIRD_PART_PATH)
        set(_THIRD_PART_PATH "${CMAKE_SOURCE_DIR}/ThirdPart")
        MESSAGE(STATUS "  -->Default The THIRD_PART_PATH Of ${_THIRD_PART_PATH}")
	else()
		MESSAGE(STATUS "  -->Search The THIRD_PART_PATH In ${_THIRD_PART_PATH}")
    endif()

	#1.i will find the possible path
	IF(NOT EXISTS ${_THIRD_PART_PATH})
		MESSAGE( STATUS "  -->You Hasn't Set The PATH Value, Will Be Searching Dirctory By Defualt Process..." )
	
		_Defualt_Search_3rdParty_Process(_findpath)

		SET(_3RDPARTY_DIR ${_findpath})
	ELSE()
		SET(_3RDPARTY_DIR ${_THIRD_PART_PATH})
	ENDIF()

	#2.if not find the path, find the envpaths
	IF(NOT EXISTS ${_3RDPARTY_DIR})
		COMMON_GET_ENV(_proj_VRTHIRDPART_ROOT VRTHIRDPART_ROOT)
		if(NOT EXISTS ${_proj_VRTHIRDPART_ROOT})
			MESSAGE(WARNING "No Find ThridPart Dir In Env VRTHIRDPART_ROOT...")
		endif()
	ENDIF()

	#3.if not find the path, user settint the path..
	IF(NOT EXISTS ${_3RDPARTY_DIR})
		UNSET(_3RDPARTY_DIR CACHE)
		SET(_3RDPARTY_DIR ${_3RDPARTY_DIR} CACHE PATH "Seting The 3RD_Party Dir Of The Project By Yourself!!!")
	ENDIF()

	IF(NOT EXISTS ${_3RDPARTY_DIR})
		MESSAGE(FATAL_ERROR "There Is No _3RDPARTY_DIR With : ${_3RDPARTY_DIR}, You Must Set The _3RDPARTY_DIR On CMake UI By Yourself!!!!")
	ENDIF()

	set(CMAKE_PREFIX_PATH 
		${CMAKE_PREFIX_PATH} 
		${_3RDPARTY_DIR}
  	)

	#result variable global
	SET(ACTUAL_3DPARTY_DIR "${_3RDPARTY_DIR}")
	SET(THIRD_PART_PATH ${ACTUAL_3DPARTY_DIR})
	SET(THIRD_PART_ROOT ${ACTUAL_3DPARTY_DIR})

	MESSAGE(STATUS "-->Result: THIRD_PART_ROOT = ${THIRD_PART_PATH}")
	MESSAGE(STATUS "========CONFIRM_THIRD_PART_ROOT--Finish!!!============================" )
ENDMACRO()