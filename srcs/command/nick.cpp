#include "../../includes/All.hpp"

/*
パラメーターがなしor多い：
:naishomarunosukenomacbook-air.local 461 * NICK :Syntax error

使えない文字；432 * (param)
:naishomarunosukenomacbook-air.local 432 * j@j :Erroneous nickname

名前被り：
:naishomarunosukenomacbook-air.local 433 * kko :Nickname already in use
*/

#define NICKNAME_ERROR1(nickname) std::string(":" + SERVER_NAME + " 432 * " + nickname + " :Erroneous nickname")
#define NICKNAME_ERROR2(nickname) std::string(":" + SERVER_NAME + " 433 * " + nickname + " :Nickname already in use")


void Client::nick(Server *server, Client *client, std::string param)
{
    std::cout << "param:" << param << std::endl;

    size_t spaceIndex = param.find(' ');

    if (param == "" || spaceIndex != std::string::npos)
        server->SendMsg2Client(client->getFd(), SYNTAX_ERROR("NICK"));
    client->setNickName(param);
}