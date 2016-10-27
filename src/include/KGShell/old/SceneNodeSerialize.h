/**************************************************************************************************
* @file SceneNodeSerialize.h
* @note �����˳����ж���ı���Ͷ�ȡ����
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
    * @brief �����귴���л�,��������xml�ļ��е���Ϣ�����л�Ϊ�����ڵ�
    * @note �ṩ�˳�����Ƿ����л��ӿ�
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
		  * @brief �����л��ӿ�
		  * @note ��xml���л��ļ�ת��Ϊ�����еĽڵ�  
		  * @param pExternNode [inout] Ĭ�ϵĳ�����Ǹ��ڵ㣬��ϵͳ��ʼ����
		  * @param strFilePath [in] xml���л��ļ�·��
		  * @return ����ֵ
		*/
		bool Execute(FeExNode::CExComposeNode* pRootNode, const std::string& strFilePath);

	public:
		///����xml�ڵ�
		virtual bool VisitEnter(const FeUtil::TiXmlElement& ele , const FeUtil::TiXmlAttribute* attr);

		///�뿪xml�ڵ�
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
		MarkGroupList			m_markList; //��Ϊһ�����游�ڵ���б�ֻ��һ����ʱ������

		osg::observer_ptr<FeUtil::CRenderContext>	m_opRenderContext;
	};



    /**
    * @class CMarkSerialization
    * @brief ����������л����������еĽڵ����л�Ϊxml�����ļ�
    * @note �ṩ�˳���������л��ӿ�
    * @author 00008
    */
	class FESHELL_EXPORT CMarkSerialization : public FeExNode::CExternNodeVisitor
	{
	public:
		CMarkSerialization();
		virtual ~CMarkSerialization();

	public:
		/**  
		  * @brief ���л�
		  * @note �������еĽڵ����л���Ϊxml�ļ�����
		  * @param pExternNode [in] ��Ҫ���л��ĳ���Root�ڵ�
		  * @param strFilePath [in] �������л�xml��·��
		  * @return ����ֵ
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
		MarkGroupList			m_markList; //��Ϊһ�����游�ڵ���б�ֻ��һ����ʱ������
	};

}

#endif//HG_SCENE_NODE_SERILIZE_H
