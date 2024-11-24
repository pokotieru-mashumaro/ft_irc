#include "../../includes/All.hpp"

/*
paramの先頭に#がないとき "JOIN hello" "JOIN hello oo"
:naishomarunosukenomacbook-air.local 403 kkomatsu hello :No such channel

成功例(nickname = kkomatsu)：JOIN #sample
:kkomatsu!~kk@localhost JOIN :#sample
:naishomarunosukenomacbook-air.local 353 kkomatsu = #sample :@kkomatsu
:naishomarunosukenomacbook-air.local 366 kkomatsu #sample :End of NAMES list

:naishomarunosukenomacbook-air.local 353 wedrf = #sample :wedrf @kkomatsu
*/

#define JOIN_ERROR1(nickname, channelname) std::string(":" + SERVER_NAME + " 403 " + nickname + " " + channelname + " :No such channeel")
#define JOIN_SUCCESS1(nickname, username, channelname) std::string(":" + nickname + "!~" + username + "@localhost JOIN :" + channelname)
#define JOIN_SUCCESS2(nickname, channelname, nicknames) std::string(":" + SERVER_NAME + " 353 " + nickname + " = " + channelname + ":" + nicknames)
#define JOIN_SUCCESS3(nickname, channelname) std::string(":" + SERVER_NAME + " 366 " + nickname + + " " + channelname + " :End of NAMES list")

static std::string getNicknames(Channel *channel)
{
    std::vector<Client *> clients = channel->getClients();
    std::string ret = "";

    for (size_t i = 0; i < clients.size(); i++)
    {
        if (clients[i]->getIsOperator())
            ret += "@";
        ret += clients[i]->getNickName();
        ret += " ";
    }
    return ret;
}

void Channel::join(Server *server, Client *client, std::string param)
{


    std::vector<std::string> params;

    params = split_string(param, ' ');
    if (params.size() != 1 || params.size() != 2)
        return server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "JOIN"));

    if (params[0][0] != '#')
        return server->SendMsg2Client(client->getFd(), JOIN_ERROR1(client->getNickName(), param));

    Channel *channel = server->getChannel(params[0]);
    if (channel == NULL)
        channel = new Channel(client, params[0]);
    if (params.size() == 2)
        channel->setPassword(params[1]);


    server->SendMsg2Client(client->getFd(), JOIN_SUCCESS1(client->getNickName(), client->getUserName(), param));
    server->SendMsg2Client(client->getFd(), JOIN_SUCCESS2(client->getNickName(), param, getNicknames(channel)));
    server->SendMsg2Client(client->getFd(), JOIN_SUCCESS3(client->getNickName(), param));
}