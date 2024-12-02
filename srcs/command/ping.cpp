#include "../../includes/All.hpp"

#define PING_SUCCESS(param) std::string(":" + SERVER_NAME + "PONG " + SERVER_NAME + " :" + param)

void Server::ping(Server *server, Client *client, std::string param)
{
    std::vector<std::string> params = split_string(param, ' ');

    if (params.size() == 0)
        return server->SendMsg2Client(client->getFd(), ERROR_409(client->getNickName()));
    return server->SendMsg2Client(client->getFd(), PING_SUCCESS(params[0]));
}