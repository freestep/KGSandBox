#ifndef SCENE_SHELL_BOOT_MANAGER_H
#define SCENE_SHELL_BOOT_MANAGER_H

#include <osg/Referenced>
#include <osgViewer/Viewer>

#include <FeShell/SystemSerializer.h>
#include <FeShell/SystemService.h>

namespace FeShell
{
	/**
	* @class CSystemManager
	* @brief 引导管理接口
	* @note 引导管理接口，定义了系统的启动和关闭系统接口
	* @author l00003
	*/
	class FESHELL_EXPORT CSystemManager : public osg::Referenced
	{
	public:
		CSystemManager( const std::string& strResorcePath );

		virtual ~CSystemManager(void);

	public:
		/**
        *@note: 开始场景的渲染事件
        */
		virtual void Frame();

		/**
        *@note: 是否打开按“ESC”退出系统
        */
		virtual void SetESCState(bool bKey);

		/**
		*@note: 初始化渲染系统，指定系统默认的配置资源路径
		*/
		virtual bool Initialize( );

		/**
		*@note: 反初始化场景，将场景中的要素归位，并完成销毁
		*/
		virtual bool UnInitialize();

	public:
		/**
		  * @note 获得相机 x00028
		*/
		virtual osgViewer::Viewer *GetViewer();

		/**
		*@note: 设置渲染系统需要渲染的外部窗口系统
		*/
		virtual bool SetGraphicContext(osg::GraphicsContext* pContext);

		/**
        *@note: 获得系统服务接口
        */
        FeShell::CSystemService* GetSystemService();

		/**
        *@note: 窗口大小改变事件分发
        */
        virtual void ResizeGraphicsContext(int x,int y,int w,int h);

		/**
        *@note: 获得上下文环境配置        
		*/
        virtual osg::GraphicsContext::Traits* 
			CreateTraits(osg::Referenced* pInheritedWindowData, int nX, int nY, int nW, int nH);

		/**
		*@note: 获得作为嵌入式窗口的绘图环境,这个接口和SetGraphicContext互斥
		*/
		virtual osgViewer::GraphicsWindowEmbedded* ViewerAsEmbeddedInWindow();

		FeUtil::CRenderContext* GetRenderContext();

	protected:
		/**
		*@note: 预加载系统，加载系统的配置文件
        */
        virtual bool PreLoadSystemConfig( );

		/**
		*@note: 初始化事件回调系统以及漫游器，在此可以添加缺省的功能回调
		*/
		virtual bool InitEventHandles();

		/**
		*@note: 初始化场景视口信息，根据配置文件初始化地球场景、场景元素系统等
		*/
		virtual bool InitViewerScene();

		/**
		*@note: 初始化服务
		*/
		virtual bool InitService();
		/**

		*@note: 初始化相机信息，设置相机的基础属性并获得渲染窗口
		*/
		virtual bool InitCameraSetting();

		

		/**
		*@note: 初始化图层信息，这些图层都不是Earth文件中配置的图层
		*/
		virtual bool InitCustomLayers();

		/**
		*@note: 初始化完成之后需要个性化的收尾工作
		*/
		virtual bool InitEnd() = 0;

		/**
		*@note: 初始化完成之后需要个性化开始的准备工作;
		*/
		virtual bool InitBegin() = 0;

		/**
        *@note: 一帧开始前的操作，此函数在一帧开始之前调用，有系统自动调用，用户不能够自行调用
        */
		virtual void PreFrame() = 0;

		/**
        *@note: 一帧结束之后的操作，此函数在一帧结束之后调用，有系统自动调用，用户不能够自行调用
        */
		virtual void PostFrame() = 0;
	
	protected:
		bool m_bFirstFrame;											//是否为第一帧
		std::string m_strSystemResoucePath;							//系统的资源路径
		CSysConfig m_systemConfig;									//系统配置文件路径
		osg::ref_ptr<osgViewer::Viewer> m_opViewer;					//渲染的视口
		osg::ref_ptr<CSystemService> m_rpSystemService;				//系统服务接口，主要提供给系统外部
		osg::ref_ptr<FeUtil::CRenderContext> m_opRenderContext;		//渲染服务接口，主要正对系统内部
		

	};

}

#endif//SCENE_SHELL_INTERFACE_H
