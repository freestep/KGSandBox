/**************************************************************************************************
* @file SilverliningSys.h
* @note 定义了云层管理的模块
* @author z00013
* @data 
**************************************************************************************************/

#ifndef SILVERLINING_SYS_H
#define SILVERLINING_SYS_H

#include <FeShell/Export.h>
#include <FeSilverlining/SilverLiningNode.h>
#include <FeShell/SystemManager.h>

#include <FeUtils/SceneSysCall.h>


namespace FeShell
{
	const std::string SILVERLINING_CALL_DEFAULT_KEY("SilverLiningSystem");

    /**
      * @class CSilverLiningSys
      * @brief 云层管理的系统模块
      * @note 定义了云层功能的系统模块
      * @author z00013
    */
    class FESHELL_EXPORT CSilverLiningSys : public FeUtil::CSceneSysCall
    {
    public:
		CSilverLiningSys();
        CSilverLiningSys(const std::string& strSilverLiningPath);
        ~CSilverLiningSys();

    public:
        FeSilverLining::FeSilverLiningNode * GetSilverLiningNode();

	protected:
		/**
        *@note: 实现本系统模型需要的初始化和反初始化函数，此函数在父类中已经调用
        */
		virtual bool InitiliazeImplement();
        virtual bool UnInitiliazeImplement();
		
    private:
        osg::ref_ptr<FeSilverLining::FeSilverLiningNode>		m_rpSilverLiningNode;
        std::string												m_strSilverLiningPath;
};
}

#endif//SILVERLINING_SYS_H
