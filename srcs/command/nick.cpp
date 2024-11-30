#include "../../includes/All.hpp"

/*
パラメーターがなしor多い：
:naishomarunosukenomacbook-air.local 461 * NICK :Syntax error

使えない文字；432 * (param)
:naishomarunosukenomacbook-air.local 432 * j@j :Erroneous nickname

名前被り：
:naishomarunosukenomacbook-air.local 433 * kko :Nickname already in use
*/

static bool contains_ng_ascii(const std::string& str) {
    for (int i = 0; i < (int)str.size(); ++i)
    {
        char ch = str[i];
        if (!isalnum(ch))
            return true;
    }
    return false;
}

static bool is_duplicate_nickname(Server *server, std::string param)
{
    std::vector<std::string> nicks;

    nicks = server->getNickNames();
    for (size_t i = 0; i < nicks.size(); i++)
    {
        if (nicks[i] == param)
            return true;
    }
    return false;
}

void Client::nick(Server *server, Client *client, std::string param)
{
    // std::cout << "param:" << param << std::endl;
    size_t spaceIndex = param.find(' ');

    if (param == "" || spaceIndex != std::string::npos)
        server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "NICK"));
    else if (contains_ng_ascii(param))
        server->SendMsg2Client(client->getFd(), ERROR_432(param));
    else if (is_duplicate_nickname(server, param))
        server->SendMsg2Client(client->getFd(), ERROR_433(param));
    else
        client->setNickName(param);
}