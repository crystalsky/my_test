#ifndef signalslot_export_h__
#define signalslot_export_h__

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
#  ifdef SIGNALSLOT_LIB
#    define SIGNALSLOT_EXPORT __declspec(dllexport)
#  else
#    define SIGNALSLOT_EXPORT __declspec(dllimport)
#  endif
#else
#  ifdef SIGNALSLOT_LIB
#    define SIGNALSLOT_EXPORT  __attribute__ ((visibility("default")))
#  else
#    define SIGNALSLOT_EXPORT
#  endif
#endif

#endif // signalslot_export_h__
