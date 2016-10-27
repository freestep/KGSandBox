/**************************************************************************************************
* @file Logger.h
* @note 日志记录功能的类
* @author c00003
* @data 2013-12-27
**************************************************************************************************/
#ifndef LOGGER_H
#define LOGGER_H

#include <OpenThreads/Mutex>
#include <string>
#include <log4cpp/Priority.hh>
#include <log4cpp/Category.hh>
#include <FeUtils/logger/Singleton.h>
#include <FeUtils/Export.h>
#ifdef __cplusplus
#pragma warning(disable : 4172)
#endif


class CLogger;
class CLogFunc;


typedef std::vector<log4cpp::Category*> LogCategories;

typedef void(CLogger::*LOGPROC2)(const std::string& ,unsigned int ,unsigned int);

/**
* @class CLogger
* @brief logger日志记录器的主要实现类
* @note 本类主要是对log4cpp进行封装和进一步的抽象，并确定日志逻辑和实现
* @author c00003
*/
//class LOGGER_EXPORT CLogger
class FEUTIL_EXPORT CLogger
    {
    SINGLETON_DECLARE(CLogger)

    public:

        /**
        * @enum 日志的控制开关，
        */
        typedef enum LogSwitch
            {
            /**
            * 关闭日志，关闭某一或者全部流向的日志
            */
            LOG_OFF     =   0,

            /**
            * 开启日志，开启某一或者全部流向的日志
            */
            LOG_ON      =   1
            }ELOGSWITCh;


        /**
        * @enum 日志的适配器，表示日志的流向。默认有四个流向
        * Console，File，Debug，NetEvent
        */
        typedef enum ELogAdapter
            {
            /**
            * 没有适配器，即日志没有任何的流向，将不会在任何地方打印出日志。
            * 同时，当在输出日志的过程中指定Adapter时，None_Adapter表示
            * 维持现有的Adapter，不添加也不指定在某一地方输出。
            */
            NONE_ADAPTER             =       0,

            /**
            * Console适配器，被指定此适配器的日志将输出到Console中，
            * 在Win32环境下是Console，Linux环境下是terminal
            */
            CONSOLE_ADAPTER          =       1,

            /**
            * File适配器，被指定此适配器的日至信息将输出到指定的文件中。
            */
            FILE_ADAPTER             =       CONSOLE_ADAPTER<<1,

            /**
            * Debug适配器，目前只适用与Win32平台的编译环境，在VC6.0，
            * VS8.0，VS9.0,VS10.0的编译工具中会打印出流向适配器的日志信息。
            * Debug适配器，顾名思义，只会在Debug时才会起作用，因为只有在调试
            * 过程中你才能从IDE环境中看到你确定Debug的日志信息。
            */
            DEBUG_ADAPTER            =       CONSOLE_ADAPTER<<2,   

            /**
            * NtEvent适配器，目前只适用于Win32平台的运行环境。
            * 此适配器的目的地是在Windows系统中存储，查看方式是：
            * 1，在桌面找到计算机（XP以下为我的电脑），并右键单击；
            * 2，在右键菜单中选中管理子菜单，此时会弹出计算机管理的应用程序；
            * 3，在左侧一次递归选中事件查看器，windows日志，应用程序；
            * 4，此时可以在右边看到输出此适配器的日志信息
            */
            NTEVNET_ADAPTER          =       CONSOLE_ADAPTER<<3,

            /**
            * 同时让File适配器和Console适配器作用
            */
            FILE_CONSOLE             =       CONSOLE_ADAPTER | 
            FILE_ADAPTER,

            /**
            * 除了NtEvent的所有的适配器都起作用
            */
            ALL_NONTEVENT            =       CONSOLE_ADAPTER |
            FILE_ADAPTER |
            DEBUG_ADAPTER,

            /**
            * 所有的适配器都起作用
            */
            ALL_ADAPTER              =       CONSOLE_ADAPTER |
            FILE_ADAPTER |
            DEBUG_ADAPTER |
            NTEVNET_ADAPTER,

            /**
            * 默认的适配器，也就是File和Console适配器的组合
            */
            DEFAULT_ADAPTER          =       FILE_CONSOLE

            }LOGADAPTER;

    public:

        /**
        * @brief 获取日志打印的回调对象
        * @note 通过输入的日志级别信息，在内部和已有的分类进行级别比较，确定日志级别。
        *       在确定日志的级别后，获取这个级别的函数指针并构造一个回调对象
        * @param unLevel [in] 日志信息的级别。 
        * @return 返回一个CLogFunc的引用对象
        */
        CLogFunc GetLoggerProc(unsigned int unLevel);

    protected:
        /**
        * @brief 打印INFO级别的信息
        * @param message [in] 日志信息的内容。 
        * @param unLogPos [in] 日志的流向，指定特定的适配器
        */
        virtual void InfoLog(const std::string& message
            ,unsigned int unLogPos = NONE_ADAPTER
            ,unsigned int unColor = -1);

        /**
        * @brief 打印ERROR级别的信息
        * @param message [in] 日志信息的内容。 
        * @param unLogPos [in] 日志的流向，指定特定的适配器
        */
        virtual void ErrorLog(const std::string& message
            ,unsigned int unLogPos = NONE_ADAPTER
            ,unsigned int unColor = -1 );

        /**
        * @brief 打印DEBUG级别的信息
        * @param message [in] 日志信息的内容。 
        * @param unLogPos [in] 日志的流向，指定特定的适配器
        */
        virtual void DebugLog(const std::string& message
            ,unsigned int unLogPos = NONE_ADAPTER
            ,unsigned int unColor = -1 );

        /**
        * @brief 打印NOTICE级别的信息
        * @param message [in] 日志信息的内容。 
        * @param unLogPos [in] 日志的流向，指定特定的适配器
        */
        virtual void NoticeLog(const std::string& message
            ,unsigned int unLogPos = NONE_ADAPTER
            ,unsigned int unColor = -1);

        /**
        * @brief 打印WARN级别的信息
        * @param message [in] 日志信息的内容。 
        * @param unLogPos [in] 日志的流向，指定特定的适配器
        */
        virtual void WarnLog(const std::string& message
            ,unsigned int unLogPos = NONE_ADAPTER
            ,unsigned int unColor = -1 );

        /**
        * @brief 打印CRIT级别的信息
        * @param message [in] 日志信息的内容。 
        * @param unLogPos [in] 日志的流向，指定特定的适配器
        */
        virtual void CritLog(const std::string& message
            ,unsigned int unLogPos = NONE_ADAPTER
            ,unsigned int unColor = -1);

        /**
        * @brief 打印ALERT级别的信息
        * @param message [in] 日志信息的内容。 
        * @param unLogPos [in] 日志的流向，指定特定的适配器
        */
        virtual void AlertLog(const std::string& message
            ,unsigned int unLogPos = NONE_ADAPTER
            ,unsigned int unColor = -1);

        /**
        * @brief 打印FATAL级别的信息
        * @param message [in] 日志信息的内容。 
        * @param unLogPos [in] 日志的流向，指定特定的适配器
        */
        virtual void FatalLog(const std::string& message
            ,unsigned int unLogPos = NONE_ADAPTER
            ,unsigned int unColor = -1);

    protected:
        /**
        * @brief 构建一个Console日志的分类
        * @note 首先创建一个Console的Category，然后确定这个Category的Adapter，
        *       再确定这个Adapter的Layout，最后将三者关系关联起来。
        * @return 成功则返回0，如果返回1，则表示已经存在Console的Category
        */
        int BuildConsoleCategory();

        /**
        * @brief 构建一个File日志的分类
        * @note 首先创建一个Console的Category，然后确定这个Category的Adapter，
        *       再确定这个Adapter的Layout，最后将三者关系关联起来。
        * @return 成功则返回0，如果返回1，则表示已经存在File的Category
        */
        int BuildFileCategory();

//#if defined(_WIN32)   LiPengfei 2014-04-9
        /**
        * @brief 构建一个Debug（IDE)日志的分类
        * @note 首先创建一个Console的Category，然后确定这个Category的Adapter，
        *       再确定这个Adapter的Layout，最后将三者关系关联起来。
        * @return 成功则返回0，如果返回1，则表示已经存在Debug（IDE）的Category
        */
        int BuildDebugCategory();


        /**
        * @brief 构建一个NtEvent日志的分类
        * @note 首先创建一个Console的Category，然后确定这个Category的Adapter，
        *       再确定这个Adapter的Layout，最后将三者关系关联起来。
        * @return 成功则返回0，如果返回1，则表示已经存在NtEvent的Category
        */
        int BuildNteventCategory();

//#endif    LiPengfei 2014-04-9

    public:

        /**
        * @brief 控制日志的开关
        * @note 控制某一个或者多个适配器的开关
        * @param unAdapters [in] 需要进行干预的适配器。
        * @param logswitch [in] 是开启还是关闭指定的适配器。
        */
        void SwitchLogger(unsigned int unAdapters,unsigned int logswitch)throw(std::runtime_error);

    protected:

        /**
        * @brief 读取环境变量
        * @note 读取环境变量，通过环境变量确定初始化的日志分类信息
        */
        virtual int ReadEnv();

        /**
        * @brief 通过指定的适配器获取分类信息
        * @param unAdapters [in] 指定的适配器对象。 
        * @param cates [out] 包含此适配器的所有的分类
        */
        void GetLogCategories(unsigned int unAdapters,LogCategories& cates)throw(std::runtime_error);

    protected:

        friend class CLogFunc;
		OpenThreads::Mutex   m_mutex;

    };


#endif//LOGGER_H
