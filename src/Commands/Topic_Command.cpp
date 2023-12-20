#include "Libs.hpp"
#include "Commands/Topic_Command.hpp"

Topic_Command::Topic_Command(std::string msg, Server &server, User &sender) : ACommand(server, sender, msg), _new_topic("")
{
}

Topic_Command::~Topic_Command()
{
}

bool Topic_Command::parse()
{
	if (_msg.empty())
		_action = SHOW;
}

void Topic_Command::execute()
{

}