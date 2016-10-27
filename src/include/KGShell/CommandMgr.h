//////////////////////////////////////////////////////////////////////////
// 带反射机制的命令管理
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
	//负责处理命令源行为的管理者
	//////////////////////////////////////////////////////////////////////////
	class KGSHELL_EXPORT CKGCommandMgr
	{
	public:
		//////////////////////////////////////////////////////////////////////////
		//命令源实体
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
		//方法命令, 命令的发出方与对应方法建立映射
		//////////////////////////////////////////////////////////////////////////
		template< class ObjPtr, typename MemFn>
		class MethodCommand : public Command
		{
		public:
			MethodCommand(const ObjPtr& pObj, MemFn pMemFn) :
			  _pObj(pObj), _pMemFn(pMemFn) {}
			//仿函数执行映射方法
			virtual bool operator()(const CKGPropertyCell& arg)
			{
				return ((*_pObj).*_pMemFn)(arg);
			}
		protected:
			//命令源发出方
			ObjPtr _pObj;
			//命令源方法
			MemFn _pMemFn;
		};

		//创建方法命令源
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

		//添加命令指令与命令源的每个映射
		template<class OBJ, typename METHOD>
		void addCommand(const std::string& name, const OBJ& o, METHOD m)
		{ 
			addCommandObject(name, make_functor(o,m));
		}
		//根据指令关键字查找并返回命令源
		virtual Command* getCommand (const std::string &name) const;
		//返回所有的指令关键字
		virtual string_list getCommandNames () const;
		//根据指令关键字查找到命令源并删除
		bool removeCommand(const std::string& name);

		//执行命令
		bool execute (const std::string &name, const CKGPropertyCell& arg) const
		{
			Command* command = getCommand(name);
			if (NULL == command)
			{
				osg::notify(osg::WARN)<<"未找到命令:# "<< name << " #"<<std::endl;
				return false;
			}
			try
			{
				const std::type_info& t = typeid(command);
				return (*command)(arg);
			}
			catch (KGException& e)
			{
				osg::notify(osg::WARN)<<"命令 '" << name << "' 意外执行失败\n"
					"\t提示:" << e.getMessage()<<" 从 "<<e.getOrigin()<<std::endl ;
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
