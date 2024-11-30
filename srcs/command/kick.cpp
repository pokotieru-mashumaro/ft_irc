#include "../../includes/All.hpp"

#define KICK_SUCCESS(nickname, username, channelname, targetnick, msg) std::string(":" + nickname + "!~" + username + "@localhost KICK :" + channelname + " " + targetnick +  " :" + msg)

void Channel::kick(Server *server, Client *client, std::string param)
{
    if (!client->isConnected())
        return server->SendMsg2Client(client->getFd(), NOT_CONNECT(client->getNickName()));
    std::vector<std::string> params = split_string(param, ' ');

    if (params.size() != 2 && params.size() != 3)
        return server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "KICK"));

    Channel *channel = server->getChannel(params[0]);
    Client *target = server->getClient(params[1]);
    if (!channel)
        return server->SendMsg2Client(client->getFd(), ERROR_401(client->getNickName(), params[0]));
    if (!channel->is_operator(client))
        return server->SendMsg2Client(client->getFd(), ERROR_482(client->getNickName(), channel->getName()));
    if (!target)
        return server->SendMsg2Client(client->getFd(), ERROR_401(client->getNickName(), params[1]));
    if (!channel->is_exist(target))
        return server->SendMsg2Client(client->getFd(), ERROR_441(client->getNickName(), target->getNickName(), channel->getName()));

    channel->unsetClient(target);
    std::string msg = params.size() == 2 ? client->getNickName() : params[2];
    server->SendMsg2Client(client->getFd(), KICK_SUCCESS(client->getNickName(), client->getUserName(), channel->getName(), target->getNickName(), msg));
    server->SendMsg2Channnel(client, channel, KICK_SUCCESS(client->getNickName(), client->getUserName(), channel->getName(), target->getNickName(), msg));
}