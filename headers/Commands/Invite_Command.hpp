#include "Libs.hpp"

class Server;
class User;
class Invite_Command : public ACommand
{
private:
	User	*_userToInvite;
	Channel	*_channel;

public:
	Invite_Command();
	~Invite_Command();

	bool parse();
	void execute();
};
