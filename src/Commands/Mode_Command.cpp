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

// Remplace ou ajoute un mode dans la liste
// Faire check de validite avant!
void Mode_Command::_addMode(char mode, t_operation op)
{
	std::vector<t_mode>::iterator	it;

	// Cherche si le mode est deja present et le met a jour
	for (it = _modes.begin(); it != _modes.end(); it++)
	{
		if (it->mode == mode)
		{
			it->operation = op;
			return ;
		}
	}
	// S'il le trouve pas, ajoute
	t_mode m;

	m.mode = mode;
	m.operation = op;
	_modes.push_back(m);
}

void Mode_Command::changeMode_i(t_operation op)
{
	if (op == OP_ADD)
		_channel->setInviteOnlyOn();
	else 
		_channel->setInviteOnlyOff();
}

void Mode_Command::changeMode_t(t_operation op)
{
	if (op == OP_ADD)
		_channel->_topicRestriction();
	else 
		_channel->_topicRestriction();
}

void Mode_Command::changeMode_k(t_operation op)
{
	if (op == OP_ADD)
		//get next arg
	else 
		_channel->setPassword("");
}

void Mode_Command::changeMode_o(t_operation op)
{
	if (op == OP_ADD && !_channel.isOperator(/*user to add*/))
		_channel->addOperator(/*user to add*/)
	else 
		_channel->removeOperator(_sender);
}

void Mode_Command::changeMode_l(t_operation op)
{
	if (op == OP_ADD)
	{
		int newLimit = std::stoi(/*arg (check if valid before)*/);
		_channel->setUserLimit(newLimit);
	}
	else 
		_channel->setUserLimit(NO_LIMIT);
}

bool Mode_Command::parse()
{
	std::istringstream	iss(_msg);
	string				channel;
	string				mode_str;
	string				args;

	if (!(iss >> channel))
	{
		// !!! ERR NO ENOUGH PARAMS
		return ERROR;
	}

	_channel = _server.getChannel(channel);
	if (!_channel)
	{
		// !!! NO SUCH CHANNER
		return ERROR;
	}
	else if (!_channel->isInChannel(_sender))
	{
		// !!! NOT IN CHANNEL
		return ERROR;
	}

	if (!(iss >> mode_str) || mode_str == ":")
	{
		_action = SHOW;
		return SUCCESS;
	}
	else
		_action = CHANGE;

	string temp;
	iss >> args;
	while (iss >> temp)
		args += " " + temp;

	return SUCCESS;
}

void Mode_Command::execute()
{
	if (parse() == ERROR)
		return ;
	
	if (_action == SHOW)
		std::cout << "Action: SHOW | Channel: " << _channel->getName() << std::endl;
	else if (_action == CHANGE)
		std::cout << "Action: CHANGE | Channel: " << _channel->getName() << std::endl;
}