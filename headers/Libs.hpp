#ifndef __LIBS_H__
#define __LIBS_H__


#define SERVER_FD 0
#define ERROR 0
#define SUCCESS 1
#define NO_LIMIT -1

//Libs
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <iostream>
#include <poll.h>
#include <vector>
#include <list>
#include <map>
#include <fcntl.h>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <unistd.h>

using std::string;
using std::vector;

# include "Server.hpp"
# include "User.hpp"
# include "Channel.hpp"

# include "Commands/ACommand.hpp"
# include "Commands/CommandFactory.hpp"
# include "Commands/User_Command.hpp"
# include "Commands/Nick_Command.hpp"
# include "Commands/Join_Command.hpp"
# include "Commands/Pass_Command.hpp"
# include "Commands/Topic_Command.hpp"
# include "Commands/Privmsg_Command.hpp"
# include "Commands/Part_Command.hpp"
# include "Commands/Invite_Command.hpp"
# include "Commands/Kick_Command.hpp"



#endif // __LIBS_H__