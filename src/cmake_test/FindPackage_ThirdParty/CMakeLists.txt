list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

cmake_policy(SET CMP0017 NEW)

# 设置搜索Dir
# set(CMAKE_PREFIX_PATH 
#   "${PROJECT_SOURCE_DIR}/ThirdParty/cmake"
# )
message(STATUS "CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}")


#find_package(OSG 3.2.1 EXACT CONFIG)
find_package(UtilityKit CONFIG)
find_package(QtUtility CONFIG)
find_package(xerces-c CONFIG)
find_package(glog CONFIG)
find_package(jsoncpp CONFIG)
find_package(tinyxml CONFIG)

find_package(QtUI CONFIG)

find_package(OSG 3.2.1 EXACT CONFIG)
find_package(Ice CONFIG)

find_package(freeglut CONFIG)
find_package(glfw CONFIG)
find_package(glew CONFIG)
find_package(glad CONFIG)
find_package(GLTools CONFIG)

#names test..
#find_package(UtilityKit2350 2.350 EXACT CONFIG NAMES UtilityKit)
#find_package(UtilityKit2351 2.351 EXACT CONFIG NAMES UtilityKit)





# find_package(Bar)
# set(CMAKE_DISABLE_FIND_PACKAGE_Blub TRUE)
# find_package(Blub NO_MODULE)
# find_package(TFramework CONFIGS TFrameworkConfig.cmake)
# find_package(Tframework)
# find_package(TApp)
# find_package(Tapp CONFIGS tapp-config.cmake)
# find_package(Special NAMES Suffix SuffixTest PATH_SUFFIXES test)

# # Test Config files which set Xyz_FOUND themselves:
#find_package(SetFoundTRUE NO_MODULE)
#find_package(SetFoundFALSE NO_MODULE)

 # Test wrong initial path when result is present.
 #set(WrongA_DIR "${VersionedD_DIR}")
 #find_package(WrongA 1.2 EXACT NAMES Baz)

# # Test wrong initial cache entry of UNINITIALIZED type when result is present.
# set(WrongB_DIR "${VersionedD_DIR}" CACHE UNINITIALIZED "Wrong Value" FORCE)
# get_property(type CACHE WrongB_DIR PROPERTY TYPE)
# find_package(WrongB 1.2 EXACT NAMES Baz)

# # Test wrong initial path when result is missing.
# set(WrongC_DIR "${VersionedD_DIR}")
# find_package(WrongC 1.3 EXACT QUIET NAMES Baz)

# # Test wrong initial cache entry of UNINITIALIZED type when result is missing.
# set(WrongD_DIR "${VersionedD_DIR}" CACHE UNINITIALIZED "Wrong Value" FORCE)
# get_property(type CACHE WrongD_DIR PROPERTY TYPE)
# find_package(WrongD 1.3 EXACT QUIET NAMES Baz)

# # HINTS should override the system but PATHS should not
# list(INSERT CMAKE_SYSTEM_PREFIX_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/A")
# find_package(wibbleA NAMES wibble PATHS B)
# find_package(wibbleB NAMES wibble HINTS B)

# # Look for package with recursive find-modules.
# find_package(RecursiveA COMPONENTS A)
# find_package(RecursiveB 2)
# find_package(RecursiveC 3.1 EXACT)

# # Test architecture-specific search directories.
# set(CMAKE_LIBRARY_ARCHITECTURE arch)
# find_package(ArchA NAMES Bar)
# find_package(ArchB NAMES Foo CONFIGS FooConfig.cmake)
# find_package(ArchC 3.1 EXACT NAMES zot)
# find_package(ArchD 4.0 EXACT NAMES zot)
# unset(CMAKE_LIBRARY_ARCHITECTURE)

# # Test <Package>_DIR environment variable.
# # We erase the main prefix path to ensure the env var is used.
# set(CMAKE_PREFIX_PATH)
# set(ENV{EnvA_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/lib/zot-3.1")
# find_package(EnvA 3.1 EXACT QUIET NAMES zot) # Should Work
# find_package(EnvB 3.1 EXACT QUIET NAMES zot) # Should Fail

# # Test system package registry if available.
# if(CMakeTestSystemPackage)
#   find_package(CMakeTestSystemPackage)
#   execute_process(COMMAND ${CMakeTestSystemPackage_CLEANUP}
#     OUTPUT_VARIABLE _output ERROR_VARIABLE _error)
# endif()