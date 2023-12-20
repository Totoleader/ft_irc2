
#include "Libs.hpp"
#include "Commands/Pass.hpp"

Pass::Pass(std::string msg, Server &server, User &sender): ACommand(server, sender)
{
	this->_msg = msg;

	parse();
}

Pass::~Pass()
{
	
}

void Pass::parse()
{
	_pass = _msg;
}

void Pass::exec()
{
	
}

