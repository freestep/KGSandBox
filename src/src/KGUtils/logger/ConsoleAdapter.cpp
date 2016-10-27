
#include <logger/ConsoleAdapter.h>


CConsoleAdapter::CConsoleAdapter(const std::string name ,std::ostream* stream)
    :log4cpp::OstreamAppender(name,stream)
{

}

CConsoleAdapter::~CConsoleAdapter()
{
    //log4cpp::OstreamAppender::~OstreamAppender();
}

void CConsoleAdapter::_append(const LoggingEvent&event)
{
    log4cpp::OstreamAppender::_append(event);
}

