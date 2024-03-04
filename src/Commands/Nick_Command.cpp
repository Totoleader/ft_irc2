// https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.2

#include "Commands/Nick_Command.hpp"

Nick_Command::Nick_Command(string msg, Server &server, User * sender): ACommand(server, sender, msg)
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
	std::string msg; 

	if (!_sender->isPassAccepted())
	{
		std::cout << "User has not entered password yet." << std::endl;
		return ;
	}
	if (parse() == ERROR)
	{
		msg = errorMessage(431, "0", "0", "0"); 
		send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
		return ;
	}
	if (_server.isNickTaken(_new_nick))
	{
		msg = errorMessage(433, _new_nick, "0", "0"); 
		send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
		return ;
	}

	vector<Channel *> channels = _server.getUserChannels(_sender);
	vector<Channel *>::iterator it;
	for (it = channels.begin(); it != channels.end(); it++)
	{
		string msg = _sender->getID() + " NICK " + _new_nick + "\r\n";
		(*it)->sendToChannel(msg);
	}
	_sender->setNick(_new_nick);

	if (!_sender->isConnected() && !_sender->getUsername().empty() && !_sender->getName().empty())
		_connectUser();
}