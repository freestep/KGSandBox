
#ifndef FE_KERNEL_TINY_XML_UTIL_H
#define FE_KERNEL_TINY_XML_UTIL_H

#include <string>

#include <FeUtils/Export.h>

namespace FeUtil
{
	namespace TinyUtil
	{
		extern FEUTIL_EXPORT bool DataValid(const char* pChar);

		extern FEUTIL_EXPORT std::string ToStdString(const char* pChar) ;

		extern FEUTIL_EXPORT bool AcceptKey(const std::string& strKey, const char* pChar);
	}
}


#endif //FE_KERNEL_TINY_XML_UTIL_H
