#include "../../includes/All.hpp"

/*
paramの先頭に#がないとき "JOIN hello" "JOIN hello oo"
:naishomarunosukenomacbook-air.local 403 kkomatsu hello :No such channel

成功例(nickname = kkomatsu)：JOIN #sample
:kkomatsu!~kk@localhost JOIN :#sample
:naishomarunosukenomacbook-air.local 353 kkomatsu = #sample :@kkomatsu
:naishomarunosukenomacbook-air.local 366 kkomatsu #sample :End of NAMES list
*/

void Channel::join(Server *server, Client *client, std::string param)
{
    if (param == "")
        server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "JOIN"));
}