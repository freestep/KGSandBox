#ifndef SCENE_SHELL_EXPORT_H
#define SCENE_SHELL_EXPORT_H

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
    #  if defined( SHELL_LIBRARY_STATIC )
    #    define KGSHELL_EXPORT
    #  elif defined( SHELL_LIBRARY )
    #    define KGSHELL_EXPORT   __declspec(dllexport)
    #  else
    #    define KGSHELL_EXPORT   __declspec(dllimport)
    #  endif
#else
    #  define KGSHELL_EXPORT
#endif  

#endif 
