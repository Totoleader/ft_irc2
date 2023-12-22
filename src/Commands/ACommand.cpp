#include "Libs.hpp"
#include "Commands/ACommand.hpp"

ACommand::ACommand(Server & server, User & sender, std::string msg): _server(server), _sender(sender), _msg(msg)
{
	
}

ACommand::~ACommand()
{
	
}

void ACommand::_connectUser()
{
	std::string msg001 = ":127.0.0.1 001 " + _sender.getNick() + " :Welcome to the Internet Relay Network\r\n";
	std::string msg002 = ":127.0.0.1 002 " + _sender.getNick() + " :Your host is ft_irc, running version 0.1\r\n";
	std::string msg003 = ":127.0.0.1 003 " + _sender.getNick() + " :This server was created NOW\r\n";
	std::string msg004 = ":127.0.0.1 004 " + _sender.getNick() + " ft_irc 0.1 o itkol\r\n";

	send(_sender.getFd(), msg001.c_str(), msg001.length(), 0);
	send(_sender.getFd(), msg002.c_str(), msg002.length(), 0);
	send(_sender.getFd(), msg003.c_str(), msg003.length(), 0);
	send(_sender.getFd(), msg004.c_str(), msg004.length(), 0);
	_sender.setConnected(true);
}


string ACommand::errorMessage(int key, string param1, string param2, string param3)
{
    if (key == 401) // 401    ERR_NOSUCHNICK "<nickname> :No such nick/channel"
    	return(":127.0.0.1 401 ERR_NOSUCHNICK " + param1 + " :No such nick/channel\r\n");
    
    if (key == 403) // 403    ERR_NOSUCHCHANNEL "<channel name> :No such channel"
    	return(":127.0.0.1 403 ERR_NOSUCHCHANNEL " + param1 + " :No such channel\r\n");    
    
    if (key == 404) // 404    ERR_CANNOTSENDTOCHAN "<channel name> :Cannot send to channel" 
    	return(":127.0.0.1 404 ERR_CANNOTSENDTOCHAN " + param1 + " :Cannot send to channel\r\n"); 
    
    if (key == 405) // 405    ERR_TOOMANYCHANNELS "<channel name> :You have joined too many channels"
    	return(":127.0.0.1 405 ERR_TOOMANYCHANNELS " + param1 + " :You have joined too many channels\r\n");  
    
    if (key == 407) // 407    ERR_TOOMANYTARGETS "<target> :<error code> recipients. <abort message>"
    	return(":127.0.0.1 403 ERR_TOOMANYTARGETS " + param1 + " :" + param2 + " recipients. " + param3 + "\r\n");  
    
    if (key == 411) // 411    ERR_NORECIPIENT ":No recipient given (<command>)"                
    	return(":127.0.0.1 411 ERR_NORECIPIENT :No recipient given (" + param1 + ")\r\n");  
    
    if (key == 412) // 412    ERR_NOTEXTTOSEND ":No text to send"
    	return(":127.0.0.1 412 ERR_NOTEXTTOSEND :No text to send\r\n");  
   
    if (key == 413) // 413    ERR_NOTOPLEVEL "<mask> :No toplevel domain specified"
    	return(":127.0.0.1 413 ERR_NOTOPLEVEL " + param1 + " :No toplevel domain specified\r\n");  
   
    if (key == 414) // 414    ERR_WILDTOPLEVEL "<mask> :Wildcard in toplevel domain"                
    	return(":127.0.0.1 414 ERR_WILDTOPLEVEL " + param1 + " :Wildcard in toplevel domain\r\n");
   
    if (key == 431) // 431    ERR_NONICKNAMEGIVEN ":No nickname given"           
    	return(":127.0.0.1 431 ERR_NONICKNAMEGIVEN :No nickname given\r\n");
   
    if (key == 432) // 432    ERR_ERRONEUSNICKNAME "<nick> :Erroneous nickname"
    	return(":127.0.0.1 432 ERR_ERRONEUSNICKNAME " + param1 + " :Erroneous nickname\r\n");
    
    if (key == 433) // 433    ERR_NICKNAMEINUSE "<nick> :Nickname is already in use"   
    	return(":127.0.0.1 433 ERR_NICKNAMEINUSE " + param1 + " :Nickname is already in use\r\n");
   
    if (key == 436) // 436    ERR_NICKCOLLISION "<nick> :Nickname collision KILL from <user>@<host>"          
    	return(":127.0.0.1 436 ERR_NICKCOLLISION " + param1 + " :Nickname collision KILL from " + param2 + "@127.0.0.1\r\n");
   
    if (key == 437) // 437    ERR_UNAVAILRESOURCE "<nick/channel> :Nick/channel is temporarily unavailable"    
    	return(":127.0.0.1 437 ERR_UNAVAILRESOURCE " + param1 + " :Nick/channel is temporarily unavailable\r\n");
   
    if (key == 441) // 441    ERR_USERNOTINCHANNEL "<nick> <channel> :They aren't on that channel"            
    	return(":127.0.0.1 441 ERR_USERNOTINCHANNEL " + param1 + " " + param2 + " :They aren't on that channel\r\n");
   
    if (key == 442) // 442    ERR_NOTONCHANNEL "<channel> :You're not on that channel"
    	return(":127.0.0.1 442 ERR_NOTONCHANNEL " + param1 + " :You're not on that channel\r\n");
   
    if (key == 443) // 443    ERR_USERONCHANNEL "<user> <channel> :is already on channel"
    	return(":127.0.0.1 443 ERR_USERONCHANNEL " + param1 + " " + param2 + " :is already on channel\r\n");
   
    if (key == 461) // 461    ERR_NEEDMOREPARAMS "<command> :Not enough parameters"   
    	return(":127.0.0.1 461 ERR_NEEDMOREPARAMS " + param1 + " :Not enough parameters\r\n");
   
    if (key == 462) // 462    ERR_ALREADYREGISTRED ":Unauthorized command (already registered)" 
    	return(":127.0.0.1 462 PAERR_ALREADYREGISTRED :Unauthorized command (already registered)\r\n");
   
    if (key == 467) // 467    ERR_KEYSET "<channel> :Channel key already set" 
    	return(":127.0.0.1 467 ERR_KEYSET " + param1 + " :Channel key already set\r\n");
   
    if (key == 471) // 471    ERR_CHANNELISFULL "<channel> :Cannot join channel (+l)"    
    	return(":127.0.0.1 471 ERR_CHANNELISFULL " + param1 + " :Cannot join channel (+l)\r\n");
   
    if (key == 472) // 472    ERR_UNKNOWNMODE "<char> :is unknown mode char to me for <channel>"
    	return(":127.0.0.1 472 ERR_UNKNOWNMODE " + param1 + " :is unknown mode char to me for " + param2 + "\r\n");
  
    if (key == 473) // 473    ERR_INVITEONLYCHAN "<channel> :Cannot join channel (+i)" 
    	return(":127.0.0.1 473 ERR_INVITEONLYCHAN " + param1 + " :Cannot join channel (+i)\r\n");
  
    if (key == 474) // 474    ERR_BANNEDFROMCHAN "<channel> :Cannot join channel (+b)"       
    	return(":127.0.0.1 474 ERR_BANNEDFROMCHAN " + param1 + " :Cannot join channel (+b)\r\n");
   
    if (key == 475) // 475    ERR_BADCHANNELKEY "<channel> :Cannot join channel (+k)"  
    	return(":127.0.0.1 475 ERR_BADCHANNELKEY " + param1 + " :Cannot join channel (+k)\r\n");
   
    if (key == 476) // 476    ERR_BADCHANMASK "<channel> :Bad Channel Mask"  
    	return(":127.0.0.1 476 ERR_BADCHANMASK " + param1 + " :Bad Channel Mask\r\n");
    
    if (key == 477) // 477    ERR_NOCHANMODES "<channel> :Channel doesn't support modes" 
    	return(":127.0.0.1 477 ERR_NOCHANMODES " + param1 + " :Channel doesn't support modes\r\n");
   
    if (key == 482) // 482    ERR_CHANOPRIVSNEEDED "<channel> :You're not channel operator"
    	return(":127.0.0.1 482 ERR_CHANOPRIVSNEEDED " + param1 + " :You're not channel operator\r\n");
    
    if (key == 484) // 484    ERR_RESTRICTED ":Your connection is restricted!"
    	return(":127.0.0.1 484 ERR_RESTRICTED :Your connection is restricted!\r\n");
  
    else // 502    ERR_USERSDONTMATCH ":Cannot change mode for other users"
    	return(":127.0.0.1  502 ERR_USERSDONTMATCH :Cannot change mode for other users\r\n");                                                                                                                
}

/*				
string ACommand::replyMessage(int key, string param1, string param2, string param3)
	msg = ":127.0.0.1 221 <user mode string>\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0); 

	msg = ":127.0.0.1 301 Alex :my away message\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0); 

	msg = ":127.0.0.1 324 <channel> <mode> <mode params>\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0); 

	msg = ":127.0.0.1 325 #channel Alex\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0); 
  
	msg = ":127.0.0.1 331 #channel :No topic is set\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0);                 

	msg = ":127.0.0.1 332 #channel :A topic name\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0); 
 
	msg = ":127.0.0.1 341 #channel Alex\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0); 

	msg = ":127.0.0.1 346 <channel> <invitemask>\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0);               

	msg = ":127.0.0.1 347 #channel :End of channel invite list\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0);   
  
	msg = ":127.0.0.1 348 <channel> <exceptionmask>\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0);   

	msg = ":127.0.0.1 349 #channel :End of channel exception list\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0);   
   
	msg = ":127.0.0.1 367 #channel <banmask>\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0);              

	msg = ":127.0.0.1 368 #channel :End of channel ban list\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0);   
}

string ACommand::clientMessage(int key, string param1, string param2, string param3)
{
	msg = ":Alex!Alex@127.0.0.1 TOPIC #channel :New topic\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0); 

	msg = ":Alex!Alex@127.0.0.1 PRIVMSG User2 :Are you receiving this message\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0); 

	msg = ":Alex!Alex@127.0.0.1 JOIN #Twilight_zone\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0); 

	msg = ":Alex!Alex@127.0.0.1 KICK #channel User2\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0); 

	msg = ":Alex!Alex@127.0.0.1 INVITE User2 #channel\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0); 

	msg = ":Alex!Alex@127.0.0.1 PART #channel :I lost\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0); 

	msg = ":Alex!Alex@127.0.0.1 NICK Kilroy\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0); 

	msg = ":Alex!Alex@127.0.0.1 QUIT :Gone to have lunch\r\n";
	send(u.getFd(), msg.c_str(), msg.length(), 0);
}
*/