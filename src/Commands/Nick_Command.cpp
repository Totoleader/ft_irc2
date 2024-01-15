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
	if (_server.isNickTaken(_new_nick))
	{
		std::cout << "ERROR nick is taken" << std::endl;
		return ; // ERR NICK TAKEN
	}

	// Broadcast aux channels du user: "old_nick is now known as new_nick" et resend la list des users
	_sender.setNick(_new_nick);

	// Connect user s'il n'est pas connecte
	if (!_sender.isConnected() && !_sender.getUsername().empty() && !_sender.getName().empty())
		_connectUser();
}