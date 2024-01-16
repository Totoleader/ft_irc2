#ifndef __KICK_COMMAND_H__
#define __KICK_COMMAND_H__

#include "Libs.hpp"

class Kick_Command : public ACommand
{
	private:
		std::vector<Channel>	_channels;
		std::vector<User>		_users;
		std::string				_message;

		bool has_operator_rights();
		void parse_message(std::stringstream &separator_stream);
		bool parse_channels(std::stringstream &separator_stream);
		bool parse_users(std::stringstream &separator_stream);
		std::string formatMessage(Channel &channel, User &user);

	public:
		Kick_Command(string msg, Server &server, User &sender);
		~Kick_Command();

		bool parse();
		void execute();
};

#endif // __KICK_COMMAND_H__