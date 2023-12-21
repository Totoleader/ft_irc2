#include "Libs.hpp"
#include "Commands/User_Command.hpp"

User_Command::User_Command(std::string msg, Server &server, User &sender): ACommand(server, sender, msg), _username(""), _realname("")
{
	std::cout << "User command created" << std::endl;
}

User_Command::~User_Command()
{
	
}

bool User_Command::parse()
{
	std::stringstream ss(_msg);
	std::string username;

	ss >> _username;
	if (!_username.empty() && _username.at(0) == ':')
		return ERROR;
	ss >> _realname >> _realname >> _realname;
	if (_realname.at(0) == ':')
	{
		std::string temp;
		while (ss >> temp)	
			_realname += " " + temp;
	}
	return SUCCESS;
}

void User_Command::execute()
{
	// if (!_sender.) check pass
	// 	return ; // ERR OR DISCONNECT
	if (parse() == ERROR)
		return ; // ERR 
	_sender.setUsername(_username);
	_sender.setName(_realname);
	if (!_sender.isConnected() && !_sender.getUsername().empty() && !_sender.getName().empty())
		_connectUser();
}