// https://datatracker.ietf.org/doc/html/rfc2812#section-3.3.1

#include "Commands/Privmsg_Command.hpp"

Privmsg_Command::Privmsg_Command(string msg, Server &server, User * sender): ACommand(server, sender, msg)
, _channel(NULL)
, _user(NULL) 
{
}

Privmsg_Command::~Privmsg_Command()
{
}

bool Privmsg_Command::channel_is_ok(string name)
{
	string msg;
	_channel = _server.getChannel(name);

	if (_channel == NULL)
	{
		msg = errorMessage(403, name, "0", "0"); 
	 	send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
		return ERROR;
	}

	if (!_channel->isInChannel(_sender))
	{
		msg = errorMessage(404, _channel->getName(), "0", "0"); 
	 	send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
		return ERROR;
	}
	return SUCCESS;
}

bool Privmsg_Command::user_is_ok(string name)
{
	string msg;
	_user = _server.getUser(name);

	if (_user == NULL)
	{
		msg = errorMessage(401, name, "0", "0"); 
	 	send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
		return ERROR;
	}
	return SUCCESS;
}

bool Privmsg_Command::parse()
{
	string channelName;
	string msg;

	channelName = _msg.substr(0, _msg.find(" "));

	if (channelName.empty())
		return ERROR;

	if (channelName.at(0) == '#' && !channel_is_ok(channelName))
		return ERROR;
	else if (channelName.at(0) != '#' && !user_is_ok(channelName))
		return ERROR;
	
	_message = _msg.substr(_msg.find(' '));
	if (_message == "")
	{
		msg = errorMessage(401, "0", "0", "0"); 
	 	send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
		return ERROR;
	}
	_msg = _sender->getID() + " PRIVMSG " + _msg + "\r\n";
	return SUCCESS;
}

void Privmsg_Command::execute()
{
	if (parse() == ERROR)
		return ;

	if (_channel)
		_channel->sendToChannelExcept(_msg, _sender);
	else if (_user)
		send(_user->getFd(), _msg.c_str(), _msg.length(), 0);
}
