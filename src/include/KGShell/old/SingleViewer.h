#ifndef SINGLE_VIEWER_IMPLEMENT_H
#define SINGLE_VIEWER_IMPLEMENT_H

#include <osgViewer/Viewer>

#include <osgEarth/DateTime>

#include <osgGA/KeySwitchMatrixManipulator>

#include <FeShell/Export.h>
#include <FeShell/SceneShell.h>
#include <FeShell/EventDispatch.h>


namespace FeShell
{
    class FESHELL_EXPORT CSingleViewer : 
        public CSceneShell,
        public CEventDispatch,
        public osgViewer::Viewer
    {
    public:
        CSingleViewer(bool bAsEmbedded);

        virtual ~CSingleViewer(void);

    public:
        /**
        *@note: 预加载系统，加载系统的配置文件
        */
        bool PreLoadSystem();

        /**
        *@note: 启动渲染系统
        */
        virtual bool Run();

        /**
        *@note: 结束渲染系统
        */
        virtual bool Halt(bool bDone);

        /**
        *@note: Frame事件分发
        */
        virtual void Frame();

        /**
        *@note: 窗口大小改变事件分发
        */
        virtual void ResizeGraphicsContext(int x,int y,int w,int h);
		/**
		* @note 获得view操作器 
		*/
		osgGA::KeySwitchMatrixManipulator* GetSwitchMatrixManipulator();

    protected:
        /**
        *@note: 初始化事件回调系统以及漫游器，在此可以添加缺省的功能回调
        */
        bool InitEventHandles();

        /**
        *@note: 初始化场景视口信息，根据配置文件初始化地球场景、场景元素系统等
        */
        bool InitViewerScene();
        
        /**
        *@note: 初始化相机信息，设置相机的基础属性并获得渲染窗口
        */
        bool InitCameraSetting();

        /**
        *@note: 初始化系统预定义的模块系统
        */
        bool InitSysModule();

        /**
        *@note: 获得窗口系统
        */
        osgViewer::GraphicsWindow* GetGraphicsWindow();

    protected:
        bool m_bAsEmbedded; //是否嵌入窗口
		osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> m_rpSwitch;
    };


}

#endif//SINGLE_VIEWER_IMPLEMENT_H
