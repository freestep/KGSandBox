/**************************************************************************************************
* @file MeasureSys.h
* @note ��������ɲ������ܵ�ģ��
* @author 00008
* @data 
**************************************************************************************************/

#ifndef OCEAN_SYS_H
#define OCEAN_SYS_H

#include <FeShell/Export.h>
#include <FeOcean/TritonNode.h>
#include <FeShell/SystemManager.h>

#include <FeUtils/SceneSysCall.h>

using namespace osgGA;

namespace FeShell
{
	const std::string OCEAN_SYSTEM_CALL_DEFAULT_KEY("OceanSystem");

    /**
      * @class CMeasureSys
      * @brief �������ܵ�ϵͳģ��
      * @note �����˲������ܵ�ϵͳģ�飬��Ҫ������ֲ����Ĺ���
      * @author l00008
    */
    class FESHELL_EXPORT COceanSys : public FeUtil::CSceneSysCall
    {
    public:
		COceanSys();
        COceanSys(const std::string& strTritonPath);
        ~COceanSys();

    public:
        FeOcean::TritonNode * GetOceanNode();

		bool Initialize(FeShell::CSystemService * pService);

	protected:
		/**
        *@note: ʵ�ֱ�ϵͳģ����Ҫ�ĳ�ʼ���ͷ���ʼ���������˺����ڸ������Ѿ�����
        */
		virtual bool InitiliazeImplement();
        virtual bool UnInitiliazeImplement();
		
    private:
        osg::ref_ptr<FeOcean::TritonNode>		m_rpTritonNode;
        std::string                             m_strTritonPath;
};
}

#endif//HG_MEASURE_SYSTEM_CALL_H
