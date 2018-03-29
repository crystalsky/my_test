set(LOC_FOO TRUE)

#子模块指定处理
#xxx_x_FOUND
#模块名_子模块名_FOUND指定是否找到相关模块处理
set(LotsOfComponents_AComp_FOUND TRUE)
set(LotsOfComponents_BComp_FOUND FALSE)
set(LotsOfComponents_CComp_FOUND TRUE)
set(LotsOfComponents_A_FOUND TRUE)

include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)

find_package_handle_standard_args(LotsOfComponents REQUIRED_VARS LOC_FOO
                                                   HANDLE_COMPONENTS)
