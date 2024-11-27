#include "../../includes/All.hpp"

/*
Parameters: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )

引数なし or 存在しないコマンドな場合
:naishomarunosukenomacbook-air.local 461 nickname MODE :Syntax error

チャンネルが存在しない
:naishomarunosukenomacbook-air.local 401 nickname #123 :No such nick or channel name

チャンネルに入っていない
:naishomarunosukenomacbook-air.local 442 nickname #123 :You are not on that channel

チャンネルのオペレーターではない
:naishomarunosukenomacbook-air.local 482 nickname #123 :You are not channel operator

+,-がないときは+になる。MODE #123 i
:nickname!~username@localhost MODE #123 +i

MODE成功 同チャンネルのユーザーにも送られる
:nickname!~username@localhost MODE #123 -i


//先頭+,-のみ。mode_charはひとつのみ。
*/

#define MODE_ERROR1(nickname, channelname) std::string(":" + SERVER_NAME + " 401 " + nickname + " " + channelname + " :No such nick or channel name")
#define MODE_ERROR2(nickname, channelname) std::string(":" + SERVER_NAME + " 442 " + nickname + " " + channelname + " :You are not on that channel")
#define MODE_ERROR3(nickname, channelname) std::string(":" + SERVER_NAME + " 482 " + nickname + " " + channelname + " :You are not channel operator")
#define MODE_SUCCESS(nickname, username, param) std::string(":" + nickname + "!?" + username + "@localhost MODE " + param)

void Channel::mode(Server *server, Client *client, std::string param)
{
    if (!client->isConnected())
        return server->SendMsg2Client(client->getFd(), NOT_CONNECT(client->getNickName()));
    std::vector<std::string> params = split_string(param, ' ');

    if (params.size() != 1)
        return server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "MODE"));

    Channel *channel = server->getChannel(params[0]);
    if (channel == NULL)
        return server->SendMsg2Client(client->getFd(), MODE_ERROR1(client->getNickName(), params[0]));
    if (!channel->is_exist(client))
        return server->SendMsg2Client(client->getFd(), MODE_ERROR2(client->getNickName(), params[0]));
    if (!channel->is_operator(client))
        return server->SendMsg2Client(client->getFd(), MODE_ERROR3(client->getNickName(), params[0]));
    
}