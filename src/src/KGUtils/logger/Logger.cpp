#include <logger/Logger.h>
#include <log4cpp/Category.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <stdlib.h>
#include <assert.h>
#include <logger/LoggerDef.h>
#include <stdarg.h>
#include <stdio.h>
#if defined(_WIN32)
#include <log4cpp/Win32DebugAppender.hh>
#include <log4cpp/NTEventLogAppender.hh>
#endif

//#ifdef 1
#include <OpenThreads/ScopedLock>
#include <OpenThreads/Mutex>
#include <string.h>

#define  ScopeLock(ScopeLockMutex)\
    OpenThreads::ScopedLock<OpenThreads::Mutex> mutex(ScopeLockMutex);
//#else
//#include <kernel/Scope.h>
//#define  ScopeLock(Mutex)\
//    HgKernel::Scope<HgKernel::FastMutex>mutex(Mutex);
//#endif
//
//#if defined(USE_HGKERNEL)
//#include <kernel/Console.h>
//#endif


SINGLETON_IMPLEMENT_NOCD(CLogger)


CLogger::CLogger()
{
    ScopeLock(m_mutex);
    if( 0 != ReadEnv())
    {
        throw std::invalid_argument("malloc char memory error");
    }
}

CLogger::~CLogger()
{
    ScopeLock(m_mutex);
    log4cpp::Category::shutdown();
}


int CLogger::ReadEnv()
{
    ScopeLock(m_mutex);
    unsigned int szEnv = 0;
    char* logVar;
    const char* strEnv = "LOG_ADAPTER";
    unsigned int unEnv =  DEFAULT_ADAPTER;

    const char*  evResult = getenv(strEnv);

    int result = 0;
    //strEnv = getenv(strEnv);
    if( 0 != evResult )
    {
        result = 0;


        logVar = (char*)malloc(szEnv * sizeof(char));
        if( 0 == logVar )
        {
            return -1;
        }

        logVar = getenv(strEnv);
        //getenv_s(&szEnv,logVar,szEnv,strEnv);

        if( 0 == strcmp("CONSOLE_ADAPTER",logVar))
        {
            unEnv =  CONSOLE_ADAPTER;
        }

        if( 0 == strcmp("FILE_ADAPTER",logVar))
        {
            unEnv =  FILE_ADAPTER;
        }

        if( 0 == strcmp("DEBUG_ADAPTER",logVar))
        {
            unEnv =  DEBUG_ADAPTER;
        }

        if( 0 == strcmp("NTEVNET_ADAPTER",logVar))
        {
            unEnv =  NTEVNET_ADAPTER;
        }

        if( 0 == strcmp("FILE_CONSOLE",logVar))
        {
            unEnv =  FILE_CONSOLE;
        }

        if( 0 == strcmp("ALL_NONTEVENT",logVar))
        {
            unEnv =  ALL_NONTEVENT;
        }

        if( 0 == strcmp("ALL_ADAPTER",logVar))
        {
            unEnv =  ALL_ADAPTER;
        }

        if( 0 == strcmp("DEFAULT_ADAPTER",logVar))
        {
            unEnv =  DEFAULT_ADAPTER;
        } 
    }
    //const char* cPattern = "%d: %p %c %x: %m%n";

    if( 0 != ( unEnv & CONSOLE_ADAPTER) )
    {
        BuildConsoleCategory();
    }

    if( 0 != ( unEnv & FILE_ADAPTER) )
    {
        BuildFileCategory();
    }
#if defined(_WIN32)
    if( 0 != ( unEnv & DEBUG_ADAPTER ) )
    {
        BuildDebugCategory();
    }

    if( 0 != ( unEnv & NTEVNET_ADAPTER) )
    {
        BuildNteventCategory();
    }
#elif defined(_LINUX)
#endif

    return result;
}

int CLogger::BuildConsoleCategory()
{
    ScopeLock(m_mutex);
    const char* cPattern = "%d: %p %c %x: %m%n";
    if(log4cpp::Category::exists("stream_category"))
    {
        return 1;
    }
    log4cpp::Category& info = log4cpp::Category::getInstance("stream_category");
    info.setPriority(LOG_NOTSET-1);
    log4cpp::PatternLayout* pLayout = new log4cpp::PatternLayout;
    pLayout->setConversionPattern(cPattern);
    log4cpp::Appender* adapter = new log4cpp::OstreamAppender("console",&std::cout);
    adapter->setLayout(pLayout);
    info.addAppender(*adapter);
    return 0;
}

int CLogger::BuildFileCategory()
{
    ScopeLock(m_mutex);
    const char* cPattern = "%d: %p %c %x: %m%n";
    //判断分类是否存在，如果存在则直接返回1
    if(log4cpp::Category::exists("file_category"))
    {
        return 1;
    }
    log4cpp::Category& info = log4cpp::Category::getInstance("file_category");
    info.setPriority(LOG_NOTSET-1);
    log4cpp::PatternLayout* pLayout = new log4cpp::PatternLayout;
    pLayout->setConversionPattern(cPattern);
    unsigned int size = 10*1024*1024;
    log4cpp::Appender* adapter = new log4cpp::RollingFileAppender("file","./log.txt",size,0xFFFF);
    adapter->setLayout(pLayout);
    info.addAppender(*adapter);
    return 0;
}

int CLogger::BuildDebugCategory()
{
    ScopeLock(m_mutex);
#if defined(_WIN32)
    const char* cPattern = "%d: %p %x: %m%n";
    if(log4cpp::Category::exists("debug_category"))
    {
        return 1;
    }
    log4cpp::Category& debug = log4cpp::Category::getInstance("debug_category");
    debug.setPriority(LOG_DEBUG+1);
    log4cpp::PatternLayout* pLayout = new log4cpp::PatternLayout;
    pLayout->setConversionPattern(cPattern);
    log4cpp::Appender* adapter = new log4cpp::Win32DebugAppender("debug");
    adapter->setLayout(pLayout);
    debug.addAppender(*adapter);
#endif
    return 0;
}

int CLogger::BuildNteventCategory()
{
    ScopeLock(m_mutex);
#if defined(_WIN32)
    const char* cPattern = "%d: %p %x: %m%n";
    if(log4cpp::Category::exists("system_category"))
    {
        return 1;
    }
    log4cpp::Category& error = log4cpp::Category::getInstance("system_category");
    error.setPriority(LOG_ERROR+1);
    log4cpp::PatternLayout* pLayout = new log4cpp::PatternLayout;
    pLayout->setConversionPattern(cPattern);
    log4cpp::Appender* adapter = new log4cpp::NTEventLogAppender("sysytem","systemAdapter");
    adapter->setLayout(pLayout);
    error.addAppender(*adapter);
#endif
    return 0;
}

void CLogger::GetLogCategories(unsigned int unAdapters,LogCategories& cates) throw(std::runtime_error)
{
    ScopeLock(m_mutex);
    //cates.clear();
#if defined(_WIN32)
    if( NONE_ADAPTER == unAdapters )
    {
        LogCategories* existCates = log4cpp::Category::getCurrentCategories();
        if( NULL == existCates)
        {
            throw std::runtime_error("get categories NULL");
        }
        cates.assign(existCates->begin(),existCates->end());
        delete existCates;
        existCates = NULL;
        return;
    }
    if( 0 != (unAdapters & CONSOLE_ADAPTER))
    {
        log4cpp::Category* category = NULL;
        if( NULL != (category = log4cpp::Category::exists("stream_category")))
        {
            cates.push_back(category);
        }
    }

    if( 0 != (unAdapters & FILE_ADAPTER))
    {
        log4cpp::Category* category = NULL;
        if( NULL != (category = log4cpp::Category::exists("file_category")))
        {
            cates.push_back(category);
        }
    }

    if( 0 != (unAdapters & DEBUG_ADAPTER))
    {
        log4cpp::Category* category = NULL;
        if( NULL != (category = log4cpp::Category::exists("debug_category")))
        {
            cates.push_back(category);
        }
    }

    if( 0 != (unAdapters & NTEVNET_ADAPTER))
    {
        log4cpp::Category* category = NULL;
        if( NULL != (category = log4cpp::Category::exists("system_category")))
        {
            cates.push_back(category);
        }
    }
#endif
}

void CLogger::InfoLog(const std::string& message , unsigned int unLogPos ,unsigned int unColor)
{
#if defined(_WIN32)
    ScopeLock(m_mutex);
    LogCategories cats(4,0);
    GetLogCategories(unLogPos,cats);

//     if( -1 == unColor)
//     {
//         unColor = CConsole::FG_GREEN;
//     }
//     CConsoleColorChange change(unColor);

    std::vector<log4cpp::Category*>::iterator it = cats.begin();
    for( ; it != cats.end() ; it++)
    {
        if(NULL == *it)
        {
            continue;
        }
        (*it)->info(message);
    }
#endif
}

void CLogger::ErrorLog(const std::string& message, unsigned int unLogPos ,unsigned int unColor)
{
#if defined(_WIN32)
    ScopeLock(m_mutex);
    LogCategories cats(4,0);
    GetLogCategories(unLogPos,cats);

    

//     if( -1 == unColor)
//     {
//         unColor = CConsole::FG_RED;
//     }
//     CConsoleColorChange change(unColor);

    std::vector<log4cpp::Category*>::iterator it = cats.begin();
    for( ; it != cats.end() ; it++)
    {
        if(NULL == *it)
        {
            continue;
        }
        (*it)->error(message);
    }
#endif
}

void CLogger::DebugLog(const std::string& message, unsigned int unLogPos,unsigned int unColor )
{
    ScopeLock(m_mutex);
    LogCategories cats;
    GetLogCategories(unLogPos,cats);

//     if( -1 == unColor)
//     {
//         unColor = CConsole::FG_WHITE;
//     }
//     CConsoleColorChange change(unColor);

    std::vector<log4cpp::Category*>::iterator it = cats.begin();
    for( ; it != cats.end() ; it++)
    {
        if(NULL == *it)
        {
            continue;
        }
        (*it)->debug(message);
    }
}

void CLogger::NoticeLog(const std::string& message, unsigned int unLogPos,unsigned int unColor )
{
    ScopeLock(m_mutex);
    LogCategories cats;
    GetLogCategories(unLogPos,cats);

//     if( -1 == unColor)
//     {
//         unColor = CConsole::FG_CYANIDE|CConsole::BG_BLUE;
//     }
//     CConsoleColorChange change(unColor);

    std::vector<log4cpp::Category*>::iterator it = cats.begin();
    for( ; it != cats.end() ; it++)
    {
        if(NULL == *it)
        {
            continue;
        }
        (*it)->notice(message);
    }
}

void CLogger::WarnLog(const std::string& message, unsigned int unLogPos ,unsigned int unColor)
{
    ScopeLock(m_mutex);
    LogCategories cats;
    GetLogCategories(unLogPos,cats);

//     if( -1 == unColor)
//     {
//         unColor = CConsole::FG_YELLOW;
//     }
//     CConsoleColorChange change(unColor);

    std::vector<log4cpp::Category*>::iterator it = cats.begin();
    for( ; it != cats.end() ; it++)
    {
        if(NULL == *it)
        {
            continue;
        }
        (*it)->warn(message);
    }
}

void CLogger::CritLog(const std::string& message, unsigned int unLogPos,unsigned int unColor )
{
    ScopeLock(m_mutex);
    LogCategories cats;
    GetLogCategories(unLogPos,cats);

//     if( -1 == unColor)
//     {
//         unColor = CConsole::FG_RED;
//     }
//     CConsoleColorChange change(unColor);

    std::vector<log4cpp::Category*>::iterator it = cats.begin();
    for( ; it != cats.end() ; it++)
    {
        if(NULL == *it)
        {
            continue;
        }
        (*it)->crit(message);
    }
}

void CLogger::AlertLog(const std::string& message, unsigned int unLogPos,unsigned int unColor )
{
    ScopeLock(m_mutex);
    LogCategories cats;
    GetLogCategories(unLogPos,cats);

//     if( -1 == unColor)
//     {
//         unColor = CConsole::FG_RED;
//     }
//     CConsoleColorChange change(unColor);

    std::vector<log4cpp::Category*>::iterator it = cats.begin();
    for( ; it != cats.end() ; it++)
    {
        if(NULL == *it)
        {
            continue;
        }
        (*it)->alert(message);
    }
}

void CLogger::FatalLog(const std::string& message, unsigned int unLogPos,unsigned int unColor)
{
    ScopeLock(m_mutex);
    LogCategories cats;
    GetLogCategories(unLogPos,cats);

//     if( -1 == unColor )
//     {
//         unColor = CConsole::FG_BLUE| CConsole::BG_RED;
//     }
//     CConsoleColorChange change(unColor);

    std::vector<log4cpp::Category*>::iterator it = cats.begin();
    for( ; it != cats.end() ; it++)
    {
        if(NULL == *it)
        {
            continue;
        }
        (*it)->fatal(message);
    }
}

/**
* 控制日志输出的开关
*/
void CLogger::SwitchLogger(unsigned int unAdapters,unsigned int logswitch)throw(std::runtime_error)
{
    ScopeLock(m_mutex);
    if( 0 != (unAdapters & CONSOLE_ADAPTER))
    {
        log4cpp::Category* cat = log4cpp::Category::exists("stream_category");
        if( LOG_OFF == logswitch)
        {
            if( NULL != cat )
            {
                cat->setPriority(0);
            }
        }
        else
        {
            if( NULL == cat )
            {
                BuildConsoleCategory() ;
            }
            if(NULL == (cat = log4cpp::Category::exists("stream_category")))
            {
                throw std::runtime_error("Build LogCategory Faild!!");
            }
            cat->setPriority(log4cpp::Priority::NOTSET+1);
        }
    }

    if( 0 != (unAdapters & FILE_ADAPTER))
    {
        log4cpp::Category* cat = log4cpp::Category::exists("file_category");
        if( LOG_OFF == logswitch)
        {
            if( NULL != cat )
            {
                cat->setPriority(0);
            }
        }
        else
        {
            if( NULL == cat )
            {
                BuildConsoleCategory() ;
            }
            if(NULL == (cat = log4cpp::Category::exists("file_category")))
            {
                throw std::runtime_error("Build LogCategory Faild!!");
            }
            cat->setPriority(log4cpp::Priority::INFO+1);
        }
    }

    if( 0 != (unAdapters & DEBUG_ADAPTER))
    {
        log4cpp::Category* cat = log4cpp::Category::exists("debug_category");
        if( LOG_OFF == logswitch)
        {
            if( NULL != cat )
            {
                cat->setPriority(0);
            }
        }
        else
        {
            if( NULL == cat )
            {
                BuildDebugCategory() ;
            }
            if(NULL == (cat = log4cpp::Category::exists("debug_category")))
            {
                throw std::runtime_error("Build LogCategory Faild!!");
            }
            cat->setPriority(log4cpp::Priority::DEBUG+1);
        }
    }

    if( 0 != (unAdapters & NTEVNET_ADAPTER))
    {
        log4cpp::Category* cat = log4cpp::Category::exists("system_category");
        if( LOG_OFF == logswitch)
        {
            if( NULL != cat )
            {
                cat->setPriority(0);
            }
        }
        else
        {
            if( NULL == cat )
            {
                BuildNteventCategory()  ;
            }
            if(NULL == (cat = log4cpp::Category::exists("system_category")))
            {
                throw std::runtime_error("Build LogCategory Faild!!");
            }
            cat->setPriority(log4cpp::Priority::ERROR+1);
        }
    }
}

/**
* 判断需要打印的日志的级别所在的级别区间，并返回该级别的打印函数的回调对象
*/
CLogFunc CLogger::GetLoggerProc(unsigned int unLevel)
{
    ScopeLock(m_mutex);
    if( unLevel <= LOG_NOTSET &&
        unLevel > LOG_DEBUG)
    {
        return CLogFunc(&CLogger::DebugLog,this);
    }
    else if(unLevel <= LOG_DEBUG&&
        unLevel > LOG_INFO)
    {
        return CLogFunc(&CLogger::DebugLog,this);
    }
    else if(unLevel <= LOG_INFO &&
        unLevel > LOG_NOTICE)
    {
        return CLogFunc(&CLogger::InfoLog,this);
    }
    else if (unLevel <= LOG_NOTICE &&
        unLevel > LOG_WARN)
    {
        return CLogFunc(&CLogger::NoticeLog,this);
    }
    else if( unLevel <= LOG_WARN &&
        unLevel > LOG_ERROR)
    {
        return CLogFunc(&CLogger::WarnLog,this);
    }
    else if( unLevel <= LOG_ERROR &&
        unLevel > LOG_CRIT)
    {
        return CLogFunc(&CLogger::ErrorLog,this);
    }
    else if( unLevel <= LOG_CRIT &&
        unLevel > LOG_ALERT)
    {
        return CLogFunc(&CLogger::CritLog,this);
    }
    else if( unLevel <= LOG_ALERT&&
        unLevel > LOG_FATAL)
    {
        return CLogFunc(&CLogger::AlertLog,this);
    }
    else
    {
        return CLogFunc(&CLogger::FatalLog,this);
    }
    return CLogFunc(NULL,NULL);
}


std::string common_sprintf( const char* format,va_list va )
{
    size_t size = 1024;
    char* buffer = new char[size];
    
    while (1) {
        va_list args_copy;

#if defined(_MSC_VER) || defined(__BORLANDC__)
        args_copy = va;
#else
        va_copy(args_copy, va);
#endif
        memset(buffer,0,size);
#if defined(_MSC_VER) || defined(__BORLANDC__)
        int n = _vsnprintf(buffer, size, format, args_copy);
#else
        int n = vsnprintf(buffer, size, format, args_copy);
#endif
        //
        va_end(args_copy);

        if ((n > -1) && (static_cast<size_t>(n) < size)) {
            std::string s(buffer);
            delete [] buffer;
            return s;
        }

        size = (n > -1) ?
            n + 1 :   
        size * 2; 
        
        delete [] buffer;
        buffer = new char[size];
    }
}

std::string common_sprintf( const char* format,... )
{
    va_list va;
    va_start(va,format);
    return common_sprintf(format,va);
    va_end(va);
}

CLogFunc::CLogFunc( LOGPROC2 logProc,CLogger* logger )
{
    m_logfunc = logProc;
    m_logger = logger;
    m_logpos = LOG_EXIST;
    m_logcolor = LOG_DEFAULT;
   
}

CLogFunc::~CLogFunc()
{
    if( NULL == m_logger || NULL == m_logfunc)
    {
        return;
    }
    (m_logger->*m_logfunc)(m_strMessage,m_logpos,m_logcolor);
     m_strMessage.~basic_string();
}

CLogFunc& CLogFunc::operator<<( const std::string& message )
{
    m_strMessage.append(message);
    return *this;
}

CLogFunc& CLogFunc::operator<<( int number )
{
    m_strMessage.append(common_sprintf("%d",number));
    return *this;
}

CLogFunc& CLogFunc::operator<<( float number )
{
    m_strMessage.append(common_sprintf("%f",number));
    return *this;
}

CLogFunc& CLogFunc::operator<<( double number )
{
    m_strMessage.append(common_sprintf("%lf",number));
    return *this;
}

CLogFunc& CLogFunc::operator<<( ILogObject* pLog )
{
    m_strMessage.append(pLog->GetLogMessage());
    return *this;
}

CLogFunc& CLogFunc::operator<<( ELogPos unAdapter )
{
    m_logpos = unAdapter;
    return *this;
}

CLogFunc& CLogFunc::operator<<(ELogColor unColor)
{
    m_logcolor = unColor;
    return *this;
}

CLogFunc& CLogFunc::operator<<(unsigned int number)
{
    m_strMessage.append(common_sprintf("%d",number));
    return *this;
}

CLogFunc& CLogFunc::operator<<(bool bo)
{
    std::string str = (bo == true ? "true" : "false");
    m_strMessage.append(str);
    return *this;
}

CLogFunc& CLogFunc::operator<<(long number)
{
    m_strMessage.append(common_sprintf("%ld",number));
    return *this;
}

CLogFunc& CLogFunc::operator<<(unsigned long number)
{
    m_strMessage.append(common_sprintf("%ld",number));
    return *this;
}

CLogFunc& CLogFunc::operator<<( unsigned long long number )
{
    m_strMessage.append(common_sprintf("%lld",number));
    return *this;
}

CLogFunc& CLogFunc::operator<<(long long number)
{
    m_strMessage.append(common_sprintf("%lld",number));
    return *this;
}

CLogFunc& CLogFunc::operator<<(const char* pszMessage)
{
    m_strMessage.append(pszMessage);
    return *this;
}
