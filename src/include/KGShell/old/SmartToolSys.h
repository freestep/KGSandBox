/**************************************************************************************************
* @file SmartToolSys.h
* @note 定义了系统挂件视图的系统，主要是管理一些系统的挂件，如指北针、标尺、经纬网格等等的节点
* @author 00008
* @data 
**************************************************************************************************/

#ifndef HG_PENDANT_VIEW_SYSTEM_CALL_H
#define HG_PENDANT_VIEW_SYSTEM_CALL_H

#include <FeShell/Export.h>
#include <FeUtils/SceneSysCall.h>
#include <FeKits/KitsCtrl.h>

namespace FeShell
{
	const std::string SMART_TOOL_SYSTEM_CALL_DEFAULT_KEY("SmartToolSystem");

    /**
    * @class CPendantViewSys
    * @brief 挂件系统调用
    * @note 管理挂件的系统调用层，其中负责创建默认的挂件以及作为容器添加一些其他的系统挂件
    *       其中管理的系统挂件必须继承自同一个接口来实现
    * @author 00008
    */
    class FESHELL_EXPORT CSmartToolSys : public FeUtil::CSceneSysCall
    {
    public:
        CSmartToolSys();

        typedef std::map<std::string, FeKit::CKitsCtrl*> SmartToolList;

    public:
		/**
        *@note: 添加一个挂件到场景中
        */
        bool AddSmartTool(FeKit::CKitsCtrl* pKitsCtrl, bool flag = true);

		/**
        *@note: 移除一个挂件从场景中
        */
        bool RemoveSmartTool(FeKit::CKitsCtrl* pKitsCtrl);
		
		/**
        *@note: 获得一个挂件从场景中
        */
        FeKit::CKitsCtrl* GetSmartTool(const std::string& strKey);

        /**
        *@note: 获得目前注册的Pendant的名称和指针
        */
        SmartToolList GetSmartTools() const;

        /**
        *@note: 当视口的大小改变时改变其大小
        */
        void ResizeSys(int nW, int nH);

    protected:
		/**
        *@note: 实现本系统模型需要的初始化和反初始化函数，此函数在父类中已经调用
        */
		virtual bool InitiliazeImplement();
        virtual bool UnInitiliazeImplement();

        virtual ~CSmartToolSys();

    protected:
        SmartToolList                         m_mapTool;
    };

}

#endif//HG_PENDANT_VIEW_SYSTEM_CALL_H
