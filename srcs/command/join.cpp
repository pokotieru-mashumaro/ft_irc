#include "../../includes/All.hpp"

#define JOIN_SUCCESS1(nickname, username, channelname) std::string(":" + nickname + "!~" + username + "@localhost JOIN :" + channelname)
#define JOIN_SUCCESS2(nickname, channelname, nicknames) std::string(":" + SERVER_NAME + " 353 " + nickname + " = " + channelname + " :" + nicknames)
#define JOIN_SUCCESS3(nickname, channelname) std::string(":" + SERVER_NAME + " 366 " + nickname + + " " + channelname + " :End of NAMES list")
#define JOIN_OTHER_CLIENT(nickname, username, channelname) std::string(":" + nickname + "!~" + username + "@localhost JOIN :" + channelname)

static std::string getNicknames(Channel *channel)
{
    std::vector<Client *> clients = channel->getClients();
    std::string ret = "";

    for (size_t i = clients.size() - 1; i > 0; i--)
    {
        if (channel->is_operator(clients[i]))
            ret += "@";
        ret += clients[i]->getNickName();
        ret += " ";
    }
    if (channel->is_operator(clients[0]))
        ret += "@";
    ret += clients[0]->getNickName();
    return ret;
}

static bool is_already_exist_client(Channel *channel, std::string client_name)
{
    std::vector<Client *> clients = channel->getClients();

    for (size_t i = 0; i < clients.size(); i++)
    {
        if (clients[i]->getNickName() == client_name)
            return true;
    }
    return false;
}

void Channel::join(Server *server, Client *client, std::string param)
{
    std::vector<std::string> params;

    if (!client->isConnected())
        return server->SendMsg2Client(client->getFd(), NOT_CONNECT(client->getNickName()));
    params = split_string(param, ' ');
    if (params.size() != 1 && params.size() != 2)
        return server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "JOIN"));
    if (params[0][0] != '#')
        return server->SendMsg2Client(client->getFd(), ERROR_403(client->getNickName(), param));

    Channel *channel = server->getChannel(params[0]);
    if (channel == NULL)
    {
        channel = new Channel(params[0]);
        server->setChannels(channel);

        channel->setOperator(client);
    }

    if (is_already_exist_client(channel, client->getNickName()))
        return;
    if (channel->is_mode_adaptation("l") && channel->getClients().size() >= channel->getMaxNum())
        return server->SendMsg2Client(client->getFd(), ERROR_471(client->getNickName(), client->getUserName()));
    if (channel->is_mode_adaptation("i") && !channel->is_invited(client->getNickName()))
        return server->SendMsg2Client(client->getFd(), ERROR_473(client->getNickName(), client->getUserName()));
    if (channel->is_mode_adaptation("k") && (params.size() != 2 || channel->getPassword() != params[1]))
        return server->SendMsg2Client(client->getFd(), ERROR_475(client->getNickName(), client->getUserName()));

    channel->setClient(client);
    channel->setName(params[0]);

    server->SendMsg2Channnel(client, channel, JOIN_OTHER_CLIENT(client->getNickName(), client->getUserName(), channel->getName()));

    server->SendMsg2Client(client->getFd(), JOIN_SUCCESS1(client->getNickName(), client->getUserName(), params[0]));
    server->SendMsg2Client(client->getFd(), JOIN_SUCCESS2(client->getNickName(), params[0], getNicknames(channel)));
    server->SendMsg2Client(client->getFd(), JOIN_SUCCESS3(client->getNickName(), params[0]));
}