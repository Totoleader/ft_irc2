// https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.2

#include "Commands/Nick_Command.hpp"

Nick_Command::Nick_Command(string msg, Server &server, User &sender): ACommand(server, sender, msg)
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
	if (!_sender.isPassAccepted())
	{
		std::cout << "User has not entered password yet." << std::endl;
		return ; // ERR OR DISCONNECT
	}
	if (parse() == ERROR)
		return ; // ERR MSG
	if (_server.isNickTaken(_new_nick))
	{
		std::cout << "ERROR nick is taken" << std::endl;
		return ; // !!! ERR NICK TAKEN
	}

	// Broadcast aux channels du user: "old_nick is now known as new_nick" et resend la list des users
	std::vector<Channel *> channels = _server.getUserChannels(_sender);
	std::vector<Channel *>::iterator it;
	for (it = channels.begin(); it != channels.end(); it++)
	{
		string msg = _sender.getID() + " NICK " + _new_nick + "\r\n";
		(*it)->sendToChannel(msg);
	}
	_sender.setNick(_new_nick);

	// Connect user s'il n'est pas connecte
	if (!_sender.isConnected() && !_sender.getUsername().empty() && !_sender.getName().empty())
		_connectUser();
}