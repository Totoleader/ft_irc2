#include "Libs.hpp"
#include "Channel.hpp"

Channel::Channel()
{
}

Channel::Channel(std::string name, User &creator, std::string pass) :
_name(name),
_topic(""),
_password(pass),
_isInviteOnly(false)
{
	this->_channelUsers.push_back(creator);
	this->_operators.push_back(creator);
}

Channel::Channel(std::string name, User &creator) :
_name(name),
_topic(""),
_password(""),
_isInviteOnly(false)
{
	this->_channelUsers.push_back(creator);
	this->_operators.push_back(creator);
}

Channel::~Channel()
{
}

/********************
	OPERATORS
*********************/
bool	Channel::operator==(Channel const & rhs) const
{
	return this->getName() == rhs.getName();
}

/********************
	METHODS
*********************/

void	Channel::addUser(User & u)		{ _channelUsers.push_back(u); }
void	Channel::addOperator(User & u)	{ _operators.push_back(u); }

void	Channel::removeUser(User & u)
{
	std::vector<User>::const_iterator it = std::find(_channelUsers.begin(), _channelUsers.end(), u);
	if (it != _channelUsers.end())
		_channelUsers.erase(it);
}

void	Channel::removeOperator(User & op)
{
	std::vector<User>::const_iterator it = std::find(_operators.begin(), _operators.end(), op);
	if (it != _operators.end())
		_operators.erase(it);
}

void	Channel::partUser(User &u)
{
	
}

void Channel::sendToChannel(std::string message)
{
	for (std::vector<User>::iterator it = _channelUsers.begin(); it != _channelUsers.end(); it++)
    {
    	send(it->getFd(), message.c_str(), message.length(), 0);
    }
}

void Channel::sendToChannelExcept(std::string message, User &except)
{
	for (std::vector<User>::iterator it = _channelUsers.begin(); it != _channelUsers.end(); it++)
    {
		if (it->getNick() != except.getNick())
		{
    		send(it->getFd(), message.c_str(), message.length(), 0);
		}	
    }
}

bool Channel::isWhitelisted(User &u)
{
	for (std::vector<User>::iterator it = _inviteList.begin(); it != _inviteList.end(); it++)
	{
		if (u.getNick() == it->getNick())
			return true;
	}
	return false;
}

void	Channel::addToWhiteList(User &newUser)
{
	_inviteList.push_back(newUser);
}

/********************
	GETTERS
*********************/

const std::string &	Channel::getName() const		{ return _name; }
const std::string & Channel::getTopic() const		{ return _topic; }
const std::string &	Channel::getPassword() const	{ return _password; }
const bool			Channel::isInviteOnly()	const 	{ return _isInviteOnly; }
const int			Channel::countUsers() const		{ return _channelUsers.size(); }

const bool	Channel::isOperator(User &u) const
{
	std::vector<User>::const_iterator it = std::find(_operators.begin(), _operators.end(), u);
	return (it != _operators.end());
}

const bool	Channel::isInvited(User &u) const
{
	std::vector<User>::const_iterator it = std::find(_inviteList.begin(), _inviteList.end(), u);
	return (it != _inviteList.end());
}

const bool	Channel::isInChannel(User & u) const
{
	std::vector<User>::const_iterator it = std::find(_channelUsers.begin(), _channelUsers.end(), u);
	return (it != _channelUsers.end());
}

// TODO: mettre les ops en 1er dans la liste
const std::string Channel::getUserList()
{
	std::vector<User>::iterator it = _channelUsers.begin();
	std::string	userList = "";

	for (; it != _channelUsers.end(); it++)
	{
		std::string user = "";
		if (isOperator(*it))
			user += "@";
		user += it->getNick();
		if (std::next(it) != _channelUsers.end())
			user += " ";
		userList += user;
	}
	return userList;
}

/********************
	SETTERS
*********************/
void	Channel::setTopic(const std::string & new_topic)	{ this->_topic = new_topic; }
void	Channel::setPassword(const std::string & new_pass)	{ this->_password = new_pass; }