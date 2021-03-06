SET(LIB_NAME GLTools)

# 定义项目版本
ADD_DEFINITIONS(-DGLTools_LIBRARY)
ADD_DEFINITIONS(-DGLEW_BUILD)

FILE(GLOB_RECURSE ${LIB_NAME}_HDRS "include/*.h")
FILE(GLOB_RECURSE ${LIB_NAME}_SRCS "src/*.cpp")


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

#增加相关文件打包文件
ADD_LIBRARY (${LIB_NAME} STATIC
	${${LIB_NAME}_HDRS}	
	${${LIB_NAME}_SRCS}
	${${LIB_NAME}_VERSION_RC}	
)

LINK_WITH_VARIABLES(${LIB_NAME} 
		
)

TARGET_LINK_LIBRARIES(${LIB_NAME} 
	GLEW::GLEW
)

SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES FOLDER "Lib")

# 设置项目标签.
SET_TARGET_PROPERTIES(${LIB_NAME} PROPERTIES PROJECT_LABEL "Win32Lib ${LIB_NAME}")

#SET_TARGET_PROPERTIES( ${LIB_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY  "${PROJECT_SOURCE_DIR}/bin/" )
#SET_TARGET_PROPERTIES( ${LIB_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/bin/debug/" )
#SET_TARGET_PROPERTIES( ${LIB_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/bin/release/") 


SOURCE_GROUP(
    "Header Files"
    FILES  ${${LIB_NAME}_HDRS} 
)

#====================================================================
IF(CMAKE_CL_64)
SET(INSTALL_LIB_DIR lib/x64)
SET(INSTALL_BIN_DIR bin/x64)
ELSE(CMAKE_CL_64)
SET(INSTALL_LIB_DIR lib)
SET(INSTALL_BIN_DIR bin)
ENDIF(CMAKE_CL_64)

INSTALL(CODE "MESSAGE(\"==========Installing Lib ${LIB_NAME} To ${CMAKE_INSTALL_PREFIX}/${LIB_NAME}...\")")
INSTALL(FILES ${${LIB_NAME}_HDRS} DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIB_NAME}/Include)
IF(CMAKE_BUILD_TYPE MATCHES Debug)
	INSTALL(
	   TARGETS ${LIB_NAME}
	   RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIB_NAME}/${INSTALL_BIN_DIR} 
	   LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIB_NAME}/${INSTALL_LIB_DIR}
	   ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIB_NAME}/${INSTALL_LIB_DIR}
	)
ELSE(CMAKE_BUILD_TYPE MATCHES Debug)
	INSTALL(
	   TARGETS ${LIB_NAME}
	   RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIB_NAME}/${INSTALL_BIN_DIR}
	   LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIB_NAME}/${INSTALL_LIB_DIR}
	   ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIB_NAME}/${INSTALL_LIB_DIR}
	)
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)