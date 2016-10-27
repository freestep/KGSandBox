#ifndef KG_GRAPH_EXPORT_H
#define KG_GRAPH_EXPORT_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( EARTH_LIBRARY_STATIC )
    #    define KGGRAPH_EXPORT
    #  elif defined( EARTH_LIBRARY )
    #    define KGGRAPH_EXPORT   __declspec(dllexport)
    #  else
    #    define KGGRAPH_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define KGGRAPH_EXPORT
#endif  

#endif 
