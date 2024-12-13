#include "../../includes/All.hpp"

#define INVITE_SUCCESS(nickname, targetname, channelname) std::string(":" + SERVER_NAME + " 341 " + nickname + " " + targetname + " " + channelname)
#define INVITE_OTHER_CLIENT(nickname, username, targetnick, channelname) std::string(":" + nickname + "!~" + username + "@localhost INVITE " + targetnick + " " + channelname)

void Channel::invite(Server *server, Client *client, std::vector<std::string> params)
{
    if (!client->isConnected())
        return server->SendMsg2Client(client->getFd(), NOT_CONNECT(client->getNickName()));

    if (params.size() != 2)
        return server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "INVITE"));

    Client *target = server->getClient(params[0]);
    Channel *channel = server->getChannel(params[1]);
    if (!target || !channel || !target->isConnected())
    {
        std::string target_str = !target ? params[0] : params[1];
        return server->SendMsg2Client(client->getFd(), ERROR_401(client->getNickName(), target_str));
    }
    if (channel->is_exist(target))
        return server->SendMsg2Client(client->getFd(), ERROR_443(client->getNickName(), target->getNickName()));
    if (!channel->is_exist(client))
        return server->SendMsg2Client(client->getFd(), ERROR_442(client->getNickName(), channel->getName()));
    if (!channel->is_operator(client))
        return server->SendMsg2Client(client->getFd(), ERROR_482(client->getNickName(), channel->getName()));
    
    if (channel->is_mode_adaptation("i") && !channel->is_invited(target->getNickName()))
        channel->setInviteList(target->getNickName());
    server->SendMsg2Client(client->getFd(), INVITE_SUCCESS(client->getNickName(), target->getNickName(), channel->getName()));
    server->SendMsg2Client(target->getFd(), INVITE_OTHER_CLIENT(client->getNickName(), client->getUserName(), target->getNickName(), channel->getName()));
}