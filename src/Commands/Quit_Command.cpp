// https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.7

#include "Commands/Quit_Command.hpp"

Quit_Command::Quit_Command(string msg, Server &server, User *sender): ACommand(server, sender, msg)
{
	
}

Quit_Command::~Quit_Command()
{
	
}

void Quit_Command::execute()
{
	_channelsToPart =  _server.getUserChannels(_sender);

	//vector<Channel *>::iterator it;
	while (_channelsToPart.size() > 0)
	{
		Channel * channel = _channelsToPart[0];
		string msg = _sender->getID() + " QUIT " + _msg + "\r\n";
		channel->sendToChannelExcept(msg, _sender);
		_server.partUserFromChannel(_sender, channel);
		_channelsToPart = _server.getUserChannels(_sender);
	}
	// for (it = _channelsToPart.begin(); it != _channelsToPart.end(); it++)
	// {
	// 	Channel * channel = *it;
	// 	string msg = _sender->getID() + " QUIT " + _msg + "\r\n";
	// 	channel->sendToChannelExcept(msg, _sender);
	// 	_server.partUserFromChannel(_sender, channel);
		
	// }
	std::cout << std::endl << "User " << _sender->getNick() << " disconnected. (QUIT)" << std::endl;
	_server.disconnect_fdList(_sender);
	_server.disconnect_userList(_sender);
}