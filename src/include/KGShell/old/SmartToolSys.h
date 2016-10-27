/**************************************************************************************************
* @file SmartToolSys.h
* @note ������ϵͳ�Ҽ���ͼ��ϵͳ����Ҫ�ǹ���һЩϵͳ�ĹҼ�����ָ���롢��ߡ���γ����ȵȵĽڵ�
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
    * @brief �Ҽ�ϵͳ����
    * @note ����Ҽ���ϵͳ���ò㣬���и��𴴽�Ĭ�ϵĹҼ��Լ���Ϊ�������һЩ������ϵͳ�Ҽ�
    *       ���й����ϵͳ�Ҽ�����̳���ͬһ���ӿ���ʵ��
    * @author 00008
    */
    class FESHELL_EXPORT CSmartToolSys : public FeUtil::CSceneSysCall
    {
    public:
        CSmartToolSys();

        typedef std::map<std::string, FeKit::CKitsCtrl*> SmartToolList;

    public:
		/**
        *@note: ���һ���Ҽ���������
        */
        bool AddSmartTool(FeKit::CKitsCtrl* pKitsCtrl, bool flag = true);

		/**
        *@note: �Ƴ�һ���Ҽ��ӳ�����
        */
        bool RemoveSmartTool(FeKit::CKitsCtrl* pKitsCtrl);
		
		/**
        *@note: ���һ���Ҽ��ӳ�����
        */
        FeKit::CKitsCtrl* GetSmartTool(const std::string& strKey);

        /**
        *@note: ���Ŀǰע���Pendant�����ƺ�ָ��
        */
        SmartToolList GetSmartTools() const;

        /**
        *@note: ���ӿڵĴ�С�ı�ʱ�ı����С
        */
        void ResizeSys(int nW, int nH);

    protected:
		/**
        *@note: ʵ�ֱ�ϵͳģ����Ҫ�ĳ�ʼ���ͷ���ʼ���������˺����ڸ������Ѿ�����
        */
		virtual bool InitiliazeImplement();
        virtual bool UnInitiliazeImplement();

        virtual ~CSmartToolSys();

    protected:
        SmartToolList                         m_mapTool;
    };

}

#endif//HG_PENDANT_VIEW_SYSTEM_CALL_H
