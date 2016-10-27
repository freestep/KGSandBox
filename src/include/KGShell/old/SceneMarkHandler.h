
#ifndef HG_ADD_ELEMENT_EVENT_HANDLER_H
#define HG_ADD_ELEMENT_EVENT_HANDLER_H

#include <FeShell/Export.h>

#include <osgGA/GUIEventHandler>

#include <FeExNode/ExFeatureNode.h>

namespace FeShell
{
	class FESHELL_EXPORT CSceneMarkHandle : public osgGA::GUIEventHandler
	{
	public:
		CSceneMarkHandle();
		~CSceneMarkHandle();

		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor*);

	public:
		bool Active() const;

		void SetActiveEventInform(FeExNode::CExternNode* pEventInform);

		void RemoveActiveEventInform();

	protected:
		/**
        *@note: 鼠标按下
        */
        bool MouseDown(float fMouseDownX, float fMouseDownY ,osgViewer::View *pViewer); 

        /**
        *@note: 鼠标左键抬起
        */
        bool LeftMouseUp(float fMouseDownX, float fMouseDownY); 

		/**
        *@note: 撤销上一次绘制
        */
        bool Revoke();

		/**
		*@note: 鼠标中键抬起
		*/
		bool MiddleMouseUp(float fMouseDownX, float fMouseDownY);

		/**
		*@note: 鼠标中键抬起
		*/
		bool MouseMove(float fMouseDownX, float fMouseDownY,osgViewer::View *pViewer);

		/**
		*@note: 鼠标拖拽
		*/
		bool DragEvent(float fMouseDownX, float fMouseDownY,osgViewer::View *pViewer);

	protected:
		osg::observer_ptr<FeExNode::CExternNode>    m_rpCurrentEventInform;

		float    m_fMouseDownX;  //鼠标按下的X位置
		float    m_fMouseDownY;  //鼠标按下的Y位置

		bool    m_bActive;

		bool    m_bPick;
	};
}

#endif//HG_ADD_ELEMENT_EVENT_HANDLER_H
