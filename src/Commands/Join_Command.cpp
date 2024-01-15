#include "Libs.hpp"
#include "Commands/Join_Command.hpp"

Join_Command::Join_Command(std::string msg, Server &server, User &sender) : ACommand(server, sender, msg)
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
}

// void joinChannel()
// {

// }

void Server::joinExistingChannel(User &u, Channel &chan)
{
	string	join = u.getID() + " JOIN " + chan.getName() + "\r\n";
	string listBegin = ":127.0.0.1 353 " + u.getNick() + " = " + chan.getName() + " :";
	string listEnd = ":127.0.0.1 366 " + u.getNick() + " " + chan.getName() + " :End of /NAMES list.\r\n";
	send(u.getFd(), join.c_str(), join.length(), 0);
	chan.sendToChannelExcept(join, u);
	for (std::map<string, User>::iterator it = chan. getUsers().begin(); it != chan.getUsers().end(); it++)
	{
		if (chan.isOperator(it->second))
			listBegin += "@";
		listBegin += it->second.getNick() + " ";
	}
	listBegin += "\r\n";
	std::cout << listBegin << std::endl;
	send(u.getFd(), listBegin.c_str(), listBegin.length(), 0);
	send(u.getFd(), listEnd.c_str(), listEnd.length(), 0);
}

bool Join_Command::passIsOk(Channel *channel, string password)
{
	if (password == channel->getPassword())
		return true;
	return false;
}

void Join_Command::joinChannel(pair<string, string> *channel_name_pass)
{
	Channel	*channel = _server.getChannel(channel_name_pass->first);
	string 	channelName = channel_name_pass->first;
	string 	password = channel_name_pass->second;

	if (channel == NULL)//si le channel n'existe pas
	{
		// createChannel()
		_server.new_channel(channelName, _sender, password);
	}
	else if (!channel->isWhitelisted(_sender)) //bouncer
	{
		// is not whitelisted message
	}
	else if (!passIsOk(channel, password))
	{
		// wrong channel password message
	}
	else // join
	{
		channel->addUser(_sender);
		// joinExistingChannel(u, _channels[chan.first]);
	}
}

void Join_Command::execute()
{
	vector< pair<string, string> >::iterator it  = _channelNamePass.begin();
	for (it; it != _channelNamePass.end(); it++)
	{
		joinChannel(it);
	}
}