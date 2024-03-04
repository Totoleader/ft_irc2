#include "Libs.hpp"
#include "Server.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Bad input." << std::endl;
		return 1;
	}
	
	Server serveur(argv[2]);

	serveur.init(argv[1]);
	serveur.listenForEvents();

	return (0);
}

