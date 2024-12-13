#include "../../includes/All.hpp"

void Client::pass(Server *server, Client *client, std::vector<std::string> params)
{
    if (params.size() != 1)
        server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "PASS"));
    if (params[0] == server->getPassword())
        client->setIsPassed(true);
    if (client->isConnected())
        server->SendMsg2Client(client->getFd(), WELCOME(client->getNickName(), client->getUserName()));
}