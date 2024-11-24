#ifndef Client_HPP
#define Client_HPP

#define NEED_PASSWORD 1
#define NEED_NAMES 2
#define IN_HOME 3
#define IN_CHANNEL 4
#define SET_CHANNELNAME 5

class Channel;
class Server;

class Client
{
private:
	int _fd;
	int _status;
	std::string _ipadd;
	bool _is_passed;
	std::string _nickname;
	std::string _username;
	std::string _realname;
	Channel *_nowchannel;

	Client();

public:
	Client(int fd);

	bool isConnected();

	int getFd() const {return _fd;}
	int getStatus() const {return _status;}
	std::string getNickName() const {return _nickname;}
	std::string getUserName() const {return _username;}
	std::string getRealName() const {return _realname;}
	Channel *getChannel() const {return _nowchannel;}

	void setStatus(int status){_status = status;}
	void setIpAdd(std::string ipadd){_ipadd = ipadd;}
	void setIsPassed(bool is_passed){_is_passed = is_passed;}
	void setNickName(std::string nickname){_nickname = nickname;}
	void setUserName(std::string username){_username = username;}
	void setRealName(std::string realname){_realname = realname;}
	void setChannel(Channel *channel){_nowchannel = channel;}

	static void pass(Server *server, Client *client, std::string param);
	static void nick(Server *server, Client *client, std::string param);
	static void user(Server *server, Client *client, std::string param);
};

#endif