#ifndef __COMMANDFACTORY_H__
#define __COMMANDFACTORY_H__


#include "Libs.hpp"
# include "Server.hpp"
# include "User.hpp"
# include "UserCommand.hpp"
# include "Commands/Nick.hpp"
# include "Commands/Pass.hpp"

// class UserCommand;
class CommandFactory
{
	private:
		static const std::string cmds[3];
		static ACommand * (CommandFactory::*f[3])(std::string, Server&, User&);

	
	public:
		ACommand *NickFactory(std::string, Server&, User&);
		ACommand *UserFactory(std::string, Server&, User&);
		ACommand *PassFactory(std::string, Server&, User&);
		
		CommandFactory(std::string msg);
		~CommandFactory();
};


#endif // __COMMANDFACTORY_H__