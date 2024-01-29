// https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.8

#include "Commands/Kick_Command.hpp"

Kick_Command::Kick_Command(string msg, Server &server, User * sender) : ACommand(server, sender, msg)
{
}

Kick_Command::~Kick_Command()
{
}

bool Kick_Command::has_operator_rights()
{
	string msg;

	vector<Channel *>::iterator it_channel = _channels.begin();

	for (; it_channel != _channels.end(); it_channel++)
	{
		if (!(*it_channel)->isOperator(_sender))
		{
			//user is not operator message !!!
			msg = errorMessage(482, (*it_channel)->getName(), "0", "0");
	 		send(_sender->getFd(), msg.c_str(), msg.length(), 0); 	
			return ERROR;
		}
	}
	return SUCCESS;
}

void Kick_Command::parse_message(stringstream &separator_stream)
{
	string msg;

	separator_stream >> _message;
	while (separator_stream >> msg)
	{
		_message += " " + msg;
	}
}

bool Kick_Command::parse_channels(stringstream &separator_stream)
{
	string 		rawChannels;
	string 		channel_token;
	Channel 	*channel;
	string 		msg;

	separator_stream >> rawChannels;
	stringstream channel_stream(rawChannels);

	while (std::getline(channel_stream, channel_token, ','))
	{
		channel = _server.getChannel(channel_token);
		if (channel == NULL)
		{
			// channel not found message !!!
			msg = errorMessage(403, rawChannels, "0", "0"); // AJOUT ALEX
	 		send(_sender->getFd(), msg.c_str(), msg.length(), 0); // AJOUT ALEX
			return ERROR;
		}
		if (channel->isInChannel(_sender) == false)
		{
			msg = errorMessage(442, channel->getName(), "0", "0"); // AJOUT ALEX
	 		send(_sender->getFd(), msg.c_str(), msg.length(), 0); // AJOUT ALEX
	 		return ERROR; // ERR NOT ON CHANNEL
		}
		_channels.push_back(channel);
	}
	return SUCCESS;
}

bool Kick_Command::parse_users(stringstream &separator_stream)
{
	User 		*user;
	string rawUsers;
	string user_token;
	string msg;

	separator_stream >> rawUsers;
	stringstream user_stream(rawUsers);
	while (std::getline(user_stream, user_token, ','))
	{
		user = _server.getUser(user_token);
		if (user == NULL)
		{
			// user does not exist message !!!
			msg = errorMessage(403, rawUsers, "0", "0"); // AJOUT ALEX
	 		send(_sender->getFd(), msg.c_str(), msg.length(), 0); // AJOUT ALEX
			return ERROR;
		}
		// if ()//is not part of channel
		// {
		// 	//error message? !!!
		// }
		_users.push_back(user);
	}
	return SUCCESS;
}

bool Kick_Command::parse()
{
	stringstream 	separator_stream(_msg);
	stringstream 	ss(_msg);
	string 			arg;
	string 			msg;

	if (_msg.empty() || !(ss >> arg) || arg == ":" || !(ss >> arg) || arg == ":")
	{
		msg = errorMessage(461, "KICK", "0", "0"); // AJOUT ALEX
		send(_sender->getFd(), msg.c_str(), msg.length(), 0);  //AJOUT ALEX
		return ERROR; // ERR need more args
	}

	if (!parse_channels(separator_stream))
		return ERROR;

	if (!parse_users(separator_stream))
		return ERROR;

	parse_message(separator_stream);

	if (_channels.size() > 1 && _channels.size() != _users.size())
	{
		// bad kick syntax message !!! (see standard https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.8)
		return ERROR; // est-ce que c'est le test needmoreparam ?
	}

	if (has_operator_rights() == false)
		return ERROR;

	return SUCCESS;
}

string Kick_Command::formatMessage(Channel * channel, User * user)
{
	return (_sender->getID() + " KICK " + channel->getName() + " " + user->getNick() + " " + _message + "\r\n");
}

void Kick_Command::execute()
{
	if (parse() == ERROR)
		return ;

	vector<Channel *>::iterator it_channel = _channels.begin();
	vector<User *>::iterator it_user = _users.begin();
	Channel * channel;
	User * user;
	string msg;
	
	for (; it_channel != _channels.end(); it_channel++)
	{
		channel = (*it_channel);

		for (; it_user != _users.end(); it_user++)
		{
			user = *it_user;

			if(channel->isInChannel(*it_user) == false)
			{
				msg = errorMessage(441, (*it_user)->getNick(), channel->getName(), "0"); // AJOUT ALEX
	 			send(_sender->getFd(), msg.c_str(), msg.length(), 0); // AJOUT ALEX
	 			// ERR USER NOT ON CHANNEL
			}

			else if (channel->isOperator(user) && !channel->isOperator(_sender))
			{
				//cannot kick operator message !!!
				msg = errorMessage(482,  channel->getName(), "0", "0");
	 			send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
			}
			else if (channel->isInChannel(user))
			{
				channel->sendToChannel(formatMessage(channel, user));
				channel->removeUser(user);
			}
		}
	}
}