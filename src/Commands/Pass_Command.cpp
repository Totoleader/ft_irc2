// https://datatracker.ietf.org/doc/html/rfc2812#section-3.1.1

#include "Commands/Pass_Command.hpp"

Pass_Command::Pass_Command(string msg, Server &server, User * sender): ACommand(server, sender, msg)
{
	
}

Pass_Command::~Pass_Command()
{
	
}

bool Pass_Command::parse()
{
	string msg;

	if (_sender->isConnected())
	{
		// ### send client is already connected msg (462) ###
		msg = errorMessage(462, "0", "0", "0"); // AJOUT ALEX
	 	send(_sender->getFd(), msg.c_str(), msg.length(), 0); // AJOUT ALEX
		return (ERROR);
	}

	if (_msg.at(0) == ':')
		_password = _msg.substr(1);
	else
		_password = _msg;

	return (SUCCESS);
}

void Pass_Command::execute()
{
	string msg;
	const string server_pass = _server.getPassword();
	
	if (parse() == ERROR || server_pass == "")
		return ;
	
	if (_password == "")
	{
		// ### send client no password enter msg ###
		msg = errorMessage(461, "PASS", "0", "0"); // AJOUT ALEX
		send(_sender->getFd(), msg.c_str(), msg.length(), 0);  //AJOUT ALEX
	}
	if (_password != server_pass)
	{
		std::cout << "Password refused." << std::endl;
		_server.disconnect_user(_sender);
	}
	else
	{
		std::cout << "Password accepted." << std::endl;
		_sender->passwordAccepted();
	}
}
