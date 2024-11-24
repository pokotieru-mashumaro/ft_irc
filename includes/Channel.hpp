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

public:
	Channel(Client *owner, std::string name);

    // Client getOperator(){return _operator;};
    std::string getName() const {return _name;};
    std::string getPassword() const {return _password;};
    std::vector<Client *> getOperators() const {return _operators;};
    std::vector<Client *> getClients() const {return _clients;};

    void setName(std::string name) {_name = name;};
    void setPassword(std::string pass) {_password = pass;};
    void setClient(Client *cli){_clients.push_back(cli);};

    static void join(Server *server, Client *client, std::string param);

    void kick();
    void invite();
    void topic();
    void mode(int mode);
};

#endif