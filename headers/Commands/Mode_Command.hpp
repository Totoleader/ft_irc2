#ifndef __Mode_Command_H__
#define __Mode_Command_H__

#include "Libs.hpp"

class Mode_Command : public ACommand
{
private:
	std::string	_availableModes;
	Channel *	_channel;
public:
	Mode_Command(std::string msg, Server &server, User &sender);
	~Mode_Command();

	bool parse();
	void execute();
};


#endif