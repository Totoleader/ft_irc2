#include "Libs.hpp"
#include "Commands/Nick_Command.hpp"

Nick_Command::Nick_Command(std::string msg, Server &server, User &sender): ACommand(server, sender, msg)
{
	std::cout << "Nick command created" << std::endl;
}

Nick_Command::~Nick_Command()
{
	
}

bool Nick_Command::parse()
{
	if (_msg.empty())
		return ERROR;
	else if (_msg.at(0) == ':')
		return ERROR;
	_new_nick = _msg;
	return SUCCESS;
}

void Nick_Command::execute()
{
	// if (!_sender.) check pass
	// 	return ; // ERR OR DISCONNECT
	if (parse() == ERROR)
		return ; // ERR MSG
	_sender.setNick(_new_nick);
	if (!_sender.getUsername().empty() && !_sender.getName().empty())
		_connectUser();
}
