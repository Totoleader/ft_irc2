#ifndef __Part_Command_H__
#define __Part_Command_H__

#include "Libs.hpp"

class Part_Command : public ACommand
{
	private:
		std::vector<Channel *>		_channelsToPart;
		std::string					_partMessage;

	public:
		Part_Command(std::string msg, Server &server, User &sender);
		~Part_Command();

		void fillChannels(std::string channelStringList);

		bool parse();
		void execute();
};

#endif //__Part_Command_H__
