#include "Libs.hpp"
#include "Server.hpp"

// void Server::init()
// {
// 	addrinfo hints;
// 	int servSocket;

// 	hints.ai_family = AF_INET;
// 	memset(&hints, 0, sizeof hints); // memset bad
// 	hints.ai_socktype = SOCK_STREAM;
// 	hints.ai_flags = AI_PASSIVE;

// 	getaddrinfo(NULL, "6667", &hints, &_servinfo);

// 	servSocket = socket(_servinfo->ai_family, _servinfo->ai_socktype, _servinfo->ai_protocol);
// 	new_client(servSocket);

// 	if (bind(fds[0].fd, _servinfo->ai_addr, _servinfo->ai_addrlen) != 0)
// 	{
// 		std::cerr << "Bind failed." << endl;
// 		exit (1);
// 	}

// 	listen(fds[0].fd, 10);//!!!10 = max connection
// }

// //boucle principale d'écoute du serveur
// void Server::listenForEvents()
// {
// 	int poll_events;

// 	while (true)
// 	{
// 		poll_events = poll(fds.data(), fds.size(), -1);//attend un event...
	
// 		if (fds[0].revents & POLLIN)//nouveau user
// 		{
// 			new_client();
// 			poll_events--;
// 		}
// 		for (size_t i = 1; i < fds.size() && poll_events; i++)//nouveau message provenant du client
// 		{
// 			if (fds[i].revents & POLLIN)
// 			{
// 				handle_client(i);
// 				poll_events--;
// 			}
// 		}
// 	}
// }

Server::Server()
{
	
}

Server::Server(std::string password)
{
	
}

Server::~Server()
{
	
}
