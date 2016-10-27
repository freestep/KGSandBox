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
			//非基本类型都应该具有如下方法
			//CKGProperty<osg::Vec4d>与CKGPropertyCell 互转的方法
			//CKGProperty<osg::Vec3d>与CKGPropertyCell 互转的方法
			//CKGProperty<osg::Vec4>与CKGPropertyCell 互转的方法
			//CKGProperty<osg::Vec3>与CKGPropertyCell 互转的方法
			//CKGProperty<osg::Vec2d>与CKGPropertyCell 互转的方法
			//CKGProperty<osg::Vec2>与CKGPropertyCell 互转的方法
			//CKGProperty<osg::Matrixd>与CKGPropertyCell 互转的方法
			//CKGProperty<osg::Matrix>与CKGPropertyCell 互转的方法
			return cellcolor;
			//warning（code:4172） 一个本地的临时变量，会导致返回时出现变量值异常。
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