#include "../includes/All.hpp"

Channel::Channel(Client *owner, std::string name)
{
    _name = name;
    _password = "";
    _operators.push_back(owner);
    _clients.push_back(owner);

    owner->setChannel(this);
    owner->setIsOperator(true);
};