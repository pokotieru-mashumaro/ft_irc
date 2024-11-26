#include "../../includes/All.hpp"

/*
params: <msgtarget> <text to be sent>

paramsがなかった時
:naishomarunosukenomacbook-air.local 411 nickname :No recipient given (PRIVMSG)

paramsが一つの時
:naishomarunosukenomacbook-air.local 412 nickname :No text to send

paramsが3つ以上の時
:naishomarunosukenomacbook-air.local 461 nickname PRIVMSG :Syntax error

paramsが2つかつ送り先がおかしい時 PRIVMSG test hello
:naishomarunosukenomacbook-air.local 401 nickname test :No such nick or channel name

成功したら自分以外に返す。
:nickname!~username@localhost PRIVMSG #123 :message
*/

#define PRIV_ERROR1(nickname) std::string(":" + SERVER_NAME + " 411 " + nickname + " :No recipient given (PRIVMSG)")
#define PRIV_ERROR2(nickname) std::string(":" + SERVER_NAME + " 412 " + nickname + " :No text to send")
#define PRIV_ERROR3(nickname, target) std::string(":" + SERVER_NAME + " 401 " + nickname + " " + target + " :No such nick or channel name")
#define PRIV_SUCCESS(nickname, username, channelname, message) std::string(":" + nickname + "!?" + username + "@localhost PRIVMSG " + channelname + " :" + message)

void Client::privmsg(Server *server, Client *client, std::string param)
{
    std::vector<std::string> params;

    if (!client->isConnected())
        return server->SendMsg2Client(client->getFd(), NOT_CONNECT(client->getNickName()));
    params = split_string(param, ' ');
    if (params.size() == 0)
        return server->SendMsg2Client(client->getFd(), PRIV_ERROR1(client->getNickName()));
    else if (params.size() == 1)
        return server->SendMsg2Client(client->getFd(), PRIV_ERROR2(client->getNickName()));
    else if (params.size() >= 3)
        return server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), ));
}