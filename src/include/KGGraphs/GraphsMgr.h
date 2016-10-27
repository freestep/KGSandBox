#ifndef _GRAPHSMGR_H_
#define _GRAPHSMGR_H_

#include <KGGraphs/Export.h>
#include <KGGraphs/Graph.h>
#include <KGGraphs/Line.h>

#include <functional>

namespace KGGraphs
{
	///ͼ�����ͣ��ߡ�����Ρ���
	typedef enum EGraphType
	{
		EGraphType_Unspecified = 0,
		EGraphType_Line,
		EGraphType_Polygon,
	}EGraphType;

	
	class CKGGraphsFactory;
	/// ͼ�ι���
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

	///����ͼ�ζ���Ħ˱��ʽ
#define GRAPH_CREATE_FACTORY( _pObj, _pMemFn, _eType)  \
	[=] (const EGraphType& _eType)->CKGGraph* { return ((*_pObj).*_pMemFn)(_eType); }
#define CRAPH_DESTROY_METHOD( _pObj, _pMemFn ) \
	[=] ()-> bool { return ((*_pObj).*_pMemFn)( ); }
	/// ͼ����������
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