#include "../../includes/All.hpp"

/*
paramの先頭に#がないとき "JOIN hello" "JOIN hello oo"
:naishomarunosukenomacbook-air.local 403 kkomatsu hello :No such channel

成功例(nickname = kkomatsu)：JOIN #sample
:kkomatsu!~kk@localhost JOIN :#sample
:naishomarunosukenomacbook-air.local 353 kkomatsu = #sample :@kkomatsu
:naishomarunosukenomacbook-air.local 366 kkomatsu #sample :End of NAMES list
*/

#define JOIN_ERROR1(nickname, channelname) std::string(":" + SERVER_NAME + " 403 " + nickname + " " + channelname + " :No such channeel")
#define JOIN_SUCCESS1(nickname, username, channelname) std::string(":" + nickname + "!~" + username + "@localhost JOIN :" + channelname)
#define JOIN_SUCCESS2(nickname, channelname) std::string(":" + SERVER_NAME + " 353 " + nickname + " = " + channelname + ":@" + nickname)
#define JOIN_SUCCESS3(nickname, channelname) std::string(":" + SERVER_NAME + " 366 " + nickname + + " " + channelname + " :End of NAMES list")


void Channel::join(Server *server, Client *client, std::string param)
{
    if (param == "")
        server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "JOIN"));
    param = split_string(param, ' ')[0];
    if (param[0] != '#')
    {
        server->SendMsg2Client(client->getFd(), JOIN_ERROR1(client->getNickName(), param));
        return;
    }

    server->SendMsg2Client(client->getFd(), JOIN_SUCCESS1(client->getNickName(), client->getUserName(), param));
    server->SendMsg2Client(client->getFd(), JOIN_SUCCESS2(client->getNickName(), param));
    server->SendMsg2Client(client->getFd(), JOIN_SUCCESS3(client->getNickName(), param));
}