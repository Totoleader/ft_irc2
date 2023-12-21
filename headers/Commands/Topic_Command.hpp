#ifndef __TOPIC_COMMAND_H_
#define __TOPIC_COMMAND_H_


#include "Libs.hpp"

class Server;
class User;
class Topic_Command : public ACommand
{
	private:
		typedef enum e_action
		{
			SHOW,
			CHANGE,
			CLEAR,
			ERR
		} t_action;

		std::string _new_topic;
		Channel *	_channel;
		t_action	_action;

		

	public:
		Topic_Command(std::string msg, Server &server, User &sender);
		~Topic_Command();

		bool	parse();
		void	execute();
};

#endif // __TOPIC_COMMAND_H_