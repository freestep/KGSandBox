/**************************************************************************************************
* @file MeasureSys.h
* @note 定义了组成测量功能的模块
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
      * @brief 测量功能的系统模块
      * @note 定义了测量功能的系统模块，主要管理多种测量的功能
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
        *@note: 实现本系统模型需要的初始化和反初始化函数，此函数在父类中已经调用
        */
		virtual bool InitiliazeImplement();
        virtual bool UnInitiliazeImplement();
		
    private:
        osg::ref_ptr<FeOcean::TritonNode>		m_rpTritonNode;
        std::string                             m_strTritonPath;
};
}

#endif//HG_MEASURE_SYSTEM_CALL_H
