#include "Libs.hpp"
#include "Commands/User_Command.hpp"

User_Command::User_Command(std::string msg, Server &server, User &sender): ACommand(server, sender, msg)
{
	
}

User_Command::~User_Command()
{
	
}

bool User_Command::parse()
{
	return 0;
}

void User_Command::execute()
{
	
}