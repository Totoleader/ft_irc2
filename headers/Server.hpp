#ifndef __SERVER_H__
#define __SERVER_H__


#include "Libs.hpp"
# include "Commands/ACommand.hpp"
# include "User.hpp"
# include "Channel.hpp"

class Channel;

class Server
{
	private:
		std::vector<struct pollfd>		fds;
		std::vector<User>				_users;
		std::map<std::string, Channel>		_channels;
		std::string							_password;
		addrinfo						*_servinfo;

		bool check_password(char *buf);

	public:
		Server();
		Server(std::string password);
		~Server();

		// void init();
		// void listenForEvents();






		// void handle_client(int new_fd);

		// void leaveChannel(User &u, std::string msg);
		// void joinExistingChannel(User &u, Channel &chan);
		// void joinChannel(User &u, std::pair<std::string, std::string> chan);
		// void connectClient(User *u);
		// void sendMessage(User &u , std::string message);
		// void changeMode(User &u , std::string message);

		// void new_client();
		// void new_client(int fd);
		// void disconnect_user(int client_i);
		// void parse_UserCommandinfo(int client_i, std::string parseUserInfo);

		// //utils
		// void createChannelMsg(User &u, std::string chan) const;
		// void getAndJoinChannels(User &u, std::string channels);

		// User	*getUser(int fd);
		// User	*getUser(std::string nick);

		// void 		setPassword(std::string newPassword);
		// const char	*getPassword()	const;
		// int			getSocket()		const;

		// 	//AJOUT DE ALEX // 
		// void kickChannels(User &u, std::string str);
		// void skipWhitespace(std::string &str);
		// bool isUser(std::string UserCommandto_kick, std::string channel_name);
		// bool userExist(std::string UserCommandto_invite);
		// bool channelExist(std::string channel_name);
		// void inviteChannels(User &u, std::string str);
};


#endif // __SERVER_H__