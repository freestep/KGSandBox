#include <KGShell/Props.h>
#include <KGUtils/Common.h>
#include <KGRender/KGSurfaceRenderer.h>

using namespace KGShell;
using namespace KGGraphs;
using namespace KGUtil;
using namespace KGRender;
using namespace std;

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Texture2D>
#include <osg/CullFace>
#include <osg/Uniform>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>
#include <osgDB/ReadFile>
//demo 
enum ETexIndex
{
	ETexIndex_TEX0 = 0,
	ETexIndex_TEX1,
	ETexIndex_TEX2,
	ETexIndex_TEX3,
};

const char* vss = {
	"uniform sampler2D depthSampler; \n"
	"varying vec4 finalColor; \n"
	"void main() \n"
	"{ \n"
	"   gl_TexCoord[0] = gl_MultiTexCoord0;"
	"   finalColor = texture2D(depthSampler, gl_TexCoord[0].st); \n"
	"   float depth = finalColor.g; \n"
	"   vec4 v = gl_Vertex; \n"
	"   v.z = (depth*255.0-125.0) * 0.1; \n "
	"   gl_Position = gl_ModelViewProjectionMatrix * v; \n"
	"} \n"
};

const char* fss = {
	"varying vec4 finalColor; \n"
	"void main() \n"
	"{ \n"
	"   gl_FragColor = finalColor; \n"
	"} \n"
};

//w, h没做判断。 所以w,h传入时要大于1
osg::Geode* drawGrid(unsigned int w, unsigned int h)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	osg::ref_ptr<osg::Vec2Array> texCoords = new osg::Vec2Array;

	for (int j = 0; j < h - 1; j++)
	{
		for (int i = 0; i < w; i++)
		{
			vertices->push_back(osg::Vec3(i, j, 0));
			vertices->push_back(osg::Vec3(i, j + 1, 0));

			texCoords->push_back(osg::Vec2(double(i) / double(w), double(j) / double(h)));
			texCoords->push_back(osg::Vec2(double(i) / double(w), double(j+1) / double(h)));
		}
	}

	colors->push_back(osg::Vec4(1, 1, 1, 1));

	geom->setVertexArray(vertices);
	geom->setColorArray(colors);
	geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	geom->setTexCoordArray(ETexIndex_TEX0, texCoords);

	for (int i = 0; i < h - 1; i++)
	{
		geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUAD_STRIP, w*i * 2, w * 2));
	}
// 	unsigned char* data = new unsigned char[w * h * 4];
// 	memset(data, 0, w * h * 4 * sizeof(unsigned char));
// 
// 	osg::ref_ptr<osg::Image> image = new osg::Image;
// 	image->setImage(w, h, 1, 4, GL_RGBA, GL_UNSIGNED_BYTE, data, osg::Image::NO_DELETE);
		
	osg::ref_ptr<osg::Image> image = osgDB::readImageFile("D:/1.bmp");

	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
	texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
	texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	texture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
	texture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
	texture->setImage(image);
	geom->getOrCreateStateSet()->setTextureAttribute(0, texture);
	geom->setUseVertexBufferObjects(true);
	geom->setUseDisplayList(false);

	geode->addDrawable(geom);
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED | osg::StateAttribute::OVERRIDE);
	geode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED | osg::StateAttribute::OVERRIDE);
//	osg::ref_ptr<osg::CullFace> cullface = new osg::CullFace();
//	cullface->setMode(osg::CullFace::FRONT);
 //   geode->getOrCreateStateSet()->setAttributeAndModes(cullface, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED | osg::StateAttribute::OVERRIDE );

	osg::ref_ptr<osg::Program> program = new osg::Program;
	osg::ref_ptr<osg::Shader> vs = new osg::Shader(osg::Shader::Type::VERTEX, vss);
	osg::ref_ptr<osg::Shader> fs = new osg::Shader(osg::Shader::Type::FRAGMENT, fss);
	osg::ref_ptr<osg::Uniform> depthSampler = new osg::Uniform("depthSampler", 0);
	geode->getOrCreateStateSet()->addUniform(depthSampler);
	program->addShader(vs);
	program->addShader(fs);
	geode->getOrCreateStateSet()->setAttributeAndModes(program, osg::StateAttribute::ON);
 
	geode->dirtyBound();

	return geode.release();

}


int main()
{
	CKGSurfaceRenderer* render = new CKGSurfaceRenderer();

	CKGGraphsMgr* graphMgr = new CKGGraphsMgr();
	
	CKGLine* line = dynamic_cast<CKGLine*>(graphMgr->_factory->createGraph(EGraphType_Line));

 	CKGPropertyCell colorcell("color");
 	colorcell.setValue<float>(true);

	//1. 命令源模式设置线的属性
	//获取line对象的id : 20160523172401_line
	const std::string id = "20160523172401_line";
	CMD()->execute(id+"color", colorcell);
	//2. 别名（反射）模式设置线的属性
	CKGRawValueMethod<CKGLine, CKGPropertyCell> linecolor(line, &CKGLine::getColor, &CKGLine::setColor);
	linecolor = colorcell;
    colorcell = linecolor();

	osgViewer::Viewer viewer;
	viewer.addEventHandler(new osgViewer::StatsHandler);
	viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
	osg::Node* node = drawGrid(512, 424);
	viewer.setSceneData(node);
	//viewer.getCamera()->setCullingMode(osg::CullSettings::ENABLE_ALL_CULLING);
	//viewer.getCamera()->setComputeNearFarMode(osg::CullSettings::COMPUTE_NEAR_USING_PRIMITIVES);
	viewer.run();
	return 0;
}