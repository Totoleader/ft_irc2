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
	public:
		ACommand(Server & server, User & sender);
		~ACommand();
	
		
		
		// virtual void	exec() = 0;
};


#endif // __ACOMMAND_H__