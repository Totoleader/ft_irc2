#include "Libs.hpp"
#include "Commands/ACommand.hpp"

ACommand::ACommand(Server & server, User & sender): _server(server), _sender(sender)
{
	
}

ACommand::~ACommand()
{
	
}