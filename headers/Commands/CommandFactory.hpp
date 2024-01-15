#ifndef __COMMANDFACTORY_H__
#define __COMMANDFACTORY_H__


#include "Libs.hpp"


class ACommand;
class CommandFactory
{
	private:
		ACommand *NickFactory(std::string, Server&, User&);
		ACommand *UserFactory(std::string, Server&, User&);
		ACommand *JoinFactory(std::string, Server&, User&);
		ACommand *PassFactory(std::string, Server&, User&);
		ACommand *TopicFactory(std::string, Server&, User&);
		ACommand *PrivmsgFactory(std::string, Server&, User&);
	public:
		CommandFactory();
		~CommandFactory();

		ACommand *getCommand(std::string msg, Server &serv, User &u);

		
};


#endif // __COMMANDFACTORY_H__