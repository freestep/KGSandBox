/**************************************************************************************************
* @file FreeSkySys.h
* @note �����˹��չ���ϵͳ
* @author 00008
* @data 
**************************************************************************************************/

#ifndef HG_ENVIRONMENT_SYSTEM_CALL_H
#define HG_ENVIRONMENT_SYSTEM_CALL_H

#include <FeShell/Export.h>
#include <FeUtils/SceneSysCall.h>

#include <FeKits/sky/HgNebula.h>
#include <FeKits/sky/FreeSky.h>

namespace FeShell
{
	const std::string ENVIRONMNET_SYSTEM_CALL_DEFAULT_KEY("FreeSkySystem");

    /**
    * @class CEnvironmentSys
    * @brief ����ϵͳͨ�õ���
    * @note ��������ϵͳ���ã����й�����յ���Ȼ������Ч����
    * @author 00008
    */
    class FESHELL_EXPORT CEnvironmentSys : public FeUtil::CSceneSysCall
    {
    public:
        CEnvironmentSys();

        typedef std::map<std::string, FeKit::CKitsCtrl*> SkyToolList;

    public:
		/**
        *@note: �����սڵ�,��սڵ���ϵͳĬ�ϵĽڵ�
        */
		FeKit::CFreeSky* GetSkyNode();

		/**
        *@note: ����Զ�����ϵ�ڵ�
        */
        FeKit::CKitsCtrl* GetSkyTool(const std::string& strKey);

        /**
        *@note: ���һ���Զ���Ļ����ڵ㵽��������
        */
        bool AddSkyTool(osg::Node* pNode, bool bAddToRoot = true);

		/**
        *@note: �Ƴ��Զ���Ļ����ڵ�ӳ�����
        */
        bool RemoveSkyTool(FeKit::CKitsCtrl* pKitsCtrl);

        /**
        *@note: ���Ŀǰע���ȫ�������ڵ��б�
        */
        SkyToolList GetSkyTools() const;

    protected:
        virtual ~CEnvironmentSys();

		/**
        *@note: ʵ�ֱ�ϵͳģ����Ҫ�ĳ�ʼ���ͷ���ʼ���������˺����ڸ������Ѿ�����
        */
		virtual bool InitiliazeImplement();
        virtual bool UnInitiliazeImplement();

    protected:
        SkyToolList   m_mapTool;
		osg::observer_ptr<FeKit::CFreeSky>    m_opFreeSky;  //����ϵͳ
    };

}

#endif//HG_FREE_SKY_SYSTEM_CALL_H
