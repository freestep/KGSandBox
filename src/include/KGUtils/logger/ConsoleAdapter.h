/**************************************************************************************************
* @file ConsoleAdapter.h
* @note 对console输出流的一些属性的拓展 
* @author c00003
* @data 2014-01-05
**************************************************************************************************/

#ifndef CONSOLE_ADAPTER
#define CONSOLE_ADAPTER

#include <log4cpp/OstreamAppender.hh>
using namespace log4cpp;
class CConsoleAdapter : public log4cpp::OstreamAppender
{
public:
    CConsoleAdapter(const std::string name ,std::ostream* stream);
    virtual ~CConsoleAdapter();

protected:
     virtual void _append(const LoggingEvent& event);
};
#endif//CONSOLE_ADAPTER