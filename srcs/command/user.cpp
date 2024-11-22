#include "../../includes/All.hpp"

/*
Parameters: <user> <mode> <unused> <realname>
<mode> <unused>を実装するのか


パラメーターがなしor多い：
:naishomarunosukenomacbook-air.local 461 * NICK :Syntax error

*/

void Client::user(Server *server, Client *client, std::string param)
{
    std::vector<std::string> params;

    params = split_string(param, ' ');
    if (params.size() != 4)
        server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "USER"));
    
    client->setUserName(params[0]);
    client->setRealName(params[3]);
}