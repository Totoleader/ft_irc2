#include "Libs.hpp"
#include "Commands/Pass_Command.hpp"

Pass_Command::Pass_Command(std::string msg, Server &server, User &sender): ACommand(server, sender, msg)
{
	
}

Pass_Command::~Pass_Command()
{
	
}

bool Pass_Command::parse()
{
	if (_sender.isConnected())
	{
		//error 462
		return (ERROR);
	}

	if (_msg.at(0) == ':')
		_password = _msg.substr(1);
	else
		_password = _msg;

	return (SUCCESS);
}

void Pass_Command::execute()
{
	const std::string server_pass = _server.getPassword();
	
	if (parse() == ERROR || server_pass == "")
		return ;
	
	if (_password != server_pass)
	{
		// _server.disconnect_user(_sender);
	}
}
