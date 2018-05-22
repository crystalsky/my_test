if(Build_General_Project)
	OPTION(BUILD_OSG OFF "Build Osg Study Projects")
	IF(BUILD_OSG)
		ADD_SUBDIRECTORY(osg)
		ADD_SUBDIRECTORY(QtStudy/OSG_Study)
	ENDIF(BUILD_OSG)

	OPTION(BUILD_OPENGL OFF "Build Opengl Study Projects")
	IF(BUILD_OPENGL)
		ADD_SUBDIRECTORY(opengl)
	ENDIF(BUILD_OPENGL)

	OPTION(BUILD_delta3d_TEST OFF "BUILD_delta3d_TEST")
	IF(BUILD_delta3d_TEST)
		ADD_SUBDIRECTORY(delta3d)
	ENDIF(BUILD_delta3d_TEST)

	IF(BUILD_OSG AND BUILD_delta3d_TEST)
		ADD_SUBDIRECTORY(QtWithOsgDelta3D/App1)
	ENDIF()

	OPTION(BUILD_QtExe OFF "BUILD_QtExe Test Qt Specific Characteristic Functions....")
	IF(BUILD_QtExe)
		ADD_SUBDIRECTORY(QtStudy/QtExe2)
	ENDIF()


	OPTION(BUILD_QtExe_With_TestSTL_Function OFF "BUILD_QtExe_With_TestSTL_Function...")
	IF(BUILD_QtExe_With_TestSTL_Function)
		ADD_SUBDIRECTORY(QtStudy/QtExe_CPP_STL)
	ENDIF()
	
	#OPTION(BUILD_QtExe2 OFF "BUILD_QtExe Test Qt Specific Characteristic Functions....")
	#IF(BUILD_QtExe2)
	    #ADD_SUBDIRECTORY(QtStudy/QtExe2)
	#ENDIF()


	ADD_SUBDIRECTORY(library_src)

ELSEIF(NOT Build_General_Project AND Build_ICE_Project)
	#MESSAGE(FATAL_ERROR "ICE_FILES_SERVER: ${LIB_SOURCES}")
	ADD_SUBDIRECTORY(ice)
ELSEIF(Build_CMakeTest_Project)
	ADD_SUBDIRECTORY(cmake_test)
ELSE()
	
ENDIF()

#ADD_SUBDIRECTORY(QtStudy/PickColorApp)

