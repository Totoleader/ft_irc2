#include "Libs.hpp"
#include "Commands/CommandFactory.hpp"


const std::string CommandFactory::cmds[3] = { "NICK", "USER", "PASS" };
ACommand * (CommandFactory::*f[3])(std::string, Server&, User&) = { &CommandFactory::NickFactory, &CommandFactory::UserFactory, &CommandFactory::PassFactory};

CommandFactory::CommandFactory(std::string msg)
{
	// std::vector<std::string> cmds = { "NICK", "USER", "PASS" };

	// ACommand * (CommandFactory::*f[])(std::string) = { &CommandFactory::NickFactory, &CommandFactory::UserFactory, &CommandFactory::PassFactory};

	// for (int i = 0; i < cmds.size(); i++)
	// {
	// }
}

CommandFactory::~CommandFactory()
{
}

ACommand *CommandFactory::NickFactory(std::string msg, Server &server, User &sender)
{
	return (new Nick(msg.substr(5), server, sender));
}

ACommand *CommandFactory::UserFactory(std::string msg, Server &server, User &sender)
{
	return (new UserCommand(msg.substr(5), server, sender));
}

ACommand *CommandFactory::PassFactory(std::string msg, Server &server, User &sender)
{
	return (new Pass(msg.substr(5), server, sender));
}