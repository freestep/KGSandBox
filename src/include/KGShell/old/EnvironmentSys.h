/**************************************************************************************************
* @file FreeSkySys.h
* @note 定义了光照管理系统
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
    * @brief 环境系统通用调用
    * @note 管理环境的系统调用，其中管理光照等自然的天气效果。
    * @author 00008
    */
    class FESHELL_EXPORT CEnvironmentSys : public FeUtil::CSceneSysCall
    {
    public:
        CEnvironmentSys();

        typedef std::map<std::string, FeKit::CKitsCtrl*> SkyToolList;

    public:
		/**
        *@note: 获得天空节点,天空节点是系统默认的节点
        */
		FeKit::CFreeSky* GetSkyNode();

		/**
        *@note: 获得自定义星系节点
        */
        FeKit::CKitsCtrl* GetSkyTool(const std::string& strKey);

        /**
        *@note: 添加一个自定义的环境节点到到场景中
        */
        bool AddSkyTool(osg::Node* pNode, bool bAddToRoot = true);

		/**
        *@note: 移除自定义的环境节点从场景中
        */
        bool RemoveSkyTool(FeKit::CKitsCtrl* pKitsCtrl);

        /**
        *@note: 获得目前注册的全部环境节点列表
        */
        SkyToolList GetSkyTools() const;

    protected:
        virtual ~CEnvironmentSys();

		/**
        *@note: 实现本系统模型需要的初始化和反初始化函数，此函数在父类中已经调用
        */
		virtual bool InitiliazeImplement();
        virtual bool UnInitiliazeImplement();

    protected:
        SkyToolList   m_mapTool;
		osg::observer_ptr<FeKit::CFreeSky>    m_opFreeSky;  //光照系统
    };

}

#endif//HG_FREE_SKY_SYSTEM_CALL_H
