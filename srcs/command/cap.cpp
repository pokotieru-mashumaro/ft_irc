#include "../../includes/All.hpp"

void Server::cap(Server *server, Client *client, std::string param)
{
    std::size_t pos = param.find('\n');

    if (pos != std::string::npos)
        param = param.substr(0, pos-1);

    if (param == "LS 302")
    {
        server->SendMsg2Client(client->getFd(), SERVER_NAME + " CAP * LS :multi-prefix");
    }
    else if (param == "REQ :multi-prefix")
        server->SendMsg2Client(client->getFd(), SERVER_NAME + " CAP * ACK :multi-prefix");
    else if (param == "END")
        server->SendMsg2Client(client->getFd(), WELCOME(client->getNickName(), client->getUserName()));
}