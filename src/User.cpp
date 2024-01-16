#include "Libs.hpp"
#include "User.hpp"

User::User()
{
}

User::User(int fd, struct sockaddr *cl): _fd(fd), _sock((struct sockaddr_storage*)cl), _pass_ok(false), _connected(false)
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

void User::clean_buffer(size_t *trail)
{
	_buffer = _buffer.substr(*trail + 2);
	*trail = getBuffer().find("\r\n");
	// msgReceived();
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

const std::string & User::getUsername() const
{
	return _username;
}

const std::string & User::getName() const
{
	return _realname;
}

const std::string User::getID() const
{
	return ":" + _nick + "!" + _username + "@127.0.0.1:" + _port;
}

struct sockaddr_storage	* User::getSock()
{
	return (_sock);
}

void User::setNick(std::string const & nick)
{
	_nick = nick;
}

void User::setUsername(std::string const & username)
{
	_username = username;
}

void User::setName(std::string const & name)
{
	_realname = name;
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

const bool User::isConnected() const
{
	return _connected;
}

bool User::isPassAccepted() const
{
	return _pass_ok;
}

void User::setConnected(bool is_connected)
{
	_connected = is_connected;
}

void User::setBuffer(char *buf)
{
	_buffer += buf;
}

std::string User::getBuffer() const
{
	return (_buffer);
}

void User::passwordAccepted()
{
	_pass_ok = true;
}
