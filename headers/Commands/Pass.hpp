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
		std::string	_msg;
		std::string	_pass;

		void	parse();
	public:
		Pass(std::string msg, Server &server, User &sender);
		~Pass();
		
		void	exec();
};

#endif // __PASS_H__