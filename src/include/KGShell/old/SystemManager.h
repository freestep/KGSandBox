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
	* @brief ��������ӿ�
	* @note ��������ӿڣ�������ϵͳ�������͹ر�ϵͳ�ӿ�
	* @author l00003
	*/
	class FESHELL_EXPORT CSystemManager : public osg::Referenced
	{
	public:
		CSystemManager( const std::string& strResorcePath );

		virtual ~CSystemManager(void);

	public:
		/**
        *@note: ��ʼ��������Ⱦ�¼�
        */
		virtual void Frame();

		/**
        *@note: �Ƿ�򿪰���ESC���˳�ϵͳ
        */
		virtual void SetESCState(bool bKey);

		/**
		*@note: ��ʼ����Ⱦϵͳ��ָ��ϵͳĬ�ϵ�������Դ·��
		*/
		virtual bool Initialize( );

		/**
		*@note: ����ʼ���������������е�Ҫ�ع�λ�����������
		*/
		virtual bool UnInitialize();

	public:
		/**
		  * @note ������ x00028
		*/
		virtual osgViewer::Viewer *GetViewer();

		/**
		*@note: ������Ⱦϵͳ��Ҫ��Ⱦ���ⲿ����ϵͳ
		*/
		virtual bool SetGraphicContext(osg::GraphicsContext* pContext);

		/**
        *@note: ���ϵͳ����ӿ�
        */
        FeShell::CSystemService* GetSystemService();

		/**
        *@note: ���ڴ�С�ı��¼��ַ�
        */
        virtual void ResizeGraphicsContext(int x,int y,int w,int h);

		/**
        *@note: ��������Ļ�������        
		*/
        virtual osg::GraphicsContext::Traits* 
			CreateTraits(osg::Referenced* pInheritedWindowData, int nX, int nY, int nW, int nH);

		/**
		*@note: �����ΪǶ��ʽ���ڵĻ�ͼ����,����ӿں�SetGraphicContext����
		*/
		virtual osgViewer::GraphicsWindowEmbedded* ViewerAsEmbeddedInWindow();

		FeUtil::CRenderContext* GetRenderContext();

	protected:
		/**
		*@note: Ԥ����ϵͳ������ϵͳ�������ļ�
        */
        virtual bool PreLoadSystemConfig( );

		/**
		*@note: ��ʼ���¼��ص�ϵͳ�Լ����������ڴ˿������ȱʡ�Ĺ��ܻص�
		*/
		virtual bool InitEventHandles();

		/**
		*@note: ��ʼ�������ӿ���Ϣ�����������ļ���ʼ�����򳡾�������Ԫ��ϵͳ��
		*/
		virtual bool InitViewerScene();

		/**
		*@note: ��ʼ������
		*/
		virtual bool InitService();
		/**

		*@note: ��ʼ�������Ϣ����������Ļ������Բ������Ⱦ����
		*/
		virtual bool InitCameraSetting();

		

		/**
		*@note: ��ʼ��ͼ����Ϣ����Щͼ�㶼����Earth�ļ������õ�ͼ��
		*/
		virtual bool InitCustomLayers();

		/**
		*@note: ��ʼ�����֮����Ҫ���Ի�����β����
		*/
		virtual bool InitEnd() = 0;

		/**
		*@note: ��ʼ�����֮����Ҫ���Ի���ʼ��׼������;
		*/
		virtual bool InitBegin() = 0;

		/**
        *@note: һ֡��ʼǰ�Ĳ������˺�����һ֡��ʼ֮ǰ���ã���ϵͳ�Զ����ã��û����ܹ����е���
        */
		virtual void PreFrame() = 0;

		/**
        *@note: һ֡����֮��Ĳ������˺�����һ֡����֮����ã���ϵͳ�Զ����ã��û����ܹ����е���
        */
		virtual void PostFrame() = 0;
	
	protected:
		bool m_bFirstFrame;											//�Ƿ�Ϊ��һ֡
		std::string m_strSystemResoucePath;							//ϵͳ����Դ·��
		CSysConfig m_systemConfig;									//ϵͳ�����ļ�·��
		osg::ref_ptr<osgViewer::Viewer> m_opViewer;					//��Ⱦ���ӿ�
		osg::ref_ptr<CSystemService> m_rpSystemService;				//ϵͳ����ӿڣ���Ҫ�ṩ��ϵͳ�ⲿ
		osg::ref_ptr<FeUtil::CRenderContext> m_opRenderContext;		//��Ⱦ����ӿڣ���Ҫ����ϵͳ�ڲ�
		

	};

}

#endif//SCENE_SHELL_INTERFACE_H
