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
	const int N_CMDS = 4;
	const std::string cmds[N_CMDS] = { "NICK", "USER", "PASS", "TOPIC" };
	ACommand * (CommandFactory::*f[N_CMDS])(std::string, Server&, User&) = { &CommandFactory::NickFactory, &CommandFactory::UserFactory, &CommandFactory::PassFactory, &CommandFactory::TopicFactory};
	
	for (int i = 0; i < N_CMDS; i++)
	{
		size_t cmd_len = cmds[i].length();
		std::string cmd_check = msg.substr(0, cmd_len);
		if ( msg.length() >= cmd_len && !isspace( msg.at(cmd_len)))
			continue ;
		if (cmd_check == cmds[i])
			return (this->*(f[i]))(msg.substr(cmd_len + 1), serv, u);
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

ACommand *CommandFactory::TopicFactory(std::string msg, Server &server, User &sender)
{
	return (new Topic_Command(msg, server, sender));
}