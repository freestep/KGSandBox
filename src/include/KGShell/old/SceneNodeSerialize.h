/**************************************************************************************************
* @file SceneNodeSerialize.h
* @note 定义了场景中对象的保存和读取方法
* @author 00008
* @date 2015.10.30
**************************************************************************************************/

#ifndef HG_SCENE_NODE_SERILIZE_H
#define HG_SCENE_NODE_SERILIZE_H

#include <FeExNode/ExternNode.h>
#include <FeExNode/ExPlaceNode.h>
#include <FeExNode/ExModelNode.h>
#include <FeExNode/ExLinesNode.h>
#include <FeExNode/ExPolygonNode.h>
#include <FeExNode/ExBillboardImage.h>
#include <FeExNode/ExOverLayImage.h>
#include <FeExNode/ExMilitarySignNode.h>

#include <FeUtils/tinyXml/tinyxml.h>
#include <FeUtils/tinyXml/tinyutil.h>
#include <FeUtils/tinyXml/tinystr.h>

#include <FeUtils/FreeViewPoint.h>

#include <FeShell/Export.h>
#include <FeUtils/SceneSysCall.h>
#include <osgEarth/MapNode>
#include <osg/Vec3d>

namespace FeShell
{
	const unsigned int MARK_ROOT_ID = 000000001;
	const std::string MARK_ROOT_TITLE = "MyMarks";

	/**
    * @class CMarkDeserialization
    * @brief 场景标反序列化,将保存在xml文件中的信息反序列化为场景节点
    * @note 提供了场景标记反序列化接口
    * @author 00008
    */
	class FESHELL_EXPORT CMarkDeserialization : public FeUtil::TiXmlVisitor
	{
	public:
		CMarkDeserialization();
		CMarkDeserialization(FeUtil::CRenderContext* pContext);
		virtual ~CMarkDeserialization();

	public:
		/**  
		  * @brief 反序列换接口
		  * @note 将xml序列化文件转化为场景中的节点  
		  * @param pExternNode [inout] 默认的场景标记父节点，由系统开始创建
		  * @param strFilePath [in] xml序列化文件路径
		  * @return 返回值
		*/
		bool Execute(FeExNode::CExComposeNode* pRootNode, const std::string& strFilePath);

	public:
		///进入xml节点
		virtual bool VisitEnter(const FeUtil::TiXmlElement& ele , const FeUtil::TiXmlAttribute* attr);

		///离开xml节点
		virtual bool VisitExit(const FeUtil::TiXmlElement& ele );

	protected:
		void EnterFolderMark( const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr );
		void ExitFolderMark(const FeUtil::TiXmlElement& ele );
		void EnterLineMark( const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr );
		void EnterPolygonMark( const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr );
		void EnterMiliMarkBillboardMark(const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr);
		void EnterMilitaryMarkOverLayMark(const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr);
		void EnterPointMark( const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr );
		void EnterModelMark( const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr );
		void EnterMilitarySignMark( const FeUtil::TiXmlElement& ele, const FeUtil::TiXmlAttribute* attr );

		
		osg::Vec3d ParsePosition(const FeUtil::TiXmlElement& element);
		osg::Vec3d ParsePosture( const FeUtil::TiXmlElement& element );
		osg::Vec3d ParseRScale( const FeUtil::TiXmlElement& element );
		osg::Vec4d ParseColor( const FeUtil::TiXmlElement& ele);
		osg::Vec4d ParseFillColor( const FeUtil::TiXmlElement& ele);
		std::vector<osg::Vec3d> ParseVertex( const FeUtil::TiXmlElement& ele);
		FeUtil::CFreeViewPoint ParseViewPoint(const FeUtil::TiXmlElement& element);
	protected:
		typedef std::vector< osg::ref_ptr<FeExNode::CExComposeNode> >  MarkGroupList;
		MarkGroupList			m_markList; //作为一个保存父节点的列表，只是一个临时的容器

		osg::observer_ptr<FeUtil::CRenderContext>	m_opRenderContext;
	};



    /**
    * @class CMarkSerialization
    * @brief 场景标记序列化，将场景中的节点序列化为xml描述文件
    * @note 提供了场景标记序列化接口
    * @author 00008
    */
	class FESHELL_EXPORT CMarkSerialization : public FeExNode::CExternNodeVisitor
	{
	public:
		CMarkSerialization();
		virtual ~CMarkSerialization();

	public:
		/**  
		  * @brief 序列化
		  * @note 将场景中的节点序列化成为xml文件保存
		  * @param pExternNode [in] 需要序列化的场景Root节点
		  * @param strFilePath [in] 保存序列化xml的路径
		  * @return 返回值
		*/
		bool Execute(FeExNode::CExComposeNode* pExternNode, const std::string& strFilePath);

		virtual bool VisitEnter(FeExNode::CExComposeNode& externNode);
		virtual bool VisitExit(FeExNode::CExComposeNode& externNode);

		virtual bool VisitEnter(FeExNode::CExPlaceNode& externNode);
		virtual bool VisitEnter(FeExNode::CExModelNode& externNode);

		virtual bool VisitEnter(FeExNode::CExLinesNode& externNode);
		virtual bool VisitEnter(FeExNode::CExPolygonNode& externNode);

		virtual bool VisitEnter(FeExNode::CExBillboardImage& externNode);
		virtual bool VisitEnter(FeExNode::CExOverLayImage& externNode);

		virtual bool VisitEnter(FeExNode::ExMilitarySignNode& externNode);

	protected:
		FeUtil::TiXmlElement* BuildViewPointElement(const FeUtil::CFreeViewPoint& viewPoint);

		FeUtil::TiXmlElement* BuildMarkPositionElement(const osg::Vec3d& value);
		FeUtil::TiXmlElement* BuildMarkPostureElement(const osg::Vec3d& value);
		FeUtil::TiXmlElement* BuildMarkScaleElement(const osg::Vec3d& value);
		FeUtil::TiXmlElement* BuildLineColor(const osg::Vec4d& veccolor);
		FeUtil::TiXmlElement* BuildFillColor(const osg::Vec4d& veccolor);

		void BuildVertex(FeUtil::TiXmlElement* pParentElement,std::vector<osg::Vec3d> vecVertexs);
		

	protected:
		typedef std::vector< FeUtil::TiXmlElement* >  MarkGroupList;
		MarkGroupList			m_markList; //作为一个保存父节点的列表，只是一个临时的容器
	};

}

#endif//HG_SCENE_NODE_SERILIZE_H
