#include "Libs.hpp"
#include "Commands/Invite_Command.hpp"

Invite_Command::Invite_Command()
{
}

Invite_Command::~Invite_Command()
{
}


bool Invite_Command::parse()
{
	std::string userName;
	std::string channelName;

	userName = _msg.substr(0, ' ');
	_userToInvite = _server.getUser(userName);
	if (_userToInvite == NULL)
	{
		// ** User not found **
		return ERROR;
	}

	channelName = _msg.substr(' ');
	_channel = _server.getChannel(channelName);
	if (_channel == NULL)
	{
		// **  Channel not found **
		return ERROR;
	}

	if (!_channel->isInviteOnly())
	{
		// ** no need to invite **
		return ERROR;
	}

	if (_channel->isInChannel(*_userToInvite))
	{
		// ** User already in the channel **
		return ERROR;
	}

	return SUCCESS;
}

void Invite_Command::execute()
{
	if (parse() == ERROR)
		return ;
	_channel->addToWhiteList(*_userToInvite);
}