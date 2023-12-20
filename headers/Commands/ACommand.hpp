#ifndef __ACOMMAND_H__
#define __ACOMMAND_H__


# include "Libs.hpp"
# include "Server.hpp"
# include "User.hpp"

class Server;
class User;
class ACommand
{
	private:
		Server	& _server;
		User	& _sender;
		std::string	_msg;
	public:
		ACommand();
		ACommand(Server & server, User & sender, std::string msg);
		virtual ~ACommand();
	
		
		
		virtual void	execute() = 0;
};


#endif // __ACOMMAND_H__