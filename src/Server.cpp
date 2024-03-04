#include "Libs.hpp"
#include "Server.hpp"

Server *Server::stat_serv = NULL;

Server::Server()
{

}

Server::Server(string password): _password(password)
{
	_channels.reserve(MAX_CHANNELS);
	stat_serv = this;
}

Server::~Server()
{
	
}

void Server::exit_cleanup(int signo)
{
	(void)signo;

	std::cout << "*** Shutting down server... ***" << std::endl;
	for (vector<struct pollfd>::iterator it = stat_serv->_fds.begin(); it != stat_serv->_fds.end(); it++)
	{
		close((*it).fd);
	}
	exit(0);
}

void Server::init(string port)
{
	addrinfo hints;
	int servSocket;

	hints.ai_family = AF_INET;
	memset(&hints, 0, sizeof hints);
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, port.c_str(), &hints, &_servinfo);

	servSocket = socket(_servinfo->ai_family, _servinfo->ai_socktype, _servinfo->ai_protocol);
	new_server(servSocket);

	if (bind(_fds[SERVER_FD].fd, _servinfo->ai_addr, _servinfo->ai_addrlen) != 0)
	{
		std::cerr << "Bind failed." << std::endl;
		exit (EXIT_FAILURE);
	}
	signal(SIGINT, Server::exit_cleanup);

	int status = listen(_fds[SERVER_FD].fd, 5);
	if (status == -1)
		std::cout << "!!!! ERROR LISTEN FAILED !!!!" << std::endl;
}

void Server::listenForEvents()
{
	int poll_events;

	while (true)
	{
		poll_events = poll(_fds.data(), _fds.size(), -1);
	

		if (_fds[SERVER_FD].revents & POLLIN)
		{
			new_client();
			poll_events--;
		}
		for (size_t i = 1; i < _fds.size() && poll_events; i++)
		{
			if (_fds[i].revents & POLLIN)
			{
				handle_event(_fds[i].fd);
				poll_events--;
			}
		}
	}
}

void Server::new_client()
{
	struct pollfd			newClient;
	struct sockaddr_storage cl;
	int						new_fd;
	
	socklen_t	addr_size = sizeof cl;
	new_fd = accept(_fds[0].fd, (struct sockaddr *)&cl, &addr_size);
	int status = fcntl(new_fd, F_SETFL, O_NONBLOCK);
	if (status == -1)
		std::cout << "!!!!! ERROR SETTING SOCKET AS NONBLOCK !!!!!!" << std::endl;

	User newUser(new_fd, (struct sockaddr*)&cl);
	_users.push_back(newUser);
	
	newClient.events = POLLIN;
	newClient.fd = new_fd;
	_fds.push_back(newClient);
}


void Server::new_channel(string channelName, User * sender, string password)
{
	Channel newChannel(channelName, sender, password);
	_channels.push_back(newChannel);
}

void Server::new_server(int fd)
{
	struct pollfd	newClient;
	
	int status = fcntl(fd, F_SETFL, O_NONBLOCK);
	if (status == -1)
		std::cout << "!!!!!! ERROR SETTING SERVER SOCKET AS NONBLOCK !!!!!!" << std::endl;
	newClient.events = POLLIN;
	newClient.fd = fd;
	_fds.push_back(newClient);
}


void Server::handle_event(int fd)
{
	char buf[1024];
	string command;
	size_t		trail;
	User * u = getUser(fd);
	if (!u)
		return ;
	memset(buf, 0, 1024);
	CommandFactory factory;
	ACommand *cmd_to_exec;
	if (recv(u->getFd(), buf, 1024, 0) <= 0)
	{
		disconnect_user(u);
		return ;
	}

	u->setBuffer(buf);
	trail = u->getBuffer().find("\r\n");
	while (trail != string::npos)
	{
		command = u->getBuffer().substr(0, trail);

		cmd_to_exec = factory.getCommand(command, *this, u);
		if (cmd_to_exec)
		{
			cmd_to_exec->execute();
			delete cmd_to_exec;
		}
		std::cout << std::endl << "client send: " << command.c_str() << std::endl;
		u->clean_buffer(&trail);
	}
}

void Server::disconnect_user(User * user)
{
	Quit_Command *quit = new Quit_Command("", *this, user);
	quit->execute();
	delete quit;

	std::cout << std::endl << "User " << user->getNick() << " disconnected.(message to client not implemented)" << std::endl;
	disconnect_fdList(user);
	disconnect_userList(user);
}

bool Server::isNickTaken(string const & nick)
{
	for (list<User>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (it->getNick() == nick)
			return true;
	}
	return false;
}

void Server::removeChannel(Channel & c)
{
	vector<Channel>::const_iterator it = std::find(_channels.begin(), _channels.end(), c);
	if (it != _channels.end())
		_channels.erase(it);
}

void Server::partUserFromChannel(User * u, Channel * c)
{
	if (!c->isInChannel(u))
		return ;

	if (c->isOperator(u))
	{
		c->removeOperator(u);
	}
	c->removeUser(u);
}

void Server::disconnect_fdList(User * user)
{
	int fd = user->getFd();

	for (vector<struct pollfd>::iterator it = _fds.begin(); it != _fds.end(); it++)
	{
		if (fd == (*it).fd)
		{
			close((*it).fd);
			_fds.erase(it); 
			return;
		}
	}
}

void Server::disconnect_userList(User * user)
{
	list<User>::iterator it = std::find(_users.begin(), _users.end(), *user);
	if (it != _users.end())
		_users.erase(it);
}


void Server::joinExistingChannel(User * u, Channel &chan)
{
	string	join = u->getID() + " JOIN " + chan.getName() + "\r\n";
	string listBegin = ":127.0.0.1 353 " + u->getNick() + " = " + chan.getName() + " :";
	string listEnd = ":127.0.0.1 366 " + u->getNick() + " " + chan.getName() + " :End of /NAMES list.\r\n";
	send(u->getFd(), join.c_str(), join.length(), 0);
	chan.sendToChannelExcept(join, u);

	listBegin += chan.getUserList() + "\r\n";
	std::cout << listBegin << std::endl;
	send(u->getFd(), listBegin.c_str(), listBegin.length(), 0);
	send(u->getFd(), listEnd.c_str(), listEnd.length(), 0);
}


User *Server::getUser(int fd)
{
	for (list<User>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (fd == it->getFd())
			return &*it;
	}
	return (NULL);
}

User *Server::getUser(string nick)
{
	for (list<User>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (nick == it->getNick())
			return &*it;
	}
	return (NULL);
}

Channel *Server::getChannel(string channel)
{
	for (unsigned int i = 0; i < _channels.size(); i++)
	{
		if (channel == _channels[i].getName())
			return &_channels[i];
	}
	return NULL;
}

const string& Server::getPassword() const
{
	return (_password);
}

int Server::getChannelSize()
{
	return _channels.size();
}

vector<Channel *> Server::getUserChannels(User * user)
{
	vector<Channel *> out;
	vector<Channel>::iterator it;

	for (it = _channels.begin(); it != _channels.end(); it++)
	{
		if (it->isInChannel(user))
			out.push_back(getChannel(it->getName()));
	}
	return out;
}