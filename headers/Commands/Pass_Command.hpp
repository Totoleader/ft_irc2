#ifndef __Pass_Command_H__
#define __Pass_Command_H__


#include "Libs.hpp"
# include "Commands/ACommand.hpp"

class Server;
class User;
class Pass_Command : public ACommand
{
	private:
		std::string _password;

	public:
		Pass_Command( std::string msg, Server &server, User &sender);
		~Pass_Command();

		bool	parse();
		void	execute();
};

#endif // __Pass_Command_H__