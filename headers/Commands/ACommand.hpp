#ifndef __ACOMMAND_H__
#define __ACOMMAND_H__


# include "Libs.hpp"


class Server;
class User;
class ACommand
{
	protected:
		Server	& _server;
		User	& _sender;
		std::string	_msg;

		void	_connectUser();
	public:
		// ACommand();
		ACommand(Server & server, User & sender, std::string msg);
		virtual ~ACommand();
		string errorMessage(int key, string param1, string param2, string param3);

		
		
		virtual void	execute() = 0;
};


#endif // __ACOMMAND_H__