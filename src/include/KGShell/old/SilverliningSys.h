/**************************************************************************************************
* @file SilverliningSys.h
* @note �������Ʋ�����ģ��
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
      * @brief �Ʋ�����ϵͳģ��
      * @note �������Ʋ㹦�ܵ�ϵͳģ��
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
        *@note: ʵ�ֱ�ϵͳģ����Ҫ�ĳ�ʼ���ͷ���ʼ���������˺����ڸ������Ѿ�����
        */
		virtual bool InitiliazeImplement();
        virtual bool UnInitiliazeImplement();
		
    private:
        osg::ref_ptr<FeSilverLining::FeSilverLiningNode>		m_rpSilverLiningNode;
        std::string												m_strSilverLiningPath;
};
}

#endif//SILVERLINING_SYS_H
