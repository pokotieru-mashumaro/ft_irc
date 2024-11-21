#ifndef Server_HPP
#define Server_HPP

class Server;

typedef void (*function)(Server *server, Client *client, std::string data);

class Server
{
private:
	int _port;
	std::string _password;
	int _socket_fd;
	static bool _is_signal;
	std::vector<Client *> _clients;
	std::vector<Channel *> _channels;
	std::vector<struct pollfd> _fds;
	std::map<std::string, function>	_commands;

	Server();

public:
	Server(int port, std::string password);

	void ServerInit();
	void SerSocket();
	void AcceptNewClient();
	void ReceiveNewData(int fd);

	static void SignalHandler(int signum);

	void CloseFds();
	void ClearClients(int fd);


	std::vector<std::string> getChannelNames();

	void setCommand(std::string command, function fun);
};
#endif
