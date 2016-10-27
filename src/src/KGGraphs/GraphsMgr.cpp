#include <KGGraphs/GraphsMgr.h>
#include <KGGraphs/Line.h>
#include <KGShell/CommandMgr.h>

#include <iostream>

namespace KGGraphs
{
	/// ͼ�ι����ߵ�ʵ��
	bool CKGGraphsMgr::registerGraphType( const std::type_info& info)
	{
		//_name_type_map[info.name()] = ;
		return true;
	}


	bool CKGGraphsMgr::unregisterGraphType( const std::type_info& info)
	{
		return true;
	}


	/// ͼ������������ʵ��
	CKGGraphsFactory::CKGGraphsFactory()
	{
	
	}

	CKGGraphsFactory::~CKGGraphsFactory()
	{

	}

	CKGGraph* CKGGraphsFactory::createGraph_protected( const EGraphType& e)
	{
		if (e == EGraphType_Line)
		{
			return new CKGLine();
		}
		return 0;
	}

// 	CKGLine* CKGGraphsFactory::createLine(  )
// 	{
// 		return new CKGLine();
// 	}

	/// ͼ�ι����ʵ��
	CKGGraphsMgr::CKGGraphsMgr()
	{
		_factory = new CKGGraphsFactory;
	}

	CKGGraphsMgr::~CKGGraphsMgr()
	{
		if (_factory)	delete _factory;  _factory = NULL;
	}

}