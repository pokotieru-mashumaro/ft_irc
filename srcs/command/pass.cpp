#include "../../includes/All.hpp"

void Client::pass(Server *server, Client *client, std::string param)
{
     size_t spaceIndex = param.find(' ');

    if (param == "" || spaceIndex != std::string::npos)
        server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "PASS"));

    if (param == server->getPassword())
        client->setIsPassed(true);
    if (client->isConnected())
        server->SendMsg2Client(client->getFd(), WELCOME(client->getNickName(), client->getUserName()));
}