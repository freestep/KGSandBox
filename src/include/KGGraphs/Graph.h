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
		
		//˵��ǰ���˽⡣
		//1��deleteGraph���ڣ�
		//��1���ͷŸ����ڶ�ջ�ϵ��ڴ����ݣ�
		//��2��������������������ⲿ���׿��ƣ�ʹ������ָ�롢share_ptr�Ȳ��������š�
		//2��ʹ��delete this���ٵĶ���ʵ��ֻ��ͨ��new�������ڴ沢��������ʵ����ʵ���϶���ʵ���Ĵ���
		//�Ѿ���CKGraphFactory�淶��ȷ��ʵ�����������ٵĵ��÷�����һ���ԣ���
		//3���ڵ���deleteGraph�󣬺������벻��ʹ�øö���ʵ���ķǾ�̬��Ա��Ҳ�޷��ö���ʵ����NULL�Ƚϵ�ָ�������
		virtual bool deleteGraph();

	protected:
		CKGGraph();
		virtual ~CKGGraph(){}
	};

}
#endif