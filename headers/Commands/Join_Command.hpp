#ifndef __JOIN_COMMAND_H__
#define __JOIN_COMMAND_H__

#include "Libs.hpp"


class Server;
class User;
class Join_Command : public ACommand
{
private:
	std::vector< std::pair<std::string, std::string> > _channelNamePass;

public:
	Join_Command(std::string msg, Server &server, User &sender);
	~Join_Command();
	void joinChannel(std::pair<std::string, std::string> *channel_name_pass);
	bool passIsOk(Channel *channel, std::string password);

	bool parse();
	void execute();
};

#endif // __JOIN_COMMAND_H__
