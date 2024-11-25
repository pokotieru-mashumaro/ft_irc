#include "../includes/All.hpp"

Channel::Channel(Client *owner, std::string name)
{
    _name = name;
    _password = "";
    _operators.push_back(owner);
    _clients.push_back(owner);

    // owner->setChannel(this);
    owner->setIsOperator(true);
};

void Channel::delete_client(Server *server, Client *client)
{
    std::vector<Client *>::iterator it;

    for (it = _operators.begin(); it != _operators.end(); ++it)
    {
        if (client == *it)
        {
            _operators.erase(it);
            break;
        }
    }
    for (it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (client == *it)
        {
            _clients.erase(it);
            break;
        }
    }

    // クライアントがいなくなったらチャンネルを削除
     std::cout << "clie:" << _clients[0]->getNickName();
    if (_clients.empty())
    {
        std::cout << "00000000000\n";
        std::vector<Channel *>::iterator it;
        std::vector<Channel *> channels = server->getChannels();
        for (it = channels.begin(); it != channels.end(); ++it)
        {
            if (this == *it)
            {
                channels.erase(it);
                break;
            }
        }
    }
}