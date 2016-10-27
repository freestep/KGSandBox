#include <FeUtils/tinyXml/tinyutil.h>

namespace FeUtil
{
	namespace TinyUtil
	{
		bool DataValid( const char* pChar )
		{
			if(pChar == NULL)
			{
				return false;
			}

			return true;
		}

		std::string ToStdString( const char* pChar )
		{
			std::string str("");
			if(DataValid(pChar))
			{
				str = std::string(pChar);
			}

			return str;
		}

		bool AcceptKey( const std::string& strKey, const char* pChar )
		{
			if(strKey.empty() || ToStdString(pChar) != strKey)
			{
				return false;
			}

			return true;
		}
	}

}