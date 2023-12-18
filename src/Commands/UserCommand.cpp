#include "Libs.hpp"
#include "Commands/UserCommand.hpp"

UserCommand::UserCommand(std::string msg, Server &server, User &sender): ACommand(server, sender)
{
	
}

UserCommand::~UserCommand()
{
	
}

void UserCommand::exec()
{
	
}