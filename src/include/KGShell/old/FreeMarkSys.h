/**************************************************************************************************
* @file FreeMarkSys.h
* @note 定义了场景标记系统
* @author 00008
* @date 2015.06.02
**************************************************************************************************/

#ifndef HG_FREE_MARK_SYSTEM_CALL_H
#define HG_FREE_MARK_SYSTEM_CALL_H

#include <osg/Vec3d>
#include <osgEarth/MapNode>


#include <FeExNode/ExternNode.h>
#include <FeExNode/ExPlaceNode.h>
#include <FeExNode/ExModelNode.h>
#include <FeExNode/ExLinesNode.h>
#include <FeExNode/ExPolygonNode.h>
#include <FeUtils/FreeViewPoint.h>
#include <FeShell/Export.h>
#include <FeUtils/SceneSysCall.h>
#include <FeShell/SceneMarkHandler.h>


namespace FeShell
{
	const std::string FREE_MARK_SYSTEM_CALL_DEFAULT_KEY("FreeMarkSystem");

    /**
    * @class CFreeMarkSys
    * @brief 场景标记系统
    * @note 提供了管理场景标记的类，其中统一管理各种场景标记，并提供了添加、删除、修改以及
	*		序列化和反序列化接口。
    * @author 00008
    */
    class FESHELL_EXPORT CFreeMarkSys : public FeUtil::CSceneSysCall
    {
    public:
        CFreeMarkSys(const std::string& strFilePath);

		/**
		*@note: 保存程序场景标记到默认或者是指定的文件中
		*/
		bool Save();
		bool Save(const std::string& strFilePath);

		/**
		*@note: 从默认或者指定的场景标记配置文件中恢复场景节点
		*/
		bool Load();
		bool Load(const std::string& strFilePath);

		/**
		*@note: 获得默认的组节点，所有的场景标记节点在初始都会有一个默认的组
		*		节点，此节点无法被删除、编辑名称、只能在其下面添加其他的组节点
		*		或者叶子节点。
		*/
		FeExNode::CExComposeNode* GetRootMark();

	public:
		/**
		*@note: 添加一个节点到root节点
		*/
		bool AddMark(FeExNode::CExternNode* pMark);
		bool AddMark(FeExNode::CExComposeNode* pParent, FeExNode::CExternNode* pMark);

		/**
		*@note: 删除一个标记点
		*/
		bool RemoveMark(FeExNode::CExternNode* pMark);
		bool RemoveMark(FeExNode::CExComposeNode* pParent, FeExNode::CExternNode* pMark);

		/**
		*@note: 添加一个临时标记点和删除一个临时标记点
		*/
		bool AddTempMark(FeExNode::CExternNode* pMark);
		bool RemoveTempMark(FeExNode::CExternNode* pMark);

		/**
		*@note：将场景中的一个标记对象激活并处于可编辑状态
		*/
		void SetActiveEventInform(FeExNode::CExternNode* pEventInform);

		/**
		*@note：完成场景对象编辑
		*/
		void RemoveActiveEventInform(FeExNode::CExternNode* pEventInform);

		/**
		*@note：将场景中的一个标记对象激活
		*/
		bool SetNodeActive(FeExNode::CExternNode* pExNode);

		/**
		*@note：获得当前的场景中的激活节点
		*/
		FeExNode::CExternNode* GetActivedNode();

    protected:
        virtual ~CFreeMarkSys();

		/**
        *@note: 实现本系统模型需要的初始化和反初始化函数，此函数在父类中已经调用
        */
		virtual bool InitiliazeImplement();
        virtual bool UnInitiliazeImplement();

    protected:
		std::string										m_strFilePath;  //默认的文件路径
		osg::observer_ptr<FeExNode::CExComposeNode>		m_opMarkRoot;  //所有标记的父节点
		osg::observer_ptr<osg::Group>					m_opTempGroup;   //临时节点保存

		osg::ref_ptr<CSceneMarkHandle>					m_rfpSceneMarkEditor;   //处理场景中显示对象的编辑器
    };
}

#endif//HG_FREE_MARK_SYSTEM_CALL_H
