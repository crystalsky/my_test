#ifndef cmake_test_lib_Export_h__
#define cmake_test_lib_Export_h__

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __MWERKS__)
#  ifdef cmake_test_lib_LIB
#    define cmake_test_lib_EXPORT __declspec(dllexport)
#  else
#    define cmake_test_lib_EXPORT __declspec(dllimport)
#  endif
#else
#  ifdef cmake_test_lib_LIB
#    define cmake_test_lib_EXPORT  __attribute__ ((visibility("default")))
#  else
#    define cmake_test_lib_EXPORT
#  endif
#endif

#endif // cmake_test_lib_Export_h__
