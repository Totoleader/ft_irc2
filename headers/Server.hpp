#ifndef __SERVER_H__
#define __SERVER_H__


#include "Libs.hpp"

class Channel;
class User;

class Server
{
	private:
		vector<struct pollfd>	_fds;
		list<User>				_users;
		vector<Channel>			_channels;
		string					_password;
		addrinfo				*_servinfo;
		static Server 			*stat_serv;

		bool check_password(char *buf);
		

	public:
		Server();
		Server(string password);
		~Server();

		void init(string port);
		void listenForEvents();

		void new_client();
		void new_channel(string channelName, User * sender, string password);
		void new_server(int fd);
		void handle_event(int fd);

		void disconnect_user(User * user);
		void removeChannel(Channel & c);
		void partUserFromChannel(User * u, Channel * c);

		bool isNickTaken(string const & nick);
		const string &getPassword() const;
		User *getUser(int fd);
		User *getUser(string nick);
		int	getChannelSize();
		Channel *getChannel(string channel_name);
		vector<Channel *> getUserChannels(User * user);
		void joinExistingChannel(User * u, Channel &chan);

		static void exit_cleanup(int signo);
		void disconnect_userList(User * user);
		void disconnect_fdList(User * user);
};


#endif // __SERVER_H__