#ifndef __NICK_H__
#define __NICK_H__


#include "Libs.hpp"
# include "Server.hpp"
# include "ACommand.hpp"
# include "User.hpp"


class Server;
class Nick : public ACommand
{
	private:
		std::string new_nick;
	public:
		Nick( std::string msg, Server &server, User &sender);// : ACommand(Sever &serv, User &sender); // sam
		~Nick();

		void	exec();
};


#endif // __NICK_H__