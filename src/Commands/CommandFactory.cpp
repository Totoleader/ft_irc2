#include "Libs.hpp"
#include "Commands/CommandFactory.hpp"

CommandFactory::CommandFactory()
{
}

CommandFactory::~CommandFactory()
{
}

ACommand *CommandFactory::getCommand(std::string msg, Server &serv, User &u)
{
	const std::string cmds[3] = { "NICK ", "USER ", "PASS " }; // si /NICK sans espace???
	ACommand * (CommandFactory::*f[3])(std::string, Server&, User&) = { &CommandFactory::NickFactory, &CommandFactory::UserFactory, &CommandFactory::PassFactory};
	
	for (int i = 0; i < 3; i++)
	{
		std::string cmd_check = msg.substr(0, cmds[i].length());
		if (cmd_check == cmds[i])
			return (this->*(f[i]))(msg.substr(cmds[i].length()), serv, u);
	}
	return NULL;
}

ACommand *CommandFactory::NickFactory(std::string msg, Server &server, User &sender)
{
	return (new Nick_Command(msg, server, sender));
}

ACommand *CommandFactory::UserFactory(std::string msg, Server &server, User &sender)
{
	return (new User_Command(msg, server, sender));
}

ACommand *CommandFactory::PassFactory(std::string msg, Server &server, User &sender)
{
	return (new Pass_Command(msg, server, sender));
}