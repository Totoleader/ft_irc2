#include "Libs.hpp"
#include "User.hpp"

User::User()
{
}

User::User(int fd, struct sockaddr *cl):_fd(fd), _sock(cl) 
{
	setIp();
}

User::~User()
{
}

void User::setIp()
{
	struct sockaddr_in *addrin = (struct sockaddr_in*)(_sock);
	struct in_addr addr = addrin->sin_addr;

	_ip = inet_ntoa(addr);
	_port = std::to_string(addrin->sin_port);
}








//getset crap->>

std::string User::getIp()
{
	return _ip;
}

std::string User::getPort()
{
	return _port;
}

std::string User::getNick()
{
	return _nick;
}

std::string User::getUser()
{
	return _login_name;
}

std::string User::getName()
{
	return _real_name;
}

std::string User::getID()
{
	return ":" + getNick() + "!" + getUser() + "@127.0.0.1:" + getPort();
}

struct sockaddr_storage	*User::getSock() const
{
	return (_sock);
}

void User::setSock(struct sockaddr_storage *s)
{
	_sock = s;
}

int User::getFd() const
{
	return (_fd);
}

void User::setFd(int fd)
{
	_fd = fd;
}

bool User::isConnected()
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
