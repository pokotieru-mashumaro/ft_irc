#ifndef Client_HPP
#define Client_HPP

class Channel;
class Server;

class Client
{
private:
	int _fd;
	std::string _ipadd;
	bool _is_passed;
	std::string _nickname;
	std::string _username;
	std::string _realname;

	Client();

public:
	Client(int fd);

	bool isConnected();

	int getFd() const {return _fd;}
	std::string getNickName() const {return _nickname;}
	std::string getUserName() const {return _username;}
	std::string getRealName() const {return _realname;}

	void setIpAdd(std::string ipadd){_ipadd = ipadd;}
	void setIsPassed(bool is_passed){_is_passed = is_passed;}
	void setNickName(std::string nickname){_nickname = nickname;}
	void setUserName(std::string username){_username = username;}
	void setRealName(std::string realname){_realname = realname;}

	static void pass(Server *server, Client *client, std::string param);
	static void nick(Server *server, Client *client, std::string param);
	static void user(Server *server, Client *client, std::string param);
	static void privmsg(Server *server, Client *client, std::string param);
	static void quit(Server *server, Client *client, std::string param);
};

#endif