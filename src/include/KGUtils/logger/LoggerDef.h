/**************************************************************************************************
* @file LoggerDef.h
* @note 日志使用接口。
*       本文件作为使用日志管理系统的唯一接口，只需要在使用的文件中加入此头文件，
*       即可以通过LOG宏在输出日志信息。
*       或者通过LOG_SWITC来控制日志流向的开关
* @author c00003
* @data 2013-12-21
**************************************************************************************************/
#ifndef LOGGER_DEF_H
#define LOGGER_DEF_H

#include <FeUtils/logger/Logger.h>
#include <FeUtils/Export.h>
#include <string>
/**
* @enum 控制日志的级别
*/
typedef enum LogLevel
    {
    /** 
    * 值越低表示级别越高，只有日志级别比分类级别高才能打印出日志信息
    * EMERG  = 0, 
    * FATAL  = 0,
    * ALERT  = 100,
    * CRIT   = 200,
    * ERROR  = 300, 
    * WARN   = 400,
    * NOTICE = 500,
    * INFO   = 600,
    * DEBUG  = 700,
    * NOTSET = 800
    */

    ///暂时未定义
    LOG_EMERG   =   log4cpp::Priority::EMERG,

    ///重大的错误
    LOG_FATAL   =   log4cpp::Priority::FATAL,

    ///严重警告
    LOG_ALERT   =   log4cpp::Priority::ALERT,

    ///危险
    LOG_CRIT    =   log4cpp::Priority::CRIT,

    ///错误
    LOG_ERROR   =   log4cpp::Priority::ERROR,

    ///轻量警告
    LOG_WARN    =   log4cpp::Priority::WARN,

    ///关注
    LOG_NOTICE  =   log4cpp::Priority::NOTICE,

    ///信息
    LOG_INFO    =   log4cpp::Priority::INFO,

    ///调试
    LOG_DEBUG   =   log4cpp::Priority::DEBUG,

    ///暂时未定义
    LOG_NOTSET  =   log4cpp::Priority::NOTSET

    }ELOGLEVEl;

/**
* @enum 控制日志的适配器，表示日志信息的流向
*/
typedef enum LOG_POS
    {
    /// 已经存在的日志适配器
    LOG_EXIST              =        CLogger::NONE_ADAPTER,

    /// Console适配器
    LOG_CONSOLE            =        CLogger::CONSOLE_ADAPTER,

    /// 文件适配器
    LOG_FILE               =        CLogger::FILE_ADAPTER,                    

    ///集成开发环境适配器
    LOG_IDE                =        CLogger::DEBUG_ADAPTER, 

    ///内核事件的适配器
    LOG_NTEVNET            =        CLogger::NTEVNET_ADAPTER,

    ///Console 和 File 适配器
    LOG_FISOLE             =        LOG_CONSOLE | 
    LOG_FILE,

    /// 除了Debug的所有适配器
    LOG_NODEBUG            =        LOG_CONSOLE|
    LOG_CONSOLE,

    /// 除了内核事件的所有适配器
    LOG_NONTEVENT          =        LOG_FISOLE|
    LOG_DEBUG,

    /// 所有适配器
    LOG_ALL                =        LOG_CONSOLE |
    LOG_FILE |
    LOG_IDE |
    LOG_NTEVNET,
    }ELogPos;



/**
* 控制日志的输出
* LEVEL 表示日志的级别
* 使用时比如    LOG(LOG_INFO)<<LOG_ALL <<"message";
* 或者直接使用  LOG(LOG_INFO)<<"message"；
* 前者表示指定日志信息的流向。
* 后者则是默认的流向
*/
#ifndef LOG
#define LOG(LEVEL)\
    CLogger::Instance()->GetLoggerProc(LEVEL)
#endif//LOG

#ifndef LOG_FILENAME
#define LOG_FILENAME __FILE__
#endif

#ifndef LOG_FILELINE
#define LOG_FILELINE __LINE__
#endif

#ifndef LOG_FUNCTION
#define LOG_FUNCTION __FUNCTION__
#endif

#ifndef LOG_CODE
#define LOG_CODE(level)\
    LOG(level)<<"file:"<<LOG_FILENAME<<",line:"<<LOG_FILELINE<<"(function:"<<LOG_FUNCTION<<")"
#endif

#ifndef LOG_SHUTDOWN
#define LOG_SHUTDOWN CLogger::Release();
#endif

#if defined(_MSC_VER)
#pragma warning( disable : 4996 )
#endif


enum ELogColor
    {
    LOG_BLUE = 1,
    LOG_GREEN,
    LOG_CYANIDE,
    LOG_RED,
    LOG_PINK,
    LOG_YELLOW,
    LOG_WHITE,
    LOG_DEFAULT = -1
    };

/**
* 控制日志的开关
* LOG_POSITION 日志的流向，指定开启或者关闭某一个日志的流向
* SWITCH 表示开发 0，表示关闭，非0表示开启
*/
#ifndef LOG_SWITCH
#define LOG_SWITCH(LOG_POSITION,SWITCH)\
    CLogger::Instance()->SwitchLogger(LOG_POSITION,SWITCH);
#endif//LOG_SWITCH

std::string common_sprintf(const char* format,va_list va);

std::string common_sprintf(const char* format,...);

class FEUTIL_EXPORT ILogObject
    {
    public:
        virtual std::string GetLogMessage() = 0;
    };

class CLogColor;
/**
* @class CLogFunc
* @brief 日志类的回调
* @note 日志的接口只有通过此类才能在外界访问到
* @author c00003
*/
class FEUTIL_EXPORT CLogFunc
    {
    public:
        /**
        * @brief 构造函数
        * @note 该类的构造函数，用于构造对象
        * @param logproc [in] 输出信息的函数的函数指针
        * @param logger [in] 日志管理器的指针
        * @return 无返回值
        */
        CLogFunc(LOGPROC2 logProc,CLogger* logger);


        /**
        * @brief 构造函数
        * @note 该类的构造函数，用于析构对象，并且在析构对象的过程中输出日志信息。
        * @return 无返回值
        */
        ~CLogFunc();

        /**
        * @brief 重载流向符
        * @note 通过流向符想日志回调中输入日志信息
        * @param message [in] 输出的日志信息
        * @return 本身对象的引用
        */
        CLogFunc& operator << (const std::string& message);

        /**
        * @brief 重载流向符
        * @note 通过流向符想日志回调中输入日志信息
        * @param number [in] 需要输出的整型数据
        * @return 本身对象的引用
        */
        CLogFunc& operator << (int number);

        /**
        * @brief 重载流向符
        * @note 通过流向符想日志回调中输入日志信息
        * @param number [in] 需要输出的浮点类型数据
        * @return 本身对象的引用
        */
        CLogFunc& operator<<(float number);

        /**
        * @brief 重载流向符
        * @note 通过流向符想日志回调中输入日志信息
        * @param number [in] 需要输出的浮点类型数据
        * @return 本身对象的引用
        */
        CLogFunc& operator<<(double number);

        /**
        * @brief 重载流向符
        * @note 通过流向符想日志回调中输入日志信息
        * @param number [in] 需要输出的unsigned long long类型数据
        * @return 本身对象的引用
        */
        CLogFunc& operator<<(unsigned long long number);

        /**
        * @brief 重载流向符
        * @note 通过流向符想日志回调中输入日志信息
        * @param number [in] 需要输出的unsigned long long类型数据
        * @return 本身对象的引用
        */
        CLogFunc& operator<<(long long number);

        /**
        * @brief 重载流向符
        * @note 通过流向符想日志回调中输入日志信息
        * @param pLog [in] 可以输出日志的对象
        * @return 本身对象的引用
        */
        CLogFunc& operator<<(ILogObject* pLog);

        /**
        * @brief 重载流向符
        * @note 通过流向符控制日志回调中日志的流向
        * @param unAdapter [in] 控制日志信息的流向
        * @return 本身对象的引用
        */
        CLogFunc& operator <<( ELogPos unAdapter);

        CLogFunc& operator<<(ELogColor unColor);

        CLogFunc& operator<<(unsigned int number);

        CLogFunc& operator<<(bool bo);

        CLogFunc& operator<<(long number);

        CLogFunc& operator<<(unsigned long number);

        CLogFunc& operator<<(const char* pszMessage);

    protected:

        /// 输出日志信息的函数指针
        LOGPROC2 m_logfunc;

        /// 日志管理器
        CLogger* m_logger;

        /// 日志流向位置
        ELogPos  m_logpos;

        /// 日志信息
        std::string m_strMessage;

        ELogColor m_logcolor;
    };

#endif//LOGGER_DEF_H

