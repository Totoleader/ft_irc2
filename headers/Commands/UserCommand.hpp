#ifndef __USERCOMMAND_H__
#define __USERCOMMAND_H__


#include "Libs.hpp"
# include "Server.hpp"
# include "ACommand.hpp"
# include "User.hpp"

class UserCommand : public ACommand
{
	private:
		std::string new_User;

	public:
		UserCommand(std::string msg, Server &server, User &sender);
		~UserCommand();

		void	exec();
};


#endif // __USERCOMMAND_H__