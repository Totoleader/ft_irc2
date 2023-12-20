#include "Libs.hpp"
#include "Commands/Nick_Command.hpp"

Nick_Command::Nick_Command(std::string msg, Server &server, User &sender): ACommand(server, sender, msg)
{
	
}

Nick_Command::~Nick_Command()
{
	
}

bool Nick_Command::parse()
{
	return 0;
}

void Nick_Command::execute()
{
	
}
