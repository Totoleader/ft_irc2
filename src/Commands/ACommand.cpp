#include "Libs.hpp"
#include "Commands/ACommand.hpp"


ACommand::ACommand(Server & server, User & sender, std::string msg): _server(server), _sender(sender), _msg(msg)
{
	
}

ACommand::~ACommand()
{
	
}