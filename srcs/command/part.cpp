#include "../../includes/All.hpp"

/*
パラメータが1,2個以外

チャンネル名がない  PART saple
:naishomarunosukenomacbook-air.local 403 nickname saple :No such channel

チャンネルにいない
:naishomarunosukenomacbook-air.local 442 jvnd #sample :You are not on that channel

成功
PART #sample
:kkk!~asd@localhost PART #sample :

PART #sample message
:kkk!~asd@localhost PART #sample :message

*/

#define PART_ERROR1(nickname, channelname) std::string(":" + SERVER_NAME + " 403 " + nickname + " " + channelname + " :No such channeel")
#define PART_ERROR2(nickname, channelname) std::string(":" + SERVER_NAME + " 442 " + nickname + " " + channelname + " :You are not on that channel")
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


void Channel::part(Server *server, Client *client, std::string param)
{
    std::vector<std::string> params;

    if (!client->isConnected())
        return server->SendMsg2Client(client->getFd(), NOT_CONNECT(client->getNickName()));
    params = split_string(param, ' ');
    if (params.size() != 1 && params.size() != 2)
        return server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "PART"));

    Channel *channel = server->getChannel(params[0]);
    if (!channel)
        return server->SendMsg2Client(client->getFd(), PART_ERROR1(client->getNickName(), params[0]));
    if (is_not_join(channel, client->getNickName()))
        return server->SendMsg2Client(client->getFd(), PART_ERROR2(client->getNickName(), params[0]));
    
    channel->unsetClient(client);
    channel->unsetOperaor(client);
    if (channel->getClients().empty())
    {
        server->unsetChannel(channel);
        delete channel;
    }
    std::string message = params.size() == 2 ? params[1] : "";
    return server->SendMsg2Client(client->getFd(), PART_SUCCESS(client->getNickName(), client->getUserName(), params[0], message));
}