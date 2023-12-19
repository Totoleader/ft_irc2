#include "Libs.hpp"
#include "Channel.hpp"

Channel::Channel()
{
}

Channel::Channel(std::string name, User &creator, std::string pass) :
_name(name),
_topic(""),
_pass(pass)
{
	this->_channelUsers.push_back(creator);
	this->_operators.push_back(creator.getNick());
}

Channel::~Channel()
{
}

bool	Channel::operator==(Channel const & rhs)
{
	return this->getName() == rhs.getName();
}

/********************
	GETTERS
*********************/
const std::string &	Channel::getName() const		{ return _name; }
const std::string &	Channel::getPassword() const	{ return _password; }
bool				Channel::isInviteOnly()	const 	{ return _isInviteOnly; }

bool	Channel::isOperator(User &u)
{
	std::list<std::string>::iterator it = std::find(_operators.begin(), _operators.end(), u.getNick());
	return (it != _operators.end());
}

bool	Channel::isInvited(User &u)
{
	std::list<std::string>::iterator it = std::find(_inviteList.begin(), _inviteList.end(), u.getNick());
	return (it != _inviteList.end());
}

