#include "Libs.hpp"
#include "Server.hpp"

Server::Server()
{
	
}

Server::Server(std::string password) : _password(password)
{
	
}

Server::~Server()
{
	
}

/********************
	SOCKETS
*********************/

void Server::init()
{
	addrinfo hints;
	int servSocket;

	hints.ai_family = AF_INET;
	memset(&hints, 0, sizeof hints); // memset bad
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, "6667", &hints, &_servinfo);

	servSocket = socket(_servinfo->ai_family, _servinfo->ai_socktype, _servinfo->ai_protocol);
	new_server(servSocket);

	if (bind(_fds[SERVER_FD].fd, _servinfo->ai_addr, _servinfo->ai_addrlen) != 0)
	{
		std::cerr << "Bind failed." << std::endl;
		exit (EXIT_FAILURE);
	}

	listen(_fds[SERVER_FD].fd, 10);//!!!10 = max connection
}

//boucle principale d'ecoute du serveur
void Server::listenForEvents()
{
	int poll_events;

	while (true)
	{
		poll_events = poll(_fds.data(), _fds.size(), -1);//attend un event...
	
		if (_fds[SERVER_FD].revents & POLLIN)//nouveau user
		{
			new_client();
			poll_events--;
		}
		for (size_t i = 1; i < _fds.size() && poll_events; i++)//nouveau message provenant du client
		{
			if (_fds[i].revents & POLLIN)
			{
				handle_event(i);
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
	fcntl(new_fd, F_SETFL, O_NONBLOCK);

	User newUser(new_fd, (struct sockaddr*)&cl);
	_users.push_back(newUser);
	
	newClient.events = POLLIN;
	newClient.fd = new_fd;
	_fds.push_back(newClient);
}

void Server::new_server(int fd)
{
	struct pollfd	newClient;
	
	fcntl(fd, F_SETFL, O_NONBLOCK);
	newClient.events = POLLIN;
	newClient.fd = fd;
	_fds.push_back(newClient);
}


void Server::handle_event(int client_i)
{
	char buf[100];
	std::string command;
	size_t		trail;
	int i;
	i = client_i - 1;
	memset(buf, 0, 100); // memset bad
	CommandFactory factory;
	ACommand *cmd_to_exec;
	if (recv(_fds[client_i].fd, buf, 100, 0) <= 0)
	{
		// disconnect_user(client_i); 
		return ;
	}

	_users[i].setBuffer(buf);
	trail = _users[i].getBuffer().find("\r\n");
	while (trail != std::string::npos)
	{
		command = _users[i].getBuffer().substr(0, trail);
		
		cmd_to_exec = factory.getCommand(command, *this, _users[i]);
		if (cmd_to_exec)
		{
			cmd_to_exec->execute();
			delete cmd_to_exec;
		}
		std::cout << std::endl << "client send: " << command.c_str() << std::endl;
		_users[i].clean_buffer(&trail);
	}
}

/********************
	METHODS
*********************/
bool	Server::isNickTaken(std::string const & nick)
{
	std::vector<User>::iterator it;

	for (it = _users.begin(); it != _users.end(); it++)
		if (it->getNick() == nick)
			return true;
	return false;
}

/********************
	GETTERS
*********************/

User *Server::getUser(int fd)
{
	for (unsigned int i = 0; i < _users.size(); i++)
	{
		if (fd == _users[i].getFd())
			return &_users[i];
	}
	return (NULL);
}

User *Server::getUser(std::string nick)
{
	for (unsigned int i = 0; i < _users.size(); i++)
	{
		if (nick == _users[i].getNick())
			return &_users[i];
	}
	return (NULL);
}

const std::string& Server::getPassword() const
{
	return (_password);
}
