SET(TARGET_NAME DSS_ICEService)

ADD_DEFINITIONS(-D${TARGET_NAME}_LIBRARY)

VIRE_MAKE_EXPORT_CLASS(
	${TARGET_NAME} ${CMAKE_CURRENT_LIST_DIR}
	DSS_ICEServiceServer
	DSS_ICEClient
)

VIRE_MAKE_CLASS(
	${TARGET_NAME}
	TaskBase
	TaskDataTrans
)

SEARCH_FILE_TO_VAL(LIB_SOURCES 
	DSS_ICEServiceServer
	DSS_ICEClient


	DSSDataService 
	DSSDataServiceI 
	ClientsManager 
	TaskManager 
	UserTaskMapper

	TaskBase
	UserTask 
	TaskDataTrans

	CRCUtil

	DSSServiceCallBackI 
)

ADD_LIBRARY(${TARGET_NAME} SHARED
   ${LIB_SOURCES}
)

include_directories(
	${Boost_INCLUDE_DIR}
	${PROJECT_INCLUDE_DIR}
	${CMAKE_CURRENT_LIST_DIR}
)

ADD_3RD_DEPENDENCIES(${TARGET_NAME} 
	UTILITYKIT_LIBRARY
	JSONCPP_LIBRARY
	GLOG_LIBRARY
)

target_link_libraries(${TARGET_NAME}
	ICE::ICE
	ICE::ICEUTIL
)

LINK_WITH_VARIABLES(${TARGET_NAME} 
	Boost_PROGRAM_OPTIONS_LIBRARY
	Boost_DATE_TIME_LIBRARY
)

SET_TARGET_PROPERTIES(${TARGET_NAME} 
	PROPERTIES 
	FOLDER "ice") 
SET_TARGET_PROPERTIES(${TARGET_NAME} 
	PROPERTIES 
	DEBUG_OUTPUT_NAME "${TARGET_NAME}${CMAKE_DEBUG_POSTFIX}")
SET_TARGET_PROPERTIES(${TARGET_NAME} 
	PROPERTIES 
	RELEASE_OUTPUT_NAME "${TARGET_NAME}${CMAKE_RELEASE_POSTFIX}")

SET(DEST_FILE_DIR ${PROJECT_SOURCE_DIR}/bin/)
MESSAGE(STATUS "....${DEST_FILE_DIR}/${TARGET_OUTPUT_NAME}${CMAKE_DEBUG_POSTFIX}")

add_custom_command(TARGET  ${TARGET_NAME} PRE_BUILD
	  COMMAND echo "delete  ${TARGET_NAME}.exe..."
	  COMMAND ${CMAKE_COMMAND} -E remove 
	  	${DEST_FILE_DIR}/debug/${TARGET_OUTPUT_NAME}${CMAKE_DEBUG_POSTFIX}.exe
	  COMMAND ${CMAKE_COMMAND} -E remove 
	  	${DEST_FILE_DIR}/release/${TARGET_OUTPUT_NAME}${CMAKE_RELEASE_POSTFIX}.exe
)

