#ifndef KG_RENDER_EXPORT_H
#define KG_RENDER_EXPORT_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
#  if defined( EARTH_LIBRARY_STATIC )
#    define KGRENDER_EXPORT
#  elif defined( EARTH_LIBRARY )
#    define KGRENDER_EXPORT   __declspec(dllexport)
#  else
#    define KGRENDER_EXPORT   __declspec(dllimport)
#  endif
#else
#  define KGRENDER_EXPORT
#endif  

#endif
