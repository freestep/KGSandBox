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
        *@note: Ԥ����ϵͳ������ϵͳ�������ļ�
        */
        bool PreLoadSystem();

        /**
        *@note: ������Ⱦϵͳ
        */
        virtual bool Run();

        /**
        *@note: ������Ⱦϵͳ
        */
        virtual bool Halt(bool bDone);

        /**
        *@note: Frame�¼��ַ�
        */
        virtual void Frame();

        /**
        *@note: ���ڴ�С�ı��¼��ַ�
        */
        virtual void ResizeGraphicsContext(int x,int y,int w,int h);
		/**
		* @note ���view������ 
		*/
		osgGA::KeySwitchMatrixManipulator* GetSwitchMatrixManipulator();

    protected:
        /**
        *@note: ��ʼ���¼��ص�ϵͳ�Լ����������ڴ˿������ȱʡ�Ĺ��ܻص�
        */
        bool InitEventHandles();

        /**
        *@note: ��ʼ�������ӿ���Ϣ�����������ļ���ʼ�����򳡾�������Ԫ��ϵͳ��
        */
        bool InitViewerScene();
        
        /**
        *@note: ��ʼ�������Ϣ����������Ļ������Բ������Ⱦ����
        */
        bool InitCameraSetting();

        /**
        *@note: ��ʼ��ϵͳԤ�����ģ��ϵͳ
        */
        bool InitSysModule();

        /**
        *@note: ��ô���ϵͳ
        */
        osgViewer::GraphicsWindow* GetGraphicsWindow();

    protected:
        bool m_bAsEmbedded; //�Ƿ�Ƕ�봰��
		osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> m_rpSwitch;
    };


}

#endif//SINGLE_VIEWER_IMPLEMENT_H
