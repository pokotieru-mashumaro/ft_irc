#ifndef Channel_HPP
#define Channel_HPP

#include "Client.hpp"

class Channel
{
private:
    std::string _name;
	std::vector<Client *>  _operators;
    std::vector<Client *> _clients;

public:
	Channel(Client *owner)
	{
        _name = "";
        _operators.push_back(owner);
        _clients.push_back(owner);
    };

    // Client getOperator(){return _operator;};
    std::string getName() const {return _name;};
    std::vector<Client *> getOperators() const {return _operators;};
    std::vector<Client *> getClients() const {return _clients;};

    void setName(std::string name) {_name = name;};
    void setClient(Client *cli){_clients.push_back(cli);};

    void kick();
    void invite();
    void topic();
    void mode(int mode);
};

#endif