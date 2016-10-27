
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
        *@note: ��갴��
        */
        bool MouseDown(float fMouseDownX, float fMouseDownY ,osgViewer::View *pViewer); 

        /**
        *@note: ������̧��
        */
        bool LeftMouseUp(float fMouseDownX, float fMouseDownY); 

		/**
        *@note: ������һ�λ���
        */
        bool Revoke();

		/**
		*@note: ����м�̧��
		*/
		bool MiddleMouseUp(float fMouseDownX, float fMouseDownY);

		/**
		*@note: ����м�̧��
		*/
		bool MouseMove(float fMouseDownX, float fMouseDownY,osgViewer::View *pViewer);

		/**
		*@note: �����ק
		*/
		bool DragEvent(float fMouseDownX, float fMouseDownY,osgViewer::View *pViewer);

	protected:
		osg::observer_ptr<FeExNode::CExternNode>    m_rpCurrentEventInform;

		float    m_fMouseDownX;  //��갴�µ�Xλ��
		float    m_fMouseDownY;  //��갴�µ�Yλ��

		bool    m_bActive;

		bool    m_bPick;
	};
}

#endif//HG_ADD_ELEMENT_EVENT_HANDLER_H
