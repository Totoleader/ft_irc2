#ifndef __User_Command_H__
#define __User_Command_H__


#include "Libs.hpp"
# include "Commands/ACommand.hpp"

class Server;
class User;
class User_Command : public ACommand
{
	private:
		std::string new_User;

	public:
		User_Command( std::string msg, Server &server, User &sender);
		~User_Command();

		bool	parse();
		void	execute();
};

#endif // __User_Command_H__