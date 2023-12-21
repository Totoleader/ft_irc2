#ifndef __PRIVMSG_COMMAND_H__
#define __PRIVMSG_COMMAND_H__

#include "Libs.hpp"


class Privmsg_Command : public ACommand
{
	private:
		std::string _channel;
		std::string _userName;
		
	public:
		Privmsg_Command( std::string msg, Server &server, User &sender );
		~Privmsg_Command();

		void execute();
};

#endif // __PRIVMSG_COMMAND_H__