#include "../../includes/All.hpp"

void Client::user(Server *server, Client *client, std::string param)
{
    std::vector<std::string> params;

    params = split_string(param, ' ');
    if (params.size() != 4)
        return server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "USER"));
    
    client->setUserName(params[0]);
    client->setRealName(params[3]);
    if (client->isConnected())
        server->SendMsg2Client(client->getFd(), WELCOME(client->getNickName(), client->getUserName()));
}