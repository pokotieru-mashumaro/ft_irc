#ifndef Channel_HPP
#define Channel_HPP

#include "Client.hpp"

class Channel
{
private:
    std::string _name;
    std::string _password;
    std::string _topic;
    size_t _max_num;
	std::vector<Client *>  _operators;
    std::vector<Client *> _clients;
    std::vector<std::string>  _invite_list;
    std::vector<std::string>  _some_mode;

public:
	Channel(std::string name);

    std::string getName() const {return _name;};
    std::string getPassword() const {return _password;};
    std::string getTopic() const {return _topic;};
    size_t getMaxNum() const {return _max_num;};
    std::vector<Client *> getOperators() const {return _operators;};
    std::vector<Client *> getClients() const {return _clients;};

    void setName(std::string name) {_name = name;};
    void setPassword(std::string pass) {_password = pass;};
    void setTopic(std::string topic) {_topic = topic;};
    void setMaxNum(size_t max_num) {_max_num = max_num;};
    void setClient(Client *cli){_clients.push_back(cli);};
    void setOperator(Client *cli){_operators.push_back(cli);};
    void setInviteList(std::string nick) {_invite_list.push_back(nick);};
    void setMode(std::string mode) {_some_mode.push_back(mode);};

    void unsetClient(Client *cli);
    void unsetOperaor(Client *cli);
    void unsetInviteList(std::string nick);
    void unsetMode(std::string mode);

    bool is_exist(Client *client);
    bool is_exist_string(std::string nickname);
    bool is_operator(Client *client);
    bool is_invited(std::string nick);
    bool is_mode_adaptation(std::string mode);

    static void join(Server *server, Client *client, std::vector<std::string> params);
    static void part(Server *server, Client *client, std::vector<std::string> params);
    static void mode(Server *server, Client *client, std::vector<std::string> params);
    static void kick(Server *server, Client *client, std::vector<std::string> params);
    static void invite(Server *server, Client *client, std::vector<std::string> params);
    static void topic(Server *server, Client *client, std::vector<std::string> params);
};

#endif