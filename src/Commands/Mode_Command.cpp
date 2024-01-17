#include "Commands/Mode_Command.hpp"
// https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.3

Mode_Command::Mode_Command(std::string msg, Server &server, User &sender) : ACommand(server, sender, msg)
{
	_availableModes = "itkol";
	_channel = NULL;
}

Mode_Command::~Mode_Command()
{
}

bool Mode_Command::parse()
{

	return SUCCESS;
}

void Mode_Command::execute()
{

}