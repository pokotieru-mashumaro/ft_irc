#include "../../includes/All.hpp"

/*
Parameters: <channel> <user> [<comment>]

引数が2,3以外
:naishomarunosukenomacbook-air.local 461 kk KICK :Syntax error

存在しないチャンネル KICK para1 para2
:naishomarunosukenomacbook-air.local 401 kk para2 :No such nick or channel name

いない人をkick
:naishomarunosukenomacbook-air.local 441 kk me #123 :They aren't on that channel

成功 チャンネル内のすべてのユーザーに同じメッセージ
:nickname!~username@localhost KICK #123 mei :nickname
messageがあれば
:nickname!~username@localhost KICK #123 mei :message

*/

#define KICK_ERROR1(nickname, para) std::string(":" + SERVER_NAME + " 401 " + nickname + " " + para + " :No such nick or channel name")
#define KICK_ERROR2(nickname, targetnick, channelname) std::string(":" + SERVER_NAME + " 441 " + nickname + " " + targetnick + " " + channelname + " :They aren't on that channel")
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
        return server->SendMsg2Client(client->getFd(), KICK_ERROR1(client->getNickName(), params[0]));
    if (!channel->is_operator(client))
        return server->SendMsg2Client(client->getFd(), NOT_OPERATOR(client->getNickName(), channel->getName()));
    if (!target)
        return server->SendMsg2Client(client->getFd(), KICK_ERROR1(client->getNickName(), params[1]));
    if (!channel->is_exist(target))
        return server->SendMsg2Client(client->getFd(), KICK_ERROR2(client->getNickName(), target->getNickName(), channel->getName()));

    channel->unsetClient(target);
    std::string msg = params.size() == 2 ? client->getNickName() : params[2];
    server->SendMsg2Client(client->getFd(), KICK_SUCCESS(client->getNickName(), client->getUserName(), channel->getName(), target->getNickName(), msg));
    server->SendMsg2Channnel(client, channel, KICK_SUCCESS(client->getNickName(), client->getUserName(), channel->getName(), target->getNickName(), msg));
}