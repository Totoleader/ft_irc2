// https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.4

#include "Commands/Topic_Command.hpp"

Topic_Command::Topic_Command(string msg, Server &server, User &sender) : ACommand(server, sender, msg), _new_topic("")
{
}

Topic_Command::~Topic_Command()
{
}

bool Topic_Command::parse()
{
	std::stringstream	ss(_msg);
	string			arg;
	
	ss >> arg;
	if (arg.empty())
	{
		return ERROR; // ERR need more args
	}
	_channel = _server.getChannel(arg);
	if (!_channel)
	{
		return ERROR; // ERR CHANNEL NOT FOUND
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
	if (parse() == ERROR)
		return ;
	switch (_action)
	{
	case SHOW:
		std::cout << "TOPIC :" << _channel->getTopic() << std::endl; // !!! RPL_TOPIC au user
		break;
	case CLEAR:
		// Check mode +t
		// Check isOperator si restriction
		_new_topic = "";
	case CHANGE:
		
		std::cout << "TOPIC set to :" << _new_topic << std::endl;
		_channel->setTopic(_new_topic);
		break;
	
	default:
		break;
	}
}
