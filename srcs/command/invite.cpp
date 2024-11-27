#include "../../includes/All.hpp"

/*
Parameters: <nickname> <channel>


引数が2つ以外の時
:naishomarunosukenomacbook-air.local 461 asd INVITE :Syntax error

:naishomarunosukenomacbook-air.local 401 kk saki :No such nick or channel name

すでにいる
:naishomarunosukenomacbook-air.local 443 mynick targetnick #123 :is already on channel

成功時 自分が受け取る
:naishomarunosukenomacbook-air.local 341 mynick targetnick #123
成功時 あいてが受け取る
:nickname!~username@localhost INVITE 相手のnick #123
*/

#define INVITE_ERROR1(nickname, channelname) std::string(":" + SERVER_NAME + " 401 " + nickname + " " + channelname + " :No such nick or channel name")
#define INVITE_ERROR2(nickname, targetnick) std::string(":" + SERVER_NAME + " 443 " + nickname + " " + targetnick + " :is already on channel")
#define INVITE_SUCCESS(nickname, targetname, channelname) std::string(":" + SERVER_NAME + " 341 " + nickname + " " + targetname + " " + channelname)
#define INVITE_OTHER_CLIENT(nickname, username, targetnick, channelname) std::string(":" + nickname + "!~" + username + "@localhost INVITE :" + targetnick + " " + channelname)

void Channel::invite(Server *server, Client *client, std::string param)
{
    if (!client->isConnected())
        return server->SendMsg2Client(client->getFd(), NOT_CONNECT(client->getNickName()));
    std::vector<std::string> params = split_string(param, ' ');

    if (params.size() != 2)
        return server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "INVITE"));

    Client *target = server->getClient(params[0]);
    Channel *channel = server->getChannel(params[1]);
    if (!target || !channel)
    {
        std::string target_str = !target ? params[0] : params[1];
        return server->SendMsg2Client(client->getFd(), INVITE_ERROR1(client->getNickName(), target_str));
    }
    if (channel->is_exist_string(params[0]))
        return server->SendMsg2Client(client->getFd(), INVITE_ERROR2(client->getNickName(), target->getNickName()));
    
    channel->setInviteList(target->getNickName());
    server->SendMsg2Client(client->getFd(), INVITE_SUCCESS(client->getNickName(), target->getNickName(), channel->getName()));
    server->SendMsg2Client(target->getFd(), INVITE_OTHER_CLIENT(client->getNickName(), client->getUserName(), target->getNickName(), channel->getName()));
}