/**************************************************************************************************
* @file MeasureSys.h
* @note ��������ɲ������ܵ�ģ��
* @author 00008
* @data 
**************************************************************************************************/

#ifndef HG_MEASURE_SYSTEM_CALL_H
#define HG_MEASURE_SYSTEM_CALL_H

#include <osgGA/GUIEventHandler>

#include <FeShell/Export.h>
#include <FeMeasure/Measure.h>
#include <FeUtils/SceneSysCall.h>

using namespace osgGA;
namespace FeShell
{
	const std::string MEASURE_SYSTEM_CALL_DEFAULT_KEY("MeasureSystem");

    class CMeasureHandler;
    /**
      * @class CMeasureSys
      * @brief �������ܵ�ϵͳģ��
      * @note �����˲������ܵ�ϵͳģ�飬��Ҫ������ֲ����Ĺ���
      * @author l00008
    */
    class FESHELL_EXPORT CMeasureSys : public FeUtil::CSceneSysCall
    {
    public:
        CMeasureSys();

    public:
		typedef enum EMeasureModel
		{
			CONNTINU_MODEL = 0, //��������ģʽ
			ONECE_MODEL = 1,  //���β���ģʽ
		};
		/**
        *@note: ���ò���ģʽ
        */
		void SetMeasureModel(EMeasureModel model);

		/**
        *@note: ��ò���ģʽ
        */
		EMeasureModel GetMeasureModel() const;

        /**
        *@note: ���õ�ǰ��Ĳ���ģ�顣
        */
        void ActiveMeasure(FeMeasure::CMeasure* pMeasure);

		/**
        *@note:����ǰ�Ļ�Ծ��������Ϊ�գ�������ڵ�ǰ�Ļģ�飬
		*	   ����ֹͣ���ӳ������Ƴ���
        */
        void DeactiveMeasure();

		/**
        *@note: ��������Ľ�����������еĽ��ֱ��ɾ��,�˺�����������ģʽ����
        */
		void ClearMesureResult();

    public:
        /**
        *@note: ����ʱ���handler
        */
        bool handle(const GUIEventAdapter& ea, GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor*);

	protected:
		/**
        *@note: ʵ�ֱ�ϵͳģ����Ҫ�ĳ�ʼ���ͷ���ʼ���������˺����ڸ������Ѿ�����
        */
		virtual bool InitiliazeImplement();
        virtual bool UnInitiliazeImplement();

		///���¼�ѭ��
		bool RunEventHandler();

		///�ر��¼�ѭ��
		bool StopEventHandler();

    protected:
        /**
        *@note: ��갴��
        */
        virtual bool MouseDown(float fMouseDownX, float fMouseDownY, GUIEventAdapter::MouseButtonMask mk); 

        /**
        *@note: ���̧��
        */
        virtual bool MouseUp(float fMouseDownX, float fMouseDownY, GUIEventAdapter::MouseButtonMask mk); 
        
        /**
        *@note: ����ƶ�
        */
        virtual bool MouseMove(float fMouseDownX, float fMouseDownY, GUIEventAdapter::MouseButtonMask mk); 
        
        /**
        *@note: ���˫��
        */
        virtual bool MouseDCheck(float fMouseDownX, float fMouseDownY, GUIEventAdapter::MouseButtonMask mk); 

    protected:
        virtual ~CMeasureSys();

        ///�������״̬,����һ�����������Ѿ����
        void SetFinish(bool bState);

		///��ò������ܵ�״̬
        bool IsFinish() const;

    protected:
        /**
        * @class CMeasureHandler
        * @brief �¼�������
        * @note �¼�������
        * @author l00008
        */
        class CMeasureHandler : public GUIEventHandler
        {
        public:
            CMeasureHandler(CMeasureSys* pMeasureSys);

            virtual ~CMeasureHandler();

            virtual bool handle(const GUIEventAdapter& ea, GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor*);

        protected:
            osg::observer_ptr<CMeasureSys>  m_opMeasureSys;
        };

        osg::ref_ptr<CMeasureHandler>					m_rpHandler;   //�¼�������
        osg::ref_ptr<FeMeasure::CMeasure>				m_opCurMeasure; //��ǰִ�еĲ���

        float											m_fMouseDownX;  //��갴�µ�Xλ��
        float											m_fMouseDownY;  //��갴�µ�Yλ��

        bool											m_bFinish;  //�Ƿ����һ�β���

		EMeasureModel									m_eMeasureModel;  //����ģʽ
    };

}

#endif//HG_MEASURE_SYSTEM_CALL_H
