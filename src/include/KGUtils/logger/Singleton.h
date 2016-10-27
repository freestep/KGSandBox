/**************************************************************************************************
* @file Singleton.h
* @note ����ʵ�ֵĺ궨�壬ֻ�����ඨ����ʹ��SINGLETON_DECLARE(className)����ʵ����ʹ��
*       SINGLETON_IMPLEMENT(className)������ʵ�ֵ�����
* @author c00005
* @data 2015-7-8
**************************************************************************************************/
#ifndef SINGLETON_H
#define SINGLETON_H

#include <map>
//////////////////////////////////////////////////////////////////////////
#ifndef SINGLETON_DECLARE
#define SINGLETON_DECLARE(className)\
    protected:\
        className();\
        ~className();\
    public:\
        static className* Instance();\
        static void Release();\
    protected:\
		class CAutoDestoryInstance\
		{\
			public:\
				CAutoDestoryInstance(){}\
				~CAutoDestoryInstance()\
				{\
					className::Release();\
				}\
		};\
		static CAutoDestoryInstance destroy;\
	protected:\
		static className* m_pInstance;
#endif//HG_SINGLETON

#ifndef SINGLETON_IMPLEMENT
#define SINGLETON_IMPLEMENT(className)\
    className* className::m_pInstance = 0;\
	className::CAutoDestoryInstance className::destroy;\
    className::className(){}\
    className::~className(){}\
    className* className::Instance()\
    {\
        if( NULL == className::m_pInstance)\
        {\
            className::m_pInstance = new className();\
        }\
        return className::m_pInstance;\
    }\
    void className::Release()\
    {\
        if( NULL != className::m_pInstance)\
        {\
            delete className::m_pInstance;\
            className::m_pInstance = 0;\
        }\
    }
#endif//SINGLETON_IMPLEMENT
//////////////////////////////////////////////////////////////////////////

#ifndef SINGLETON_IMPLEMENT_NOCD
#define SINGLETON_IMPLEMENT_NOCD(className)\
	className* className::m_pInstance = 0;\
	className::CAutoDestoryInstance className::destroy;\
	className* className::Instance()\
	{\
	if( NULL == className::m_pInstance)\
		{\
		className::m_pInstance = new className();\
		}\
		return className::m_pInstance;\
	}\
	void className::Release()\
	{\
	if( NULL != className::m_pInstance)\
		{\
		delete className::m_pInstance;\
		className::m_pInstance = 0;\
		}\
	}
#endif//SINGLETON_IMPLEMENT_NOCD

//////////////////////////////////////////////////////////////////////////

#ifndef MULTITON_DECLEAR
#define MULTITON_DECLEAR(className)\
    protected:\
        className();\
        ~className();\
    public:\
        static className* Instance(const string& symbol);\
        static void Release();\
	protected:\
		class CAutoDestoryInstance\
		{\
			public:\
				CAutoDestoryInstance(){}\
				~CAutoDestoryInstance()\
				{\
					className::Release();\
				}\
		};\
		static CAutoDestoryInstance destroy;\
    protected:\
        static std::map<string,className*> mapInst;
#endif//MULTITON_DECLEAR

#ifndef MULTITON_IMPLEMENT
#define MULTITON_IMPLEMENT(className)\
    className* className::m_pInstance = 0;\
	className::CAutoDestoryInstance className::destroy;\
    className::className(){}\
    className::~className(){}\
    className* className::Instance(const string& symbol)\
    {\
        if( 0!= mapInst.count(symbol))\
        {\
            return mapInst[symbol];\
        }\
        if( NULL == className::m_pInstance)\
        {\
            className* pInst = new className();\
            mapInst[symbol]=pInst;\
        }\
        return className::m_pInstance;\
    }\
    void className::Release()\
    {\
        std::map<string,className*>::iterator it = mapInst.begin();\
        for( ; it != mapInst.end() ; it++)\
        {\
            if(it->second)\
            {\
                delete it->second;\
            }\
        }\
    }
#endif// MULTITON_IMPLEMENT

#endif//SINGLETON_H
