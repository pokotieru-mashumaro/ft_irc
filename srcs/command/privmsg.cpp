#include "../../includes/All.hpp"

#define PRIV_SUCCESS(nickname, username, channelname, message) std::string(":" + nickname + "!~" + username + "@localhost PRIVMSG " + channelname + " :" + message)

static bool is_ok_target(Server *server, std::string target)
{
    std::vector<std::string> channel_names = server->getChannelNames();
    for (size_t i = 0; i < channel_names.size(); i++)
        if (channel_names[i] == target)
            return true;
    std::vector<std::string> client_names = server->getNickNames();
    for (size_t i = 0; i < client_names.size(); i++)
        if (client_names[i] == target)
            return true;
    return false;
}

void Client::privmsg(Server *server, Client *client, std::string param)
{
    std::vector<std::string> params;

    if (!client->isConnected())
        return server->SendMsg2Client(client->getFd(), NOT_CONNECT(client->getNickName()));
    params = split_string(param, ' ');
    if (params.size() == 0)
        return server->SendMsg2Client(client->getFd(), ERROR_411(client->getNickName()));
    else if (params.size() == 1)
        return server->SendMsg2Client(client->getFd(), ERROR_412(client->getNickName()));
    else if (params.size() >= 3)
        return server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "PRIVMSG"));
    if (!is_ok_target(server, params[0]))
        return server->SendMsg2Client(client->getFd(), ERROR_401(client->getNickName(), params[0]));
    if (params[0][0] == '#')
    {
        Channel *channel = server->getChannel(params[0]);
        if (!channel->is_exist(client))
            return;
        return server->SendMsg2Channnel(client, channel, PRIV_SUCCESS(client->getNickName(), client->getUserName(), params[0], params[1]));
    }
    else
    {
        Client *target = server->getClient(params[0]);
        if (!target->isConnected())
            return server->SendMsg2Client(client->getFd(), ERROR_401(client->getNickName(), params[0]));
        return server->SendMsg2Client(target->getFd(), PRIV_SUCCESS(client->getNickName(), client->getUserName(), params[0], params[1]));
    }
}