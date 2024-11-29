#include "../includes/All.hpp"

Channel::Channel(std::string name)
{
    _name = name;
    _password = "";
    _topic = "";
};

void Channel::unsetClient(Client *cli)
{
    for (std::vector<Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it) 
    {
        if (*it == cli) 
        {
            _clients.erase(it);
            break;
        }
    }
}

void Channel::unsetOperaor(Client *cli)
{
    for (std::vector<Client *>::iterator it = _operators.begin(); it != _operators.end(); ++it)
     {
        if (*it == cli) 
        {
            _operators.erase(it);
            break;
        }
    }
}

void Channel::unsetInviteList(std::string nick)
{
    for (std::vector<std::string>::iterator it = _invite_list.begin(); it != _invite_list.end(); ++it)
     {
        if (*it == nick) 
        {
            _invite_list.erase(it);
            break;
        }
    }
}

bool Channel::is_exist(Client *client)
{
    for (size_t i = 0; i < _clients.size(); i++)
    {
        if (_clients[i] == client)
            return true;
    }
    return false;
}

bool Channel::is_exist_string(std::string nickname)
{
    for (size_t i = 0; i < _clients.size(); i++)
    {
        if (_clients[i]->getNickName() == nickname)
            return true;
    }
    return false;
}

bool Channel::is_operator(Client *client)
{
    for (size_t i = 0; i < _operators.size(); i++)
    {
        if (_operators[i] == client)
            return true;
    }
    return false;
}

bool Channel::is_invited(std::string nick)
{
    for (size_t i = 0; i < _invite_list.size(); i++)
    {
        if (_invite_list[i] == nick)
            return true;
    }
    return false;
}