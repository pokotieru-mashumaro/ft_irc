#ifndef Channel_HPP
#define Channel_HPP

#include "Client.hpp"

class Channel
{
private:
    std::string _name;
    std::string _password;
	std::vector<Client *>  _operators;
    std::vector<Client *> _clients;
    std::vector<std::string>  _invite_list;

public:
	Channel(std::string name);

    // Client getOperator(){return _operator;};
    std::string getName() const {return _name;};
    std::string getPassword() const {return _password;};
    std::vector<Client *> getOperators() const {return _operators;};
    std::vector<Client *> getClients() const {return _clients;};

    void setName(std::string name) {_name = name;};
    void setPassword(std::string pass) {_password = pass;};
    void setClient(Client *cli){_clients.push_back(cli);};
    void setOperator(Client *cli){_operators.push_back(cli);};
    void setInviteList(std::string nick) {_invite_list.push_back(nick);};

    void unsetClient(Client *cli);
    void unsetOperaor(Client *cli);
    void unsetInviteList(std::string nick);

    bool is_exist(Client *client);
    bool is_exist_string(std::string nickname);
    bool is_operator(Client *client);
    bool is_invited(std::string nick);

    static void join(Server *server, Client *client, std::string param);
    static void part(Server *server, Client *client, std::string param);
    static void mode(Server *server, Client *client, std::string param);
    static void kick(Server *server, Client *client, std::string param);
    static void invite(Server *server, Client *client, std::string param);

    void topic();
};

#endif