#ifndef __PASS_H__
#define __PASS_H__


#include "Libs.hpp"
# include "Server.hpp"
# include "ACommand.hpp"
# include "User.hpp"

class Server;
class Pass : public ACommand
{
	private:
		std::string new_User;

	public:
		Pass( std::string msg, Server &server, User &sender);// : ACommand(Sever &serv, User &sender); // sam
		~Pass();

		void	exec();
};

#endif // __PASS_H__