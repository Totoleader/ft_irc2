// https://datatracker.ietf.org/doc/html/rfc2812#section-3.2.2

#include "Commands/Part_Command.hpp"

Part_Command::Part_Command(std::string msg, Server &server, User &sender) :
ACommand(server, sender, msg),
_partMessage("")
{

}

Part_Command::~Part_Command()
{
}

// Split une liste de channels en string "#chan1,#chan2" vers une list d'instance Channel
// existants si le user est dans le channel
void Part_Command::fillChannels(std::string fillChannelsList)
{
	std::istringstream	iss(fillChannelsList);
	std::string			chanName;

	while (std::getline(iss, chanName, ','))
	{
		Channel * c;
		c = _server.getChannel(chanName);
		if (!c)
		{
			// !!! ERR_NOSUCHCHANNEL
			std::cout << "NO SUCH CHANNEL" << std::endl;
			continue ;
		}
		else if (!c->isInChannel(_sender))
		{
			// !!! ERR_NOTONCHANNEL
			std::cout << "NOT IN CHANNEL" << std::endl;
			continue ;
		}
		else
			_channelsToPart.push_back(c);
	}
}

bool Part_Command::parse()
{
	if (_msg.empty())
	{
		/// !!! needmoreparams
		return ERROR;
	}

	std::istringstream	iss(_msg);
	std::string			chanStringList;
	if (!(iss >> chanStringList) || chanStringList == ":")
	{
		// !!! needmore params
		std::cout << "NEED MORE PARAMS" << std::endl;
		return ERROR;
	}

	fillChannels(chanStringList);
	if (_channelsToPart.empty())	// Liste vide, aucun channel a PART
	{
		std::cout << "LIST EMPTY... RETURNING" << std::endl;
		return ERROR;
	}
	
	// Check si une raison est donnee
	if (iss >> _partMessage)
	{
		// Si le message a le sufixe ':', va chercher les mots apres espaces
		if (_partMessage.at(0) == ':')
		{
			std::string temp;
			while (iss >> temp)
				_partMessage += " " + temp;
			//_partMessage = _partMessage.substr(1);	// remove prefix ':'
		}
	}

	return SUCCESS;
}

void Part_Command::execute()
{
	if (parse() == ERROR)
		return ;
	
	std::vector<Channel *>::iterator it;
	for (it = _channelsToPart.begin(); it != _channelsToPart.end(); it++)
	{
		Channel * channel = *it;
		std::cout << "Parted channel: " << channel->getName() << std::endl;
		std::cout << "Reason: " << _partMessage << std::endl;

		std::string msg = _sender.getID() + " PART " + channel->getName() + " " + _partMessage + "\r\n";
		channel->sendToChannel(msg);

		_server.partUserFromChannel(_sender, *channel);
	}
}