#include "../../includes/All.hpp"

#define TOPIC_SUCCESS1(nickname, username, channelname, topic) std::string(":" + nickname + "!~" + username + "@localhost TOPIC :" + channelname +  " :" + topic)
#define TOPIC_SUCCESS2(nickname, channelname, topic) std::string(":" + SERVER_NAME + " 332 " + nickname + " " + channelname + " :" + topic)

void Channel::topic(Server *server, Client *client, std::string param)
{
    if (!client->isConnected())
        return server->SendMsg2Client(client->getFd(), NOT_CONNECT(client->getNickName()));
    std::vector<std::string> params = split_string(param, ' ');

    if (params.size() != 1 && params.size() != 2)
        return server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "TOPIC"));
    
    Channel *channel = server->getChannel(params[0]);
    if (!channel)
        return server->SendMsg2Client(client->getFd(), ERROR_403(client->getNickName(), params[0]));
    if (!channel->is_exist(client))
        return server->SendMsg2Client(client->getFd(), ERROR_442(client->getNickName(), channel->getName()));
    if (channel->is_mode_adaptation("t") && !channel->is_operator(client))
        return server->SendMsg2Client(client->getFd(), ERROR_482(client->getNickName(), channel->getName()));
    if (params.size() == 1 && channel->getTopic() == "")
        return server->SendMsg2Client(client->getFd(), ERROR_331(client->getNickName(), channel->getName()));

    if (params.size() == 1)
    {
        return server->SendMsg2Client(client->getFd(), TOPIC_SUCCESS2(client->getNickName(), channel->getName(), channel->getTopic()));
    }
    else if (params.size() == 2)
    {
        channel->setTopic(params[1]);
        server->SendMsg2Channnel(client, channel, TOPIC_SUCCESS1(client->getNickName(), client->getUserName(), channel->getName(), params[1]));
        return server->SendMsg2Client(client->getFd(), TOPIC_SUCCESS1(client->getNickName(), client->getUserName(), channel->getName(), params[1]));
    }
}