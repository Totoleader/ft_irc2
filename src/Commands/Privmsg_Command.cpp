#include "Libs.hpp"
#include "Commands/Privmsg_Command.hpp"

Privmsg_Command::Privmsg_Command(std::string msg, Server &server, User &sender): ACommand(server, sender, msg)
{
}

Privmsg_Command::~Privmsg_Command()
{
}

// void Privmsg_Command::execute()
// {
// 	size_t channelBegin;
// 	size_t messageBegin;
// 	string chan;
// 	string msg;

// 	channelBegin = message.find(' ', 0) + 1;
// 	messageBegin = message.find(' ', channelBegin + 1) + 1;

// 	chan = message.substr(channelBegin, messageBegin - channelBegin - 1);
// 	// message = message.substr(messageBegin);
// 	msg = u.getID() + " " + message + "\r\n";

// 	if (chan.at(0) == '#' && channelExist(chan) && isUser(u.getNick(), chan))
// 		_channels[chan].sendToChannelExcept(msg, u);
// 	else
// 	{
// 		for (size_t i = 0; i < _users.size(); i++)
// 		{
// 			if (_users[i].getNick() == chan)
// 				{send(_users[i].getFd(), msg.c_str(), msg.length(), 0); return;}
//     	}
// 			msg = ":127.0.0.1 401 " + chan + " :" + chan + " No such nick/channel\r\n";//to check <--
			
// 			send(u.getFd(), msg.c_str(), msg.length(), 0);/////////////////////////////////////////////
// 	}
// }

bool Privmsg_Command::parse()
{
	std::string channelName;

	channelName = _msg.substr(0, ' ');
	_channel = _server.getChannel(channelName);
	if (_channel == NULL)
	{
		// ** Channel not found **
		return ERROR;
	}

	if (!_channel->isInChannel(_sender))
	{
		// **  User not in the channel **
		return ERROR;
	}

	_message = _msg.substr(' ');
	if (_message == "")
	{
		return ERROR;
	}

}

void Privmsg_Command::execute()
{
	if (parse() == ERROR)
		return ;
	_channel->sendToChannelExcept(_message, _sender);
}
