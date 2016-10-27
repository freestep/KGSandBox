#ifndef _LISTENER_H_
#define _LISTENER_H_

#include <KGShell/Export.h>

#include <KGShell/Props.h>

#include <vector>

namespace KGShell
{
	template<typename T>
	class KGSHELL_EXPORT KGListener
	{
	public:
		virtual ~KGListener(){ };
	
	public:
		void valueChanged(const CKGPropertyCell& prop)
		{
			
		}
		
		void register_property(CKGPropertyCell& prop)
		{
			_property.push_back(prop);
		}
		
		void unregister_property(CKGPropertyCell& prop)
		{
			std::vector<CKGPropertyCell>::iterator it = 
				std::find(_property.begin(), _property.end(), prop);
			if (it != _property.end())
			{
				_property.erase(it);
			}
		}

	protected:
		std::vector<CKGPropertyCell> _property;
	};
}

#endif