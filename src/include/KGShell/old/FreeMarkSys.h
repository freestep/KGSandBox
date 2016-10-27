/**************************************************************************************************
* @file FreeMarkSys.h
* @note �����˳������ϵͳ
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
    * @brief �������ϵͳ
    * @note �ṩ�˹�������ǵ��࣬����ͳһ������ֳ�����ǣ����ṩ����ӡ�ɾ�����޸��Լ�
	*		���л��ͷ����л��ӿڡ�
    * @author 00008
    */
    class FESHELL_EXPORT CFreeMarkSys : public FeUtil::CSceneSysCall
    {
    public:
        CFreeMarkSys(const std::string& strFilePath);

		/**
		*@note: ������򳡾���ǵ�Ĭ�ϻ�����ָ�����ļ���
		*/
		bool Save();
		bool Save(const std::string& strFilePath);

		/**
		*@note: ��Ĭ�ϻ���ָ���ĳ�����������ļ��лָ������ڵ�
		*/
		bool Load();
		bool Load(const std::string& strFilePath);

		/**
		*@note: ���Ĭ�ϵ���ڵ㣬���еĳ�����ǽڵ��ڳ�ʼ������һ��Ĭ�ϵ���
		*		�ڵ㣬�˽ڵ��޷���ɾ�����༭���ơ�ֻ���������������������ڵ�
		*		����Ҷ�ӽڵ㡣
		*/
		FeExNode::CExComposeNode* GetRootMark();

	public:
		/**
		*@note: ���һ���ڵ㵽root�ڵ�
		*/
		bool AddMark(FeExNode::CExternNode* pMark);
		bool AddMark(FeExNode::CExComposeNode* pParent, FeExNode::CExternNode* pMark);

		/**
		*@note: ɾ��һ����ǵ�
		*/
		bool RemoveMark(FeExNode::CExternNode* pMark);
		bool RemoveMark(FeExNode::CExComposeNode* pParent, FeExNode::CExternNode* pMark);

		/**
		*@note: ���һ����ʱ��ǵ��ɾ��һ����ʱ��ǵ�
		*/
		bool AddTempMark(FeExNode::CExternNode* pMark);
		bool RemoveTempMark(FeExNode::CExternNode* pMark);

		/**
		*@note���������е�һ����Ƕ��󼤻���ڿɱ༭״̬
		*/
		void SetActiveEventInform(FeExNode::CExternNode* pEventInform);

		/**
		*@note����ɳ�������༭
		*/
		void RemoveActiveEventInform(FeExNode::CExternNode* pEventInform);

		/**
		*@note���������е�һ����Ƕ��󼤻�
		*/
		bool SetNodeActive(FeExNode::CExternNode* pExNode);

		/**
		*@note����õ�ǰ�ĳ����еļ���ڵ�
		*/
		FeExNode::CExternNode* GetActivedNode();

    protected:
        virtual ~CFreeMarkSys();

		/**
        *@note: ʵ�ֱ�ϵͳģ����Ҫ�ĳ�ʼ���ͷ���ʼ���������˺����ڸ������Ѿ�����
        */
		virtual bool InitiliazeImplement();
        virtual bool UnInitiliazeImplement();

    protected:
		std::string										m_strFilePath;  //Ĭ�ϵ��ļ�·��
		osg::observer_ptr<FeExNode::CExComposeNode>		m_opMarkRoot;  //���б�ǵĸ��ڵ�
		osg::observer_ptr<osg::Group>					m_opTempGroup;   //��ʱ�ڵ㱣��

		osg::ref_ptr<CSceneMarkHandle>					m_rfpSceneMarkEditor;   //����������ʾ����ı༭��
    };
}

#endif//HG_FREE_MARK_SYSTEM_CALL_H
