/**************************************************************************************************
* @file MeasureSys.h
* @note 定义了组成测量功能的模块
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
      * @brief 测量功能的系统模块
      * @note 定义了测量功能的系统模块，主要管理多种测量的功能
      * @author l00008
    */
    class FESHELL_EXPORT CMeasureSys : public FeUtil::CSceneSysCall
    {
    public:
        CMeasureSys();

    public:
		typedef enum EMeasureModel
		{
			CONNTINU_MODEL = 0, //连续测量模式
			ONECE_MODEL = 1,  //单次测量模式
		};
		/**
        *@note: 设置测量模式
        */
		void SetMeasureModel(EMeasureModel model);

		/**
        *@note: 获得测量模式
        */
		EMeasureModel GetMeasureModel() const;

        /**
        *@note: 设置当前活动的测量模块。
        */
        void ActiveMeasure(FeMeasure::CMeasure* pMeasure);

		/**
        *@note:将当前的活跃测量重置为空，如果存在当前的活动模块，
		*	   则将其停止并从场景中移除。
        */
        void DeactiveMeasure();

		/**
        *@note: 清除测量的结果，将场景中的结果直接删除,此函数仅对连续模式适用
        */
		void ClearMesureResult();

    public:
        /**
        *@note: 处理时间的handler
        */
        bool handle(const GUIEventAdapter& ea, GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor*);

	protected:
		/**
        *@note: 实现本系统模型需要的初始化和反初始化函数，此函数在父类中已经调用
        */
		virtual bool InitiliazeImplement();
        virtual bool UnInitiliazeImplement();

		///打开事件循环
		bool RunEventHandler();

		///关闭事件循环
		bool StopEventHandler();

    protected:
        /**
        *@note: 鼠标按下
        */
        virtual bool MouseDown(float fMouseDownX, float fMouseDownY, GUIEventAdapter::MouseButtonMask mk); 

        /**
        *@note: 鼠标抬起
        */
        virtual bool MouseUp(float fMouseDownX, float fMouseDownY, GUIEventAdapter::MouseButtonMask mk); 
        
        /**
        *@note: 鼠标移动
        */
        virtual bool MouseMove(float fMouseDownX, float fMouseDownY, GUIEventAdapter::MouseButtonMask mk); 
        
        /**
        *@note: 鼠标双击
        */
        virtual bool MouseDCheck(float fMouseDownX, float fMouseDownY, GUIEventAdapter::MouseButtonMask mk); 

    protected:
        virtual ~CMeasureSys();

        ///设置鼠标状态,设置一个测量功能已经完成
        void SetFinish(bool bState);

		///获得测量功能的状态
        bool IsFinish() const;

    protected:
        /**
        * @class CMeasureHandler
        * @brief 事件处理类
        * @note 事件处理类
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

        osg::ref_ptr<CMeasureHandler>					m_rpHandler;   //事件处理器
        osg::ref_ptr<FeMeasure::CMeasure>				m_opCurMeasure; //当前执行的测量

        float											m_fMouseDownX;  //鼠标按下的X位置
        float											m_fMouseDownY;  //鼠标按下的Y位置

        bool											m_bFinish;  //是否结束一次测量

		EMeasureModel									m_eMeasureModel;  //测量模式
    };

}

#endif//HG_MEASURE_SYSTEM_CALL_H
