#ifndef __Nick_Command_H__
#define __Nick_Command_H__


#include "Libs.hpp"

class Server;
class User;
class Nick_Command : public ACommand
{
	private:
		std::string new_Nick_Command;

	public:
		Nick_Command(std::string msg, Server &server, User &sender);
		~Nick_Command();

		bool	parse();
		void	execute();
};

#endif // __Nick_Command_H__