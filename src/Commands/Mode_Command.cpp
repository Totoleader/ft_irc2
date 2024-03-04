#include "Commands/Mode_Command.hpp"
// https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.3

Mode_Command::Mode_Command(string msg, Server &server, User * sender) : ACommand(server, sender, msg)
{
	_action = NONE;
	_availableModes = "itkol";
	_channel = NULL;
}

Mode_Command::~Mode_Command()
{
}

void Mode_Command::_addMode(char mode, t_operation op)
{
	std::vector<t_mode>::iterator	it;

	for (it = _modes.begin(); it != _modes.end(); it++)
	{
		if (it->mode == mode)
		{
			it->operation = op;
			return ;
		}
	}
	t_mode m;

	m.mode = mode;
	m.operation = op;
	_modes.push_back(m);
}


void Mode_Command::changeMode_i(t_operation op)
{
	(op == OP_ADD) ? _channel->setInviteOnlyOn() : _channel->setInviteOnlyOff();
	string sign = (_channel->isInviteOnly()) ? "+" : "-";
	_channel->sendToChannel(_sender->getID() + " MODE " + _channel->getName() + " " + sign + "i\r\n");
}

void Mode_Command::changeMode_t(t_operation op)
{
	(op == OP_ADD) ? _channel->setTopicRestriction(true) : _channel->setTopicRestriction(false);
	string sign = (_channel->isTopicRestricted()) ? "+" : "-";
	_channel->sendToChannel(_sender->getID() + " MODE " + _channel->getName() + " " + sign + "t\r\n");
}

void Mode_Command::changeMode_k(t_operation op, string arg)
{
	(op == OP_ADD) ? _channel->setPassword(arg) : _channel->setPassword("");
	string sign = (_channel->getPassword().empty()) ? "-" : "+";
	_channel->sendToChannel(_sender->getID() + " MODE " + _channel->getName() + " " + sign + "k " + arg + "\r\n");
}

void Mode_Command::changeMode_o(t_operation op, string arg)
{
	string msg;
	User * target = _server.getUser(arg);

	if (!_channel->isInChannel(target))
	{
		msg = errorMessage(441, arg, _channel->getName(), "0"); 
		send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
		return ;
	}

	if (op == OP_ADD && _channel->isOperator(target))
		return ;

	(op == OP_ADD) ? _channel->addOperator(target) : _channel->removeOperator(target);
	string sign = (_channel->isOperator(target)) ? "+" : "-";
	_channel->sendToChannel(_sender->getID() + " MODE " + _channel->getName() + " " + sign + "o " + target->getNick() + "\r\n");
}

void Mode_Command::changeMode_l(t_operation op, string arg)
{
	std::istringstream 	iss(arg);
	string 				msg;
	int newLimit = -1;

	iss >> newLimit;
	if (op == OP_ADD)
	{
		if (newLimit >= 1 && newLimit <= 100)
		{
			_channel->setUserLimit(newLimit);
			stringstream ss;
			ss << newLimit;
			string limitStr = ss.str();
			_channel->sendToChannel(_sender->getID() + " MODE " + _channel->getName() + " +l " + limitStr + "\r\n");
		}
	}
	else
	{
		_channel->setUserLimit(NO_LIMIT);
		_channel->sendToChannel(_sender->getID() + " MODE " + _channel->getName() + " -l\r\n");
	}
}

bool Mode_Command::_fillModeVector(string modes)
{
	string msg;
	t_operation op = OP_ADD;

	for (size_t i = 0; i < modes.length(); i++)
	{
		if (modes[i] == '+')
			op = OP_ADD;
		else if (modes[i] == '-')
			op = OP_REMOVE;
		else if (std::find(_availableModes.begin(), _availableModes.end(), modes[i]) != _availableModes.end()) // cherche le mode dans la list de modes permis
			_addMode(modes[i], op);
		else
		{
			std::cout << "ERROR '" << modes[i] << "' not available!!" << std::endl;
			msg = errorMessage(472, modes, _channel->getName(), "0"); 
			send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
			return ERROR;
		}
	}
	return SUCCESS;
}

void Mode_Command::_showModes()
{
	string modes = "+";

	if (_channel->isInviteOnly())
		modes += "i";
	if (_channel->isTopicRestricted())
		modes += "t";
	if (_channel->getPassword() != "")
		modes += "k";
	if (_channel->getUserLimit() > NO_LIMIT)
		modes += "l";

	if (modes != "+")
	{
		std::cout << modes << std::endl;
		string msg = replyMessage(324, _channel->getName(), modes, "");
		send(_sender->getFd(), msg.c_str(), msg.length(), 0);
	}
}

bool Mode_Command::parse()
{
	std::istringstream	iss(_msg);
	string				channel;
	string				mode_str;
	string 				msg;

	if (!(iss >> channel) || channel == "MODE")
	{
		msg = errorMessage(461, "MODE", "0", "0"); 
		send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
		return ERROR;
	}

	_channel = _server.getChannel(channel);
	if (!_channel)
	{
		msg = errorMessage(403, channel, "0", "0"); 
		send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
		return ERROR;
	}
	else if (!_channel->isInChannel(_sender))
	{
		msg = errorMessage(442, channel, "0", "0"); 
	 	send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
		return ERROR;
	}

	if (!(iss >> mode_str) || mode_str == ":")
	{
		_action = SHOW;
		return SUCCESS;
	}
	else
		_action = CHANGE;

	if (_fillModeVector(mode_str) == ERROR)
		return ERROR;

	string temp;
	iss >> _args;
	while (iss >> temp)
		_args += " " + temp;

	return SUCCESS;
}

void Mode_Command::execute()
{
	string msg;

	if (parse() == ERROR)
		return ;
	
	if (_action == SHOW)
	{
		std::cout << "Action: SHOW | Channel: " << _channel->getName() << std::endl;
		_showModes();
	}
	else if (_action == CHANGE && _channel->isOperator(_sender))
	{
		std::istringstream iss(_args);
		for (vector<t_mode>::iterator it = _modes.begin(); it != _modes.end(); it++)
		{
			string arg;
			switch (it->mode)
			{
			case 'i':
				changeMode_i(it->operation);
				break;
			case 't':
				changeMode_t(it->operation);
				break;
			case 'k':
				iss >> arg;
				changeMode_k(it->operation, arg);
				break;
			case 'o':
				iss >> arg;
				changeMode_o(it->operation, arg);
				break;
			case 'l':
				iss >> arg;
				changeMode_l(it->operation, arg);
				break;
			default:
				break;
			}
		}
	}
	else
	{
		msg = errorMessage(482, _channel->getName(), "0", "0"); 
		send(_sender->getFd(), msg.c_str(), msg.length(), 0);  
	}
}