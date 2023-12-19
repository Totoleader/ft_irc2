#ifndef __CHANNEL_H__
#define __CHANNEL_H__


#include "Libs.hpp"
# include "Server.hpp"
# include "Commands/ACommand.hpp"
# include "User.hpp"

class Channel
{
private:
	std::string 				_name;
	std::string 				_topic;
	std::string 				_password;

	std::list<User>				_channelUsers;
	std::list<std::string>		_operators;		// utiliser Nick

	//mode
	bool						_isInviteOnly;
	std::list<std::string>		_inviteList;	// utiliser Nick
public:
	Channel();
	Channel(std::string name, User &creator, std::string pass);
	~Channel();

	bool		operator==(Channel const & rhs);

	// GETTERS
	const std::string &	getName() const;
	const std::string &	getTopic() const;
	const std::string &	getPassword() const;
	const bool			isOperator(User &u) const;
	const bool			isInviteOnly() const;
	const bool			isInvited(User &u) const;
	
	// SETTERS
	void	setTopic(const std::string & new_topic);
	void	setPassword(const std::string & new_pass); // mode +k 123
};

#endif // __CHANNEL_H__