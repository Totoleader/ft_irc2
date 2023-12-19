#ifndef __USER_H__
#define __USER_H__


#include "Libs.hpp"
# include "Server.hpp"
# include "Commands/ACommand.hpp"

class User
{
	private:
		std::string				_nick; 
		std::string				_login_name;
		std::string				_real_name;
		std::string				_ip;
		std::string				_port;
		bool					_connected;
		int						_fd;
		bool					_first_msg;//?
		struct sockaddr_storage	*_sock;
	
		std::string					buffer;

	public:
		User();
		User(int fd, struct sockaddr *cl);
		~User();


		//get
		const std::string&	getNick() const;
		const std::string&	getUser() const;
		const std::string&	getName() const;
		const std::string&	getIp()	const;
		const std::string&	getPort() const;
		const std::string	getID() const;
		const int&			getFd() const;
		void				setSock(struct sockaddr_storage *s);
		const bool&			isFirstMsg() const;
		const bool&			isConnected() const;
		struct sockaddr_storage	*getSock();

		//set
		void	setIp();
		void	setFd(int fd);
		void	msgReceived();
		void	setConnected(bool is_connected);
		void	setBuffer(char *buf);
		std::string	getBuffer() const;
	};



#endif // __USER_H__