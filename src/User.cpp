#include "Libs.hpp"
#include "User.hpp"

User::User()
{
}

User::User(int fd, struct sockaddr *cl): _fd(fd), _sock((struct sockaddr_storage*)cl) 
{
	setIp();
}

User::~User()
{
}

bool User::operator==(User const & rhs) const
{
	return this->_nick == rhs.getNick();
}

void User::setIp()
{
	struct sockaddr_in *addrin = (struct sockaddr_in*)(_sock);
	struct in_addr addr = addrin->sin_addr;

	_ip = inet_ntoa(addr);
	_port = std::to_string(addrin->sin_port);
}








//getset crap->>

const std::string & User::getIp() const
{
	return _ip;
}

const std::string & User::getPort() const
{
	return _port;
}

const std::string & User::getNick() const
{
	return _nick;
}

const std::string & User::getUser() const
{
	return _login_name;
}

const std::string & User::getName() const
{
	return _real_name;
}

const std::string User::getID() const
{
	return ":" + getNick() + "!" + getUser() + "@127.0.0.1:" + getPort();
}

struct sockaddr_storage	* User::getSock()
{
	return (_sock);
}

void User::setSock(struct sockaddr_storage *s)
{
	_sock = s;
}

const int & User::getFd() const
{
	return (_fd);
}

void User::setFd(int fd)
{
	_fd = fd;
}

const bool & User::isConnected() const
{
	return _connected;
}

void User::setConnected(bool is_connected)
{
	_connected = is_connected;
}

void User::setBuffer(char *buf)
{
	buffer += buf;
}

std::string User::getBuffer() const
{
	return (buffer);
}
