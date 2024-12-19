#include "../../includes/All.hpp"

#define PING_SUCCESS(param) std::string(":" + SERVER_NAME + " PONG " + SERVER_NAME + " :" + param)

void Server::ping(Server *server, Client *client, std::vector<std::string> params)
{
    if (params.size() == 0)
        return server->SendMsg2Client(client->getFd(), ERROR_409(client->getNickName()));
    return server->SendMsg2Client(client->getFd(), PING_SUCCESS(params[0]));
}