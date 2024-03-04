// https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.2

#include "Commands/Part_Command.hpp"

Part_Command::Part_Command(string msg, Server &server, User * sender) :
ACommand(server, sender, msg),
_partMessage("")
{

}

Part_Command::~Part_Command()
{
}

void Part_Command::fillChannels(string fillChannelsList)
{
	std::istringstream	iss(fillChannelsList);
	string			chanName;
	string			msg;

	while (std::getline(iss, chanName, ','))
	{
		Channel * c;
		c = _server.getChannel(chanName);
		if (!c)
		{
			msg = errorMessage(403, chanName, "0", "0"); 
			send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
			continue ;
		}
		else if (!c->isInChannel(_sender))
		{
			msg = errorMessage(442, chanName, "0", "0"); 
			send(_sender->getFd(), msg.c_str(), msg.length(), 0); 
			continue ;
		}
		else
			_channelsToPart.push_back(c);
	}
}

bool Part_Command::parse()
{
	string msg;

	if (_msg.empty())
	{
		msg = errorMessage(461, "PART", "0", "0"); 
		send(_sender->getFd(), msg.c_str(), msg.length(), 0);  
		return ERROR;
	}

	std::istringstream	iss(_msg);
	string			chanStringList;
	if (!(iss >> chanStringList) || chanStringList == ":")
	{
		msg = errorMessage(461, "PART", "0", "0"); 
		send(_sender->getFd(), msg.c_str(), msg.length(), 0);   
		return ERROR;
	}

	fillChannels(chanStringList);
	if (_channelsToPart.empty())
	{
		return ERROR;
	}
	
	if (iss >> _partMessage)
	{
		if (_partMessage.at(0) == ':')
		{
			string temp;
			while (iss >> temp)
				_partMessage += " " + temp;
		}
	}

	return SUCCESS;
}

void Part_Command::execute()
{
	if (parse() == ERROR)
		return ;
	
	vector<Channel *>::iterator it;
	for (it = _channelsToPart.begin(); it != _channelsToPart.end(); it++)
	{
		Channel * channel = *it;

		std::cout << "Parted channel: " << channel->getName() << std::endl;
		std::cout << "Reason: " << _partMessage << std::endl;

		string msg = _sender->getID() + " PART " + channel->getName() + " " + _partMessage + "\r\n";
		channel->sendToChannel(msg);

		_server.partUserFromChannel(_sender, channel);
	}
}