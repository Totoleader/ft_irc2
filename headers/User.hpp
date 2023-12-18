#ifndef __USER_H__
#define __USER_H__


#include "Libs.hpp"
# include "Server.hpp"
# include "Commands/ACommand.hpp"

class User
{
	private:
		std::string					_nick; 
		std::string					_login_name;
		std::string					_real_name;
		std::string					_ip;
		std::string					_port;
		bool					_connected;
		int						_fd;
		bool					_first_msg;
		struct sockaddr_storage	*_sock;
	
		std::string					buffer;
	public:
		User();
		~User();
	};



#endif // __USER_H__