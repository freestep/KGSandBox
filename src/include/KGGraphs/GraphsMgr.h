#ifndef _GRAPHSMGR_H_
#define _GRAPHSMGR_H_

#include <KGGraphs/Export.h>
#include <KGGraphs/Graph.h>
#include <KGGraphs/Line.h>

#include <functional>

namespace KGGraphs
{
	///图形类型，线、多边形……
	typedef enum EGraphType
	{
		EGraphType_Unspecified = 0,
		EGraphType_Line,
		EGraphType_Polygon,
	}EGraphType;

	
	class CKGGraphsFactory;
	/// 图形管理
	class KGGRAPH_EXPORT CKGGraphsMgr
	{
	public:
		CKGGraphsMgr();
		virtual ~CKGGraphsMgr();

		bool registerGraphType( const std::type_info& );
		bool unregisterGraphType( const std::type_info& );

	public:
		CKGGraphsFactory* _factory;

// 		typedef std::map<std::string, EGraphType> classnametype_map;
// 		classnametype_map _name_type_map; 

	};

	///创建图形对象的λ表达式
#define GRAPH_CREATE_FACTORY( _pObj, _pMemFn, _eType)  \
	[=] (const EGraphType& _eType)->CKGGraph* { return ((*_pObj).*_pMemFn)(_eType); }
#define CRAPH_DESTROY_METHOD( _pObj, _pMemFn ) \
	[=] ()-> bool { return ((*_pObj).*_pMemFn)( ); }
	/// 图形生产工厂
	class KGGRAPH_EXPORT CKGGraphsFactory
	{
	public:
		CKGGraphsFactory();
		virtual ~CKGGraphsFactory();

		CKGGraph* createGraph(const EGraphType& eType)
		{
			std::function<CKGGraph*( const EGraphType&)> func = GRAPH_CREATE_FACTORY( 
				this,
				&CKGGraphsFactory::createGraph_protected,
				eType);

			return func(eType);
		}

		bool destroyGraph(CKGGraph* graph)
		{
 			std::function<bool ()> func = CRAPH_DESTROY_METHOD( 
 				graph, 
 				&CKGGraph::deleteGraph);
 			return func();
		}

	public:
		CKGGraph* createGraph_protected( const EGraphType& );

	//	CKGLine* createLine( );
	};

}

#endif