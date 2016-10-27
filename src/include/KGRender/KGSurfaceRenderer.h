#ifndef _KGRENDRE_H_
#define _KGRENDRE_H_

#include <KGRender/Export.h>
#include <KGGraphs/GraphsMgr.h>
#include <KGShell/CommandMgr.h>

using namespace KGShell;
using namespace KGGraphs;

namespace KGRender
{
	class KGRENDER_EXPORT CKGSurfaceRenderer
	{
	public:
		CKGSurfaceRenderer();
		~CKGSurfaceRenderer();

	protected:
		CKGGraphsMgr* _graphicmgr;
		CKGCommandMgr* _commandmgr;
		
	};
}

#endif