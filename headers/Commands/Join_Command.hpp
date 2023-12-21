#ifndef __JOIN_COMMAND_H__
#define __JOIN_COMMAND_H__

#include "Libs.hpp"
using std::string;
using std::pair;
using std::vector;

class Server;
class User;
class Join_Command : public ACommand
{
private:
	vector<pair<string, string> > _channelNamePass;
public:
	Join_Command(std::string msg, Server &server, User &sender);
	~Join_Command();
	void joinChannel(string channel);


	bool parse();
	void execute();
};






#endif // __JOIN_COMMAND_H__