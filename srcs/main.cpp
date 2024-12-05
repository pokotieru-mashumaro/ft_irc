#include "../includes/All.hpp"

bool check_arg(char **av)
{
	int port = atoi(av[1]);

	for (size_t i = 0; i < strlen(av[1]); i++)
	{
		if ('0' > av[1][i] || av[1][i] > '9')
			return false;
	}
	if (port < 0 || port > 65535)
		return false;
	return true;
}

int main(int ac, char **av)
{
	if (ac != 3 || check_arg(av) == false)
		return 1;
	Server ser(atoi(av[1]), av[2]);

	std::cout << "---- SERVER ----" << std::endl;
	try
	{
		signal(SIGINT, Server::SignalHandler);
		signal(SIGQUIT, Server::SignalHandler);
		ser.ServerInit();
	}
	catch(const std::exception& e)
	{
		ser.CloseFds();
		std::cerr << e.what() << std::endl;
	}
	std::cout << "The Server Closed!" << std::endl;
}
