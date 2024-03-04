// https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.7

#include "Commands/Invite_Command.hpp"

Invite_Command::Invite_Command(string msg, Server &server, User * sender) : ACommand(server, sender, msg)
{
}

Invite_Command::~Invite_Command()
{
}


bool Invite_Command::parse()
{
	string			userName;
	string			channelName;
	stringstream	ss(_msg);
	stringstream	bb(_msg);
	string			arg;
	string 			msg;

	if (_msg.empty() || !(ss >> arg) || arg == ":" || !(ss >> arg))
	{
		msg = errorMessage(461, "INVITE", "0", "0");
		send(_sender->getFd(), msg.c_str(), msg.length(), 0);
		return ERROR;
	}

	bb >> userName;
	_userToInvite = _server.getUser(userName);
	if (_userToInvite == NULL)
	{
		msg = errorMessage(401, userName, "0", "0");
		send(_sender->getFd(), msg.c_str(), msg.length(), 0);  
		return ERROR;
	}

	bb >> channelName;
	_channel = _server.getChannel(channelName);
	if (_channel == NULL)
	{
	 	msg = errorMessage(403, channelName, "0", "0"); 
	 	send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
	 	return ERROR;
	}

	if (_channel->isInChannel(_sender) == false)
	{
	 	msg = errorMessage(442, channelName, "0", "0"); 
	 	send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
	 	return ERROR;
	}
	
	if (_channel->isInviteOnly() && !_channel->isOperator(_sender))
	{
	 	msg = errorMessage(482, channelName, "0", "0");
	 	send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
	 	return ERROR;
	}

	if (_channel->isInChannel(_userToInvite))
	{
	 	msg = errorMessage(443, userName, channelName, "0");
	 	send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
	 	return ERROR;
	}

	return SUCCESS;
}

void Invite_Command::execute()
{
	string msg;

	if (parse() == ERROR)
		return ;
	_channel->addToWhiteList(_userToInvite);
	msg = replyMessage(341, _userToInvite->getNick(), _channel->getName(), "0");
	send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
	msg = ":"+ _sender->getNick() + "!" + _sender->getUsername() + "@127.0.0.1 INVITE " + _userToInvite->getNick() + " " + _channel->getName() + "\r\n";
	send(_userToInvite->getFd(), msg.c_str(), msg.length(), 0); 
}