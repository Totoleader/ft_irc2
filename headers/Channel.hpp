#ifndef __CHANNEL_H__
#define __CHANNEL_H__


#include "Libs.hpp"


class Channel
{
private:
	std::string 				_name;
	std::string 				_topic;
	std::string 				_password;

	std::vector<User>			_channelUsers;
	std::vector<User>			_operators;

	//mode
	bool						_isInviteOnly;
	std::vector<User>			_inviteList;

public:
	Channel();
	Channel(std::string name, User &creator, std::string pass);
	Channel(std::string name, User &creator);
	~Channel();

	// **** OPERATORS ****

	bool		operator==(Channel const & rhs) const;

	// **** METHODS ****
	void				addUser(User & u);
	void				addOperator(User & u);

	void				removeUser(User & u);
	void				removeOperator(User & op);

	void				sendToChannel(std::string message);
	void 				sendToChannelExcept(std::string message, User &except);
	void				addToWhiteList(User &newUser);

	// **** GETTERS ****

	const std::string &	getName() const;
	const std::string &	getTopic() const;
	const std::string &	getPassword() const;
	bool			isOperator(User & u) const;
	bool			isInviteOnly() const;
	bool			isInvited(User & u) const;
	bool			isInChannel(const User & u) const;
	int			countUsers() const;
	bool 				isWhitelisted(User &u);
	const std::string	getUserList();

	// **** SETTERS ****

	void	setTopic(const std::string & new_topic);
	void	setPassword(const std::string & new_pass); // mode +k 123
};

#endif // __CHANNEL_H__