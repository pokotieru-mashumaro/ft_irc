#include "../../includes/All.hpp"

/*
Parameters: <channel> *( "," <channel> ) <user> *( "," <user> ) [<comment>]

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

void Channel::kick(Server *server, Client *client, std::string param)
{
    if (!client->isConnected())
        return server->SendMsg2Client(client->getFd(), NOT_CONNECT(client->getNickName()));
    std::vector<std::string> params = split_string(param, ' ');

    if (params.size() != 2 && params.size() != 3)
        return server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "INVITE"));

    Channel *channel = server->getChannel(params[0]);
    Client *target = server->getClient(params[1]);

}