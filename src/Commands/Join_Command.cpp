// https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.1

#include "Commands/Join_Command.hpp"

Join_Command::Join_Command(string msg, Server &server, User &sender) : ACommand(server, sender, msg)
{
	
}

Join_Command::~Join_Command()
{
	
}

bool Join_Command::parse()
{
	std::pair<string, string> pair;
	string channels;
	string passwords;
	string channel_token;
	string password_token;

	channels = _msg.substr(0, _msg.find(' '));
	if (_msg.find(' ') != string::npos)
		passwords = _msg.substr(_msg.find(' '));

	std::stringstream channel_stream(channels);
	std::stringstream password_stream(passwords);

	while (std::getline(channel_stream, channel_token, ','))
	{
		if (!std::getline(password_stream, password_token, ','))
			password_token = "";

		pair.first = channel_token;
		pair.second = password_token;
		_channelNamePass.push_back(pair);
	}
	return SUCCESS;//error case???
}

// void joinChannel()
// {

// }

bool Join_Command::passIsOk(Channel *channel, string password)
{
	if (password == channel->getPassword())
		return SUCCESS;
	return ERROR;
}

void Join_Command::joinChannel(std::pair<string, string> *channel_name_pass)
{
	Channel	*channel = _server.getChannel(channel_name_pass->first);
	string 	channelName = channel_name_pass->first;
	string 	password = channel_name_pass->second;

	if (channel == NULL)//si le channel n'existe pas
	{
		// createChannel()
		_server.new_channel(channelName, _sender, password);
		_server.joinExistingChannel(_sender, *_server.getChannel(channelName));
		//send client channel created message !!!
	}
	else if (channel->isInviteOnly() && !channel->isWhitelisted(_sender)) //bouncer
	{
		// is not whitelisted message !!!
	}
	else if (!passIsOk(channel, password))
	{
		// wrong channel password message !!!
	}
	else // join
	{
		channel->addUser(_sender);
		_server.joinExistingChannel(_sender, *channel);
	}
}

void Join_Command::execute()
{
	// vector< pair<string, string> >::iterator it  = _channelNamePass.begin();
	if (parse() == ERROR)
		return ;
	if (!_sender.isConnected())
	{
		std::cout << "Cannot join, user not connected" << std::endl;
		return ;
	}
	for (std::vector< std::pair<string, string> >::iterator it  = _channelNamePass.begin(); it != _channelNamePass.end(); it++)
	{
		joinChannel(&(*it));
	}
}