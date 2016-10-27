/**************************************************************************************************
* @file LoggerExport.h
* @note Logger库导出文件
* @author c00003
* @data 2014-01-07
**************************************************************************************************/
#ifndef LOGGEREXPORT_H
#define LOGGEREXPORT_H

#if defined(_MSC_VER) \
 || defined(__CYGWIN__) \
 || defined(__MINGW32__) \
 || defined(__BCPLUSPLUS__) \
 || defined(__MWERKS__)
#if defined( LOGGER_EXPORT_STATIC )
#   define LOGGER_EXPORT
#elif defined(LOGGER_EXPORT_DLL)
#   define LOGGER_EXPORT __declspec(dllexport)
#else//LOGGER_EXPORT_DLL
#   define LOGGER_EXPORT __declspec(dllimport)
#endif//LOGGER_EXPORT_STATIC
#endif

#ifdef _MSC_VER   
#   if (_MSC_VER >= 1300)   
#      define STL_MEMBER_TEMPLATES   
#   endif   
#endif   
 

#ifndef NULL   
#   ifdef  __cplusplus   
#      define NULL    0   
#else   
#   define NULL   ((void *)0)   
#   endif   
#endif//NULL

#endif//LOGGEREXPORT_H
