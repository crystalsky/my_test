message(STATUS "  VersionTest_FIND_VERSION = ${VersionTest_FIND_VERSION}\n
  VersionTest_FIND_VERSION_MAJOR = ${VersionTest_FIND_VERSION_MAJOR}
  VersionTest_FIND_VERSION_MINOR = ${VersionTest_FIND_VERSION_MINOR}
  VersionTest_FIND_VERSION_PATCH = ${VersionTest_FIND_VERSION_PATCH}
  VersionTest_FIND_VERSION_TWEAK = ${VersionTest_FIND_VERSION_TWEAK}
  VersionTest_FIND_VERSION_COUNT = ${VersionTest_FIND_VERSION_COUNT}
")


if(NOT "${VersionTest_FIND_VERSION}" STREQUAL "1.2.3.4")
  message(SEND_ERROR "VersionTest_FIND_VERSION=${VersionTest_FIND_VERSION} is not 1.2.3.4")
endif()
if(NOT "${VersionTest_FIND_VERSION_MAJOR}" STREQUAL "1")
  message(SEND_ERROR "VersionTest_FIND_VERSION_MAJOR=${VersionTest_FIND_VERSION_MAJOR} is not 1")
endif()
if(NOT "${VersionTest_FIND_VERSION_MINOR}" STREQUAL "2")
  message(SEND_ERROR "VersionTest_FIND_VERSION_MINOR=${VersionTest_FIND_VERSION_MINOR} is not 2")
endif()
if(NOT "${VersionTest_FIND_VERSION_PATCH}" STREQUAL "3")
  message(SEND_ERROR "VersionTest_FIND_VERSION_PATCH=${VersionTest_FIND_VERSION_PATCH} is not 3")
endif()
if(NOT "${VersionTest_FIND_VERSION_TWEAK}" STREQUAL "4")
  message(SEND_ERROR "VersionTest_FIND_VERSION_TWEAK=${VersionTest_FIND_VERSION_TWEAK} is not 4")
endif()
if(NOT "${VersionTest_FIND_VERSION_COUNT}" STREQUAL "4")
  message(SEND_ERROR "VersionTest_FIND_VERSION_COUNT=${VersionTest_FIND_VERSION_COUNT} is not 4")
endif()
