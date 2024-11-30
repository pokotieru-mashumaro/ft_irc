#include "../../includes/All.hpp"

/*
Parameters: <channel> [ <topic> ]

引数1,2以外

topicない状態で引数1個（自分だけ）  TOPIC #123
:naishomarunosukenomacbook-air.local 331 kk #123 :No topic is set

存在しないchannel
:naishomarunosukenomacbook-air.local 403 KK asdf :No such channel

成功（全員同じ）TOPIC #123 @@
:KK!~kkoma@localhost TOPIC #123 :@@

成功,引数1個(自分だけ) TOPIC #123
:naishomarunosukenomacbook-air.local 332 KK #123 :@@
:naishomarunosukenomacbook-air.local 333 KK #123 KK 1732858505
*/

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
    if (!channel->is_operator(client))
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