#include "../../includes/All.hpp"


void Client::pass(Server *server, Client *client, std::string param)
{
     size_t spaceIndex = param.find(' ');

    if (param == "" || spaceIndex != std::string::npos)
        server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "PASS"));

    // std::cout << param << "==" << server->getPassword() << "=\n";
    if (param == server->getPassword())
        client->setIsPassed(true);
}