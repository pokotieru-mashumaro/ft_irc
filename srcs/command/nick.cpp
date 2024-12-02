#include "../../includes/All.hpp"

static bool contains_ng_ascii(const std::string& str) {
    char ok_ascii[8] = {'|', '-', '[', ']', '{', '}', '_'};
    int ng_count;

    for (int i = 0; i < (int)str.size(); ++i)
    {
        char ch = str[i];
        ng_count = 0;
        for (int j = 0; j < 7; j++) 
            if (ch != ok_ascii[j])
                ng_count++;
        if (!isalnum(ch) && ng_count == 7)
            return true;
        else if (i ==0 && ch == '-')
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
    if (client->isConnected())
        server->SendMsg2Client(client->getFd(), WELCOME(client->getNickName(), client->getUserName()));
}