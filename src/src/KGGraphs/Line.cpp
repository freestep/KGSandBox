#include <KGGraphs/Line.h>
#include <KGShell/CommandMgr.h>


using namespace KGShell;

namespace KGGraphs
{
	CKGLine::CKGLine()
	{
		///��ID����������ID��ʱ��_ͼ������
		const std::string id = "20160523172401_line";
		CMD()->addCommand(id+"color", this, &CKGLine::setColor);

		ACTIVE_TRANSPARENCY(typeid(CKGLine), ERenderBin_GEOM, this);
	}

	CKGLine::~CKGLine()
	{
		const std::string id = "20160523172401_line";
		CMD()->removeCommand(id+"color");
	}

	bool CKGLine::buildGraph()
	{
		return true;
	}

	bool CKGLine::setColor( CKGPropertyCell color )
	{
		std::cout<<"������������ɫ"<<std::endl;
		///������color�е�rgba
		const CKGProperty<osg::Vec4d> kgprop_color = osg::Vec4d(1.f,1.f,1.f,1.f);
		return set_color(kgprop_color);
	}


	bool CKGLine::set_color( const CKGProperty<osg::Vec4d>& color )
	{
		osg::Vec4d veccolor = color.value();
		return true;
	}

}