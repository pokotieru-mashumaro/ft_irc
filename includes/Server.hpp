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
	void ReceiveNewData(int fd, int i);

	static void SignalHandler(int signum);

	void CloseFds();
	void ClearClients(int fd);

	void SendMsg2Client(int cli_fd, std::string str);
	void execute(Client *client, std::string command, std::string param);

	std::string getPassword(){return _password;};
	std::vector<Channel *> getChannels(){return _channels;};
	std::vector<std::string> getNickNames();
	std::vector<std::string> getChannelNames();
	Channel *getChannel(std::string channelname);

	void setCommand(std::string command, function fun);
	void setChannels(Channel *channel) {_channels.push_back(channel);};

	static void cap(Server *server, Client *client, std::string param);
};
#endif
