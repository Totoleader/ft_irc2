#ifndef __USERCOMMAND_H__
#define __USERCOMMAND_H__


#include "Libs.hpp"
# include "Server.hpp"
# include "ACommand.hpp"
# include "User.hpp"

class Server;
class UserCommand : public ACommand
{
	private:
		std::string new_User;

	public:
		UserCommand( std::string msg, Server &server, User &sender);// : ACommand(Sever &serv, User &sender); // sam
		~UserCommand();

		void	exec();
};


#endif // __USERCOMMAND_H__