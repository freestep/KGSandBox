#include <KGUtils/Common.h>

namespace KGUtil
{
	///ActivateTransparencyOnType 实现
	ActivateTransparencyOnType::ActivateTransparencyOnType(const std::type_info& t, const ERenderBin renderorder): _t(t), _renderorder(renderorder) { }
	void ActivateTransparencyOnType::operator()(osg::Node* nptr) const
	{
		if(typeid(*nptr)==_t)
		{
			osg::StateSet* ss = nptr->getOrCreateStateSet();
			ss->setRenderBinDetails(_renderorder, "DepthSortedBin");
			ss->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
			ss->setMode(GL_BLEND,osg::StateAttribute::ON | osg::StateAttribute::PROTECTED | osg::StateAttribute::OVERRIDE);
			ss->setMode(GL_LIGHTING,osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED | osg::StateAttribute::OVERRIDE);
		}
	}

	///DeactivateTransparencyOnType 实现
	DeactivateTransparencyOnType::DeactivateTransparencyOnType(const std::type_info& t, const ERenderBin renderorder): _t(t), _renderorder(renderorder) { }
	void DeactivateTransparencyOnType::operator()(osg::Node* nptr) const
	{
		if(typeid(*nptr)==_t)
		{
			osg::StateSet* ss = nptr->getOrCreateStateSet();
			ss->setRenderBinDetails(_renderorder, "RenderBin");
			ss->setRenderingHint(osg::StateSet::OPAQUE_BIN);
			ss->setMode(GL_BLEND,osg::StateAttribute::ON | osg::StateAttribute::PROTECTED | osg::StateAttribute::OVERRIDE);
			ss->setMode(GL_LIGHTING,osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED | osg::StateAttribute::OVERRIDE);
		}
	}

}