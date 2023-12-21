#include "Libs.hpp"
#include "Commands/Topic_Command.hpp"

Topic_Command::Topic_Command(std::string msg, Server &server, User &sender) : ACommand(server, sender, msg), _new_topic("")
{
}

Topic_Command::~Topic_Command()
{
}

bool Topic_Command::parse()
{
	std::stringstream	ss(_msg);
	std::string			arg;
	
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
			std::string temp;
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
		/* send topic reply to user */
		break;
	case CHANGE:
	case CLEAR:
		// Check mode +t
		// Check isOperator si restriction
		_channel->setTopic(_new_topic);
		break;
	
	default:
		break;
	}
	
}
