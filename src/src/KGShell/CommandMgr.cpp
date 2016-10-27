#include <KGShell/CommandMgr.h>

#include <cassert>

namespace KGShell
{
	static CKGCommandMgr* s_commandmgr_instance = NULL; 

	CKGCommandMgr::CKGCommandMgr ()
	{
		assert(s_commandmgr_instance == NULL);
		s_commandmgr_instance = this;
	}

	CKGCommandMgr::~CKGCommandMgr ()
	{
		assert(s_commandmgr_instance == this);
		s_commandmgr_instance = NULL;
	}

	CKGCommandMgr*
		CKGCommandMgr::instance()
	{
		return s_commandmgr_instance 
			? s_commandmgr_instance 
			: new CKGCommandMgr;
	}

	void CKGCommandMgr::addCommandObject (const std::string &name, Command* command)
	{
		if (_commands.find(name) != _commands.end())
			osg::notify(osg::WARN)<<"ÖØ¸´ÃüÁîÃû"<<std::endl;

		_commands[name] = command;
	}

	CKGCommandMgr::Command* CKGCommandMgr::getCommand( const std::string &name ) const
	{
		const command_map::const_iterator it = _commands.find(name);
		return (it != _commands.end() ? it->second : 0);
	}

	string_list CKGCommandMgr::getCommandNames() const
	{
		string_list names;
		command_map::const_iterator it = _commands.begin();
		command_map::const_iterator last = _commands.end();
		while (it != last) {
			names.push_back(it->first);
			++it;
		}
		return names;
	}

	bool CKGCommandMgr::removeCommand( const std::string& name )
	{
		command_map::iterator it = _commands.find(name);
		if (it == _commands.end())
			return false;

		delete it->second;
		_commands.erase(it);
		return true;
	}

}