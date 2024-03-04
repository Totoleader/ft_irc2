// https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.4

#include "Commands/Topic_Command.hpp"

Topic_Command::Topic_Command(string msg, Server &server, User * sender) : ACommand(server, sender, msg), _new_topic("")
{
}

Topic_Command::~Topic_Command()
{
}

bool Topic_Command::parse()
{
	stringstream	ss(_msg);
	string			arg;
	string 			msg; 

	if (_msg.empty() || !(ss >> arg) || arg == ":")
	{
		msg = errorMessage(461, "TOPIC", "0", "0"); 
		send(_sender->getFd(), msg.c_str(), msg.length(), 0);  
		return ERROR;
	}
	_channel = _server.getChannel(arg);
	if (!_channel)
	{
		msg = errorMessage(403, arg, "0", "0"); 
		send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
		return ERROR;
	}
	if (_channel->isInChannel(_sender) == false)
	{
		msg = errorMessage(442, arg, "0", "0"); 
		send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
		return ERROR;
	}

	ss >> _new_topic;
	if (_new_topic.empty())
		_action = SHOW;
	else if (_new_topic == ":")
		_action = CLEAR;
	else
	{
		_action = CHANGE;
		if (_new_topic.at(0) == ':')
		{
			string temp;
			while (ss >> temp)
				_new_topic += " " + temp;
			_new_topic = _new_topic.substr(1);
		}
	}
	return SUCCESS;
}

void Topic_Command::execute()
{
	string msg;

	if (parse() == ERROR)
		return ;
	switch (_action)
	{
	case SHOW:
		if (!_channel->getTopic().empty())
			msg = replyMessage(332, _channel->getName(), _channel->getTopic(), "0");
		else
			msg = replyMessage(331, _channel->getName(), "0", "0");
		send(_sender->getFd(), msg.c_str(), msg.length(), 0);
		break;
	case CLEAR:
		if (_channel->isTopicRestricted() && _channel->isOperator(_sender) == false)
		{
			msg = errorMessage(482, _channel->getName(), "0", "0");
			send(_sender->getFd(), msg.c_str(), msg.length(), 0);
			break;
		}
		_new_topic = "";
	case CHANGE:
		if (_channel->isTopicRestricted() && _channel->isOperator(_sender) == false)
		{
			msg = errorMessage(482, _channel->getName(), "0", "0");
			send(_sender->getFd(), msg.c_str(), msg.length(), 0);
			break;
		}
		_channel->setTopic(_new_topic);
		_channel->sendToChannel(_sender->getID() + " TOPIC " + _msg + "\r\n");
		break;
	
	default:
		break;
	}
}
