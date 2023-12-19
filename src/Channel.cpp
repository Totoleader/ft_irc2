#include "Libs.hpp"
#include "Channel.hpp"

Channel::Channel()
{
}

Channel::Channel(std::string name, User &creator, std::string pass) :
_name(name),
_topic(""),
_password(pass)
{
	this->_channelUsers.push_back(creator);
	this->_operators.push_back(creator.getNick());
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
void	Channel::addOperator(User & u)	{ _operators.push_back(u.getNick()); }

void	Channel::removeUser(User & u)
{
	std::list<User>::const_iterator it = std::find(_channelUsers.begin(), _channelUsers.end(), u);
	if (it != _channelUsers.end())
		_channelUsers.erase(it);
}

void	Channel::removeOperator(User & op)
{
	std::list<std::string>::const_iterator it = std::find(_operators.begin(), _operators.end(), op.getNick());
	if (it != _operators.end())
		_operators.erase(it);
}

void	Channel::partUser(User &u)
{
	
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
	std::list<std::string>::const_iterator it = std::find(_operators.begin(), _operators.end(), u.getNick());
	return (it != _operators.end());
}

const bool	Channel::isInvited(User &u) const
{
	std::list<std::string>::const_iterator it = std::find(_inviteList.begin(), _inviteList.end(), u.getNick());
	return (it != _inviteList.end());
}

const bool	Channel::isInChannel(User & u) const
{
	std::list<User>::const_iterator it = std::find(_channelUsers.begin(), _channelUsers.end(), u);
	return (it != _channelUsers.end());
}

/********************
	SETTERS
*********************/
void	Channel::setTopic(const std::string & new_topic)	{ this->_topic = new_topic; }
void	Channel::setPassword(const std::string & new_pass)	{ this->_password = new_pass; }