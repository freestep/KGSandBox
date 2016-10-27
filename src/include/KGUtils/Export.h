#ifndef HGUTIL_EXPORT_H
#define HGUTIL_EXPORT_H 1

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__) || defined( __MWERKS__)
#  if defined( KGUTILS_LIBRARY_STATIC )
#    define KGUTIL_EXPORT
#  elif defined( KGUTILS_LIBRARY )
#    define KGUTIL_EXPORT   __declspec(dllexport)
#  else
#    define KGUTIL_EXPORT   __declspec(dllimport)
#endif
#else
#define KGUTIL_EXPORT
#endif


#endif //KGUTIL_EXPORT_H