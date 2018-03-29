#ifndef DSS_ICEService_Export_h__
#define DSS_ICEService_Export_h__

/* #undef USE_STATIC_LIBRARY */

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
#  if defined( DSS_ICEService_LIBRARY_STATIC )
#    define DSS_ICEService_Export
#  elif defined( DSS_ICEService_LIBRARY )
#    define DSS_ICEService_Export __declspec(dllexport)
#  else
#    define DSS_ICEService_Export __declspec(dllimport)
#  endif
#else
#  ifdef DSS_ICEService_LIBRARY
#    define DSS_ICEService_Export  __attribute__ ((visibility("default")))
#  else
#    define DSS_ICEService_Export
#  endif
#endif

#endif // DSS_ICEService_Export_h__
