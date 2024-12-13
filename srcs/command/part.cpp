#include "../../includes/All.hpp"

#define PART_SUCCESS(nickname, username, channelname, message) std::string(":" + nickname + "!~" + username + "@localhost PART " + channelname + " :" + message)

static bool is_not_join(Channel *channel, std::string nickname)
{
    std::vector<Client *> clients = channel->getClients();

    for (size_t i = 0; i < clients.size(); i++)
    {
        if (clients[i]->getNickName() == nickname)
            return false;
    }
    return true;
}

void Channel::part(Server *server, Client *client, std::vector<std::string> params)
{

    if (!client->isConnected())
        return server->SendMsg2Client(client->getFd(), NOT_CONNECT(client->getNickName()));
    if (params.size() != 1 && params.size() != 2)
        return server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "PART"));

    Channel *channel = server->getChannel(params[0]);
    if (!channel)
        return server->SendMsg2Client(client->getFd(), ERROR_403(client->getNickName(), params[0]));
    if (is_not_join(channel, client->getNickName()))
        return server->SendMsg2Client(client->getFd(), ERROR_442(client->getNickName(), params[0]));
    
    channel->unsetClient(client);
    channel->unsetOperaor(client);
    if (channel->getClients().empty())
    {
        server->unsetChannel(channel);
        delete channel;
    }
    std::string message = params.size() == 2 ? params[1] : "";

    server->SendMsg2Channnel(client, channel, PART_SUCCESS(client->getNickName(), client->getUserName(), params[0], message));
    server->SendMsg2Client(client->getFd(), PART_SUCCESS(client->getNickName(), client->getUserName(), params[0], message));
}