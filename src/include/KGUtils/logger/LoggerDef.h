/**************************************************************************************************
* @file LoggerDef.h
* @note ��־ʹ�ýӿڡ�
*       ���ļ���Ϊʹ����־����ϵͳ��Ψһ�ӿڣ�ֻ��Ҫ��ʹ�õ��ļ��м����ͷ�ļ���
*       ������ͨ��LOG���������־��Ϣ��
*       ����ͨ��LOG_SWITC��������־����Ŀ���
* @author c00003
* @data 2013-12-21
**************************************************************************************************/
#ifndef LOGGER_DEF_H
#define LOGGER_DEF_H

#include <FeUtils/logger/Logger.h>
#include <FeUtils/Export.h>
#include <string>
/**
* @enum ������־�ļ���
*/
typedef enum LogLevel
    {
    /** 
    * ֵԽ�ͱ�ʾ����Խ�ߣ�ֻ����־����ȷ��༶��߲��ܴ�ӡ����־��Ϣ
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

    ///��ʱδ����
    LOG_EMERG   =   log4cpp::Priority::EMERG,

    ///�ش�Ĵ���
    LOG_FATAL   =   log4cpp::Priority::FATAL,

    ///���ؾ���
    LOG_ALERT   =   log4cpp::Priority::ALERT,

    ///Σ��
    LOG_CRIT    =   log4cpp::Priority::CRIT,

    ///����
    LOG_ERROR   =   log4cpp::Priority::ERROR,

    ///��������
    LOG_WARN    =   log4cpp::Priority::WARN,

    ///��ע
    LOG_NOTICE  =   log4cpp::Priority::NOTICE,

    ///��Ϣ
    LOG_INFO    =   log4cpp::Priority::INFO,

    ///����
    LOG_DEBUG   =   log4cpp::Priority::DEBUG,

    ///��ʱδ����
    LOG_NOTSET  =   log4cpp::Priority::NOTSET

    }ELOGLEVEl;

/**
* @enum ������־������������ʾ��־��Ϣ������
*/
typedef enum LOG_POS
    {
    /// �Ѿ����ڵ���־������
    LOG_EXIST              =        CLogger::NONE_ADAPTER,

    /// Console������
    LOG_CONSOLE            =        CLogger::CONSOLE_ADAPTER,

    /// �ļ�������
    LOG_FILE               =        CLogger::FILE_ADAPTER,                    

    ///���ɿ�������������
    LOG_IDE                =        CLogger::DEBUG_ADAPTER, 

    ///�ں��¼���������
    LOG_NTEVNET            =        CLogger::NTEVNET_ADAPTER,

    ///Console �� File ������
    LOG_FISOLE             =        LOG_CONSOLE | 
    LOG_FILE,

    /// ����Debug������������
    LOG_NODEBUG            =        LOG_CONSOLE|
    LOG_CONSOLE,

    /// �����ں��¼�������������
    LOG_NONTEVENT          =        LOG_FISOLE|
    LOG_DEBUG,

    /// ����������
    LOG_ALL                =        LOG_CONSOLE |
    LOG_FILE |
    LOG_IDE |
    LOG_NTEVNET,
    }ELogPos;



/**
* ������־�����
* LEVEL ��ʾ��־�ļ���
* ʹ��ʱ����    LOG(LOG_INFO)<<LOG_ALL <<"message";
* ����ֱ��ʹ��  LOG(LOG_INFO)<<"message"��
* ǰ�߱�ʾָ����־��Ϣ������
* ��������Ĭ�ϵ�����
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
* ������־�Ŀ���
* LOG_POSITION ��־������ָ���������߹ر�ĳһ����־������
* SWITCH ��ʾ���� 0����ʾ�رգ���0��ʾ����
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
* @brief ��־��Ļص�
* @note ��־�Ľӿ�ֻ��ͨ����������������ʵ�
* @author c00003
*/
class FEUTIL_EXPORT CLogFunc
    {
    public:
        /**
        * @brief ���캯��
        * @note ����Ĺ��캯�������ڹ������
        * @param logproc [in] �����Ϣ�ĺ����ĺ���ָ��
        * @param logger [in] ��־��������ָ��
        * @return �޷���ֵ
        */
        CLogFunc(LOGPROC2 logProc,CLogger* logger);


        /**
        * @brief ���캯��
        * @note ����Ĺ��캯���������������󣬲�������������Ĺ����������־��Ϣ��
        * @return �޷���ֵ
        */
        ~CLogFunc();

        /**
        * @brief ���������
        * @note ͨ�����������־�ص���������־��Ϣ
        * @param message [in] �������־��Ϣ
        * @return ������������
        */
        CLogFunc& operator << (const std::string& message);

        /**
        * @brief ���������
        * @note ͨ�����������־�ص���������־��Ϣ
        * @param number [in] ��Ҫ�������������
        * @return ������������
        */
        CLogFunc& operator << (int number);

        /**
        * @brief ���������
        * @note ͨ�����������־�ص���������־��Ϣ
        * @param number [in] ��Ҫ����ĸ�����������
        * @return ������������
        */
        CLogFunc& operator<<(float number);

        /**
        * @brief ���������
        * @note ͨ�����������־�ص���������־��Ϣ
        * @param number [in] ��Ҫ����ĸ�����������
        * @return ������������
        */
        CLogFunc& operator<<(double number);

        /**
        * @brief ���������
        * @note ͨ�����������־�ص���������־��Ϣ
        * @param number [in] ��Ҫ�����unsigned long long��������
        * @return ������������
        */
        CLogFunc& operator<<(unsigned long long number);

        /**
        * @brief ���������
        * @note ͨ�����������־�ص���������־��Ϣ
        * @param number [in] ��Ҫ�����unsigned long long��������
        * @return ������������
        */
        CLogFunc& operator<<(long long number);

        /**
        * @brief ���������
        * @note ͨ�����������־�ص���������־��Ϣ
        * @param pLog [in] ���������־�Ķ���
        * @return ������������
        */
        CLogFunc& operator<<(ILogObject* pLog);

        /**
        * @brief ���������
        * @note ͨ�������������־�ص�����־������
        * @param unAdapter [in] ������־��Ϣ������
        * @return ������������
        */
        CLogFunc& operator <<( ELogPos unAdapter);

        CLogFunc& operator<<(ELogColor unColor);

        CLogFunc& operator<<(unsigned int number);

        CLogFunc& operator<<(bool bo);

        CLogFunc& operator<<(long number);

        CLogFunc& operator<<(unsigned long number);

        CLogFunc& operator<<(const char* pszMessage);

    protected:

        /// �����־��Ϣ�ĺ���ָ��
        LOGPROC2 m_logfunc;

        /// ��־������
        CLogger* m_logger;

        /// ��־����λ��
        ELogPos  m_logpos;

        /// ��־��Ϣ
        std::string m_strMessage;

        ELogColor m_logcolor;
    };

#endif//LOGGER_DEF_H

