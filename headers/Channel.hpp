#ifndef __CHANNEL_H__
#define __CHANNEL_H__


#include "Libs.hpp"


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

	// **** OPERATORS ****

	bool		operator==(Channel const & rhs) const;

	// **** METHODS ****
	
	void				addUser(User & u);
	void				addOperator(User & u);

	void				removeUser(User & u);
	void				removeOperator(User & op);

	// **** GETTERS ****

	const std::string &	getName() const;
	const std::string &	getTopic() const;
	const std::string &	getPassword() const;
	bool				isOperator(User & u) const;
	bool				isInviteOnly() const;
	bool				isInvited(User & u) const;
	bool				isInChannel(User & u) const;
	int					countUsers() const;
	int					countOperators() const;
	
	// **** SETTERS ****

	void	setTopic(const std::string & new_topic);
	void	setPassword(const std::string & new_pass); // mode +k 123
};

#endif // __CHANNEL_H__