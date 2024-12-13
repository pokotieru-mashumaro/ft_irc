#include "../../includes/All.hpp"

void Server::cap(Server *server, Client *client, std::vector<std::string> params)
{
    if (params.size() == 2 &&  params[0] == "LS" && params[1] == "302")
        server->SendMsg2Client(client->getFd(), SERVER_NAME + " CAP * LS :multi-prefix");
    else if (params.size() == 2 && params[0] == "REQ" && params[1] == ":multi-prefix")
        server->SendMsg2Client(client->getFd(), SERVER_NAME + " CAP * ACK :multi-prefix");
    else if (params[0] == "END")
        server->SendMsg2Client(client->getFd(), WELCOME(client->getNickName(), client->getUserName()));
}