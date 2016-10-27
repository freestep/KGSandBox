//////////////////////////////////////////////////////////////////////////
// ��������Ƶ��������
//////////////////////////////////////////////////////////////////////////
#ifndef _COMMANDMGR_H_
#define _COMMANDMGR_H_

#include <KGShell/Export.h>
#include <KGShell/Props.h>

#include <KGUtils/Common.h>

#include <KGShell/Exception.h>

#include <map>

using namespace KGUtil;

namespace KGShell
{
	//////////////////////////////////////////////////////////////////////////
	//����������Դ��Ϊ�Ĺ�����
	//////////////////////////////////////////////////////////////////////////
	class KGSHELL_EXPORT CKGCommandMgr
	{
	public:
		//////////////////////////////////////////////////////////////////////////
		//����Դʵ��
		//////////////////////////////////////////////////////////////////////////
		class Command
		{
		public:
			virtual ~Command() { }
			
			virtual bool operator()(const CKGPropertyCell& )=0;
		};

		typedef bool (*command_t) (const CKGPropertyCell&);

	protected:
		//////////////////////////////////////////////////////////////////////////
		//��������, ����ķ��������Ӧ��������ӳ��
		//////////////////////////////////////////////////////////////////////////
		template< class ObjPtr, typename MemFn>
		class MethodCommand : public Command
		{
		public:
			MethodCommand(const ObjPtr& pObj, MemFn pMemFn) :
			  _pObj(pObj), _pMemFn(pMemFn) {}
			//�º���ִ��ӳ�䷽��
			virtual bool operator()(const CKGPropertyCell& arg)
			{
				return ((*_pObj).*_pMemFn)(arg);
			}
		protected:
			//����Դ������
			ObjPtr _pObj;
			//����Դ����
			MemFn _pMemFn;
		};

		//������������Դ
		template< class ObjPtr, typename MemFn >
		Command* make_functor( const ObjPtr& pObj, MemFn pMemFn )
		{
			return new MethodCommand<ObjPtr, MemFn>(pObj, pMemFn);
		}
	private:
		CKGCommandMgr();
		virtual ~CKGCommandMgr();
	public:
		static CKGCommandMgr* instance();

		//�������ָ��������Դ��ÿ��ӳ��
		template<class OBJ, typename METHOD>
		void addCommand(const std::string& name, const OBJ& o, METHOD m)
		{ 
			addCommandObject(name, make_functor(o,m));
		}
		//����ָ��ؼ��ֲ��Ҳ���������Դ
		virtual Command* getCommand (const std::string &name) const;
		//�������е�ָ��ؼ���
		virtual string_list getCommandNames () const;
		//����ָ��ؼ��ֲ��ҵ�����Դ��ɾ��
		bool removeCommand(const std::string& name);

		//ִ������
		bool execute (const std::string &name, const CKGPropertyCell& arg) const
		{
			Command* command = getCommand(name);
			if (NULL == command)
			{
				osg::notify(osg::WARN)<<"δ�ҵ�����:# "<< name << " #"<<std::endl;
				return false;
			}
			try
			{
				const std::type_info& t = typeid(command);
				return (*command)(arg);
			}
			catch (KGException& e)
			{
				osg::notify(osg::WARN)<<"���� '" << name << "' ����ִ��ʧ��\n"
					"\t��ʾ:" << e.getMessage()<<" �� "<<e.getOrigin()<<std::endl ;
			}
			return false;
		}

	protected:
		void addCommandObject (const std::string &name, Command* command);

	private:
		typedef std::map<std::string, Command*> command_map;
		command_map _commands;

	};

#define CMD KGShell::CKGCommandMgr::instance

}

#endif 
