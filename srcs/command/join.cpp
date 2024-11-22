#include "../../includes/All.hpp"

/*

*/

void Channel::join(Server *server, Client *client, std::string param)
{
    if (param == "")
        server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "JOIN"));
}