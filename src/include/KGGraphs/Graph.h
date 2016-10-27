#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <KGGraphs/Export.h>
#include <KGUtils/Common.h>
#include <KGShell/Props.h>

#include <osg/Group>

namespace KGGraphs
{
	class CKGGraphsFactory;
}

namespace KGGraphs
{

	class KGGRAPH_EXPORT CKGGraph : public osg::Group
	{
		friend class CKGGraphsFactory;
	public:
		KG_META_Object(KGGraphs, CKGGraph);

		virtual bool buildGraph();
		
		//说用前需了解。
		//1、deleteGraph意在：
		//（1）释放该类在堆栈上的内存数据；
		//（2）处理变量生命周期在外部不易控制，使用智能指针、share_ptr等不灵活的困扰。
		//2、使用delete this销毁的对象实例只能通过new来申请内存并创建对象实例（实际上对象实例的创建
		//已经被CKGraphFactory规范，确保实例创建与销毁的调用方法的一致性）。
		//3、在调用deleteGraph后，后续代码不在使用该对象实例的非静态成员，也无法用对象实例与NULL比较等指针操作。
		virtual bool deleteGraph();

	protected:
		CKGGraph();
		virtual ~CKGGraph(){}
	};

}
#endif