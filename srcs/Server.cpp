#include "../includes/All.hpp"

Server::Server(int port, std::string password)
{
	_port = port;
	_password = password;
	_socket_fd = -1;
	(void)_channels;

	// server
	setCommand("CAP", &Server::cap);

	// client
	setCommand("PASS", &Client::pass);
	setCommand("NICK", &Client::nick);
	setCommand("USER", &Client::user);
	setCommand("PRIVMSG", &Client::privmsg);
	// setCommand("QUIT", &Client::quit);

	// channel
	setCommand("JOIN", &Channel::join);
	setCommand("PART", &Channel::part);
	setCommand("KICK", &Channel::kick);
	setCommand("INVITE", &Channel::invite);
	setCommand("TOPIC", &Channel::topic);
	setCommand("MODE", &Channel::mode);

}

std::vector<std::string> Server::getNickNames()
{
	std::vector<std::string> ret;

	for (size_t i = 0; i < _clients.size(); i++)
	{
		ret.push_back(_clients[i]->getNickName());
	}
	return ret;
}

Client *Server::getClient(std::string nickname)
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (nickname == _clients[i]->getNickName())
			return _clients[i];
	}
	return NULL;
}

Channel *Server::getChannel(std::string channelname)
{
	for (size_t i = 0; i < _channels.size(); i++)
	{
		if (channelname == _channels[i]->getName())
			return _channels[i];
	}
	return NULL;
}

std::vector<std::string> Server::getChannelNames()
{
	std::vector<std::string> ret;

	for (size_t i = 0; i < _channels.size(); i++)
	{
		ret.push_back(_channels[i]->getName());
	}
	return ret;
}


void Server::setCommand(std::string command, function fun)
{
	_commands.insert(std::pair<std::string, function>(command, fun));
}

void Server::unsetChannel(Channel *channel)
{
	for (std::vector<Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it) 
    {
        if (*it == channel) 
        {
            _channels.erase(it);
            break;
        }
    }
}

void Server::ClearClients(int fd)
{
	for (size_t i = 0; i < _fds.size(); i++)
	{
		if (_fds[i].fd == fd)
		{
			_fds.erase(_fds.begin() + i);
			break;
		}
	}
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i]->getFd() == fd)
		{
			_clients.erase(_clients.begin() + i);
			break;
		}
	}
}

bool Server::_is_signal = false;
void Server::SignalHandler(int signum)
{
	(void)signum;
	std::cout << std::endl
			  << "Signal Received!" << std::endl;
	Server::_is_signal = true;
}

void Server::CloseFds()
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		std::cout << RED << "Client <" << _clients[i]->getFd() << "> Disconnected" << WHI << std::endl;
		close(_clients[i]->getFd());
	}
	if (_socket_fd != -1)
	{
		std::cout << RED << "Server <" << _socket_fd << "> Disconnected" << WHI << std::endl;
		close(_socket_fd);
	}
}

void Server::SendMsg2Client(int cli_fd, std::string str)
{
	str = str + +"\r\n";
	ssize_t bytes = send(cli_fd, str.c_str(), str.length(), 0);
	if (bytes == -1)
		std::cout << RED << "やばいよやばいよ" << WHI << std::endl;
}

void Server::SendMsg2Channnel(Client  *client, Channel *channel, std::string str)
{
	str = str + +"\r\n";
	std::vector<Client *>clients = channel->getClients();
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i] != client)
		{
			ssize_t bytes = send(clients[i]->getFd(), str.c_str(), str.length(), 0);
			if (bytes == -1)
				std::cout << RED << "やばいよやばいよ" << WHI << std::endl;
		}
	}
}

void Server::execute(Client *client, std::string command, std::string param)
{
	function fun = _commands[command];

	if (!fun && !client->isConnected())
		return;
	else if (!fun)
		SendMsg2Client(client->getFd(), NOT_COMMAND_ERROR(client->getNickName(), command));
	else
		(fun)(this, client, param);
}

void Server::ReceiveNewData(int fd, int i)
{
	char buff[1024];
	ssize_t bytes;

	memset(buff, 0, sizeof(buff));
	bytes = recv(fd, buff, sizeof(buff) - 1, 0);
	if (bytes <= 0)
	{
		std::cout << RED << "Client <" << fd << "> Disconnected" << WHI << std::endl;
		ClearClients(fd);
		close(fd);
	}
	else
	{
		buff[bytes] = '\0';
		std::cout << YEL << "Client <" << fd << "> Data: " << WHI << buff;

		std::string str = buff;
		std::vector<std::string> lines = split_string(str, '\n');

		// std::cout << "lines--------------------\n";
		// for (size_t j = 0; j < lines.size(); j++)
		// {
		// 	std::cout << "line:" << lines[i] << std::endl;
		// }

		for (size_t j = 0; j < lines.size(); j++)
		{

			std::string command = trim(lines[j]);
			std::string param = "";
			size_t spaceIndex = lines[j].find(' ');

			if (spaceIndex != std::string::npos)
			{
				command = lines[j].substr(0, spaceIndex);
				param = lines[j].substr(spaceIndex + 1);
				param = trim(param);
			}
			execute(_clients[i], command, param);
		}
		// こんなのが必要な可能性あり チャッピー曰く
		//  _fds[i].events = POLLIN | POLLHUP;
		//  _fds[i].revents = 0;
	}
}

void Server::AcceptNewClient()
{
	struct sockaddr_in cliadd;
	struct pollfd NewPoll;
	socklen_t len;
	int incofd;
	Client *cli;

	len = sizeof(cliadd);
	incofd = accept(_socket_fd, (sockaddr *)&(cliadd), &len);
	if (incofd == -1)
	{
		std::cout << "accept() failed" << std::endl;
		return;
	}
	if (fcntl(incofd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cout << "fcntl() failed" << std::endl;
		return;
	}
	NewPoll.fd = incofd;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;
	cli = new Client(incofd);
	cli->setIpAdd(inet_ntoa((cliadd.sin_addr)));
	_clients.push_back(cli);
	_fds.push_back(NewPoll);
	std::cout << GRE << "Client <" << incofd << "> Connected" << WHI << std::endl;
}

void Server::SerSocket()
{
	int en;
	struct sockaddr_in add;
	struct pollfd NewPoll;

	en = 1;
	add.sin_family = AF_INET;
	add.sin_addr.s_addr = INADDR_ANY;
	add.sin_port = htons(this->_port);
	_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket_fd == -1)
		throw(std::runtime_error("faild to create socket"));
	if (setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		throw(std::runtime_error("faild to set option (SO_REUSEADDR) on socket"));
	if (fcntl(_socket_fd, F_SETFL, O_NONBLOCK) == -1)
		throw(std::runtime_error("faild to set option (O_NONBLOCK) on socket"));
	if (bind(_socket_fd, (struct sockaddr *)&add, sizeof(add)) == -1)
		throw(std::runtime_error("faild to bind socket"));
	if (listen(_socket_fd, SOMAXCONN) == -1)
		throw(std::runtime_error("listen() faild"));
	NewPoll.fd = _socket_fd;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;
	_fds.push_back(NewPoll);
}

void Server::ServerInit()
{
	SerSocket();
	std::cout << GRE << "Server <" << _socket_fd << "> Connected" << WHI << std::endl;
	std::cout << "Waiting to accept a connection...\n";
	while (Server::_is_signal == false)
	{
		if ((poll(&_fds[0], _fds.size(), -1) == -1) && Server::_is_signal == false)
			throw(std::runtime_error("poll() faild"));
		for (size_t i = 0; i < _fds.size(); i++)
		{
			if (_fds[i].revents & POLLIN)
			{
				if (_fds[i].fd == _socket_fd)
					AcceptNewClient();
				else
					ReceiveNewData(_fds[i].fd, i - 1); // i-1: _fdsの先頭はサーバーのfd、_clientsの先頭はclientだから一つ詰まっている
			}
		}
	}
	CloseFds();
}
