#ifndef _KGLINE_H_
#define _KGLINE_H_

#include <KGGraphs/Export.h>
#include <KGGraphs/Graph.h>
#include <KGShell/Props.h>
#include <KGUtils/Common.h>

using namespace KGShell;

namespace KGGraphs
{
	class CKGGraphsFactory;
}

namespace KGGraphs
{
	class KGGRAPH_EXPORT CKGLine : public CKGGraph
	{
		friend class CKGGraphsFactory;
	public:
		KG_META_Object(KGGraphs, CKGLine);

		virtual bool buildGraph();



		bool setColor(CKGPropertyCell );

		CKGPropertyCell getColor() const{ 
			CKGPropertyCell cellcolor("color");
			//�ǻ������Ͷ�Ӧ�þ������·���
			//CKGProperty<osg::Vec4d>��CKGPropertyCell ��ת�ķ���
			//CKGProperty<osg::Vec3d>��CKGPropertyCell ��ת�ķ���
			//CKGProperty<osg::Vec4>��CKGPropertyCell ��ת�ķ���
			//CKGProperty<osg::Vec3>��CKGPropertyCell ��ת�ķ���
			//CKGProperty<osg::Vec2d>��CKGPropertyCell ��ת�ķ���
			//CKGProperty<osg::Vec2>��CKGPropertyCell ��ת�ķ���
			//CKGProperty<osg::Matrixd>��CKGPropertyCell ��ת�ķ���
			//CKGProperty<osg::Matrix>��CKGPropertyCell ��ת�ķ���
			return cellcolor;
			//warning��code:4172�� һ�����ص���ʱ�������ᵼ�·���ʱ���ֱ���ֵ�쳣��
		}

	protected:
		CKGLine();
		~CKGLine();

		bool set_color( const CKGProperty<osg::Vec4d>& color );

	public:
		CKGProperty<osg::Vec4d> _linecolor;
	//	CKGRawValueMethod<CKGLine, CKGPropertyCell> _linecolor;

	//	KG_PROPERTY("linecolor", CKGLine, CKGPropertyCell)
	};
}


#endif