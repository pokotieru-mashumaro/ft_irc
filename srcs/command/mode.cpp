#include "../../includes/All.hpp"

#define MODE_SUCCESS(nickname, username, param) std::string(":" + nickname + "!?" + username + "@localhost MODE " + param)
#define MODE_SUCCESS2(nickname, username, param1, param2) std::string(":" + nickname + "!?" + username + "@localhost MODE " + param1 + " " + param2)

static void mode_cmd_i(Server *server, Client *client, Channel *channel, std::vector<std::string> params)
{
    if (params.size() != 2)
        return server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "MODE"));

    if ((params[1] == "i" || params[1] == "+i") && !channel->is_mode_adaptation("i"))
    {
        channel->setMode("i");
        server->SendMsg2Channnel(client, channel, MODE_SUCCESS(client->getNickName(), client->getUserName(), "+i"));
        return server->SendMsg2Client(client->getFd(), MODE_SUCCESS(client->getNickName(), client->getUserName(), "+i"));
    }
    else if (params[1] == "-i" && channel->is_mode_adaptation("i"))
    {
        channel->unsetMode("i");
        server->SendMsg2Channnel(client, channel, MODE_SUCCESS(client->getNickName(), client->getUserName(), "-i"));
        return server->SendMsg2Client(client->getFd(), MODE_SUCCESS(client->getNickName(), client->getUserName(), "-i"));
    }
}

static void mode_cmd_t(Server *server, Client *client, Channel *channel, std::vector<std::string> params)
{
    if (params.size() != 2)
        return server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "MODE"));

    if ((params[1] == "t" || params[1] == "+t") && !channel->is_mode_adaptation("t"))
    {
        channel->setMode("t");
        server->SendMsg2Channnel(client, channel, MODE_SUCCESS(client->getNickName(), client->getUserName(), "+t"));
        return server->SendMsg2Client(client->getFd(), MODE_SUCCESS(client->getNickName(), client->getUserName(), "+t"));
    }
    else if (params[1] == "-t" && channel->is_mode_adaptation("t"))
    {
        channel->unsetMode("t");
        server->SendMsg2Channnel(client, channel, MODE_SUCCESS(client->getNickName(), client->getUserName(), "-t"));
        return server->SendMsg2Client(client->getFd(), MODE_SUCCESS(client->getNickName(), client->getUserName(), "-t"));
    }
}

static void mode_cmd_k(Server *server, Client *client, Channel *channel, std::vector<std::string> params)
{
    if ((params[1] == "k" || params[1] == "+k") && !channel->is_mode_adaptation("k"))
    {
        if (params.size() != 3)
            return server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "MODE"));
        channel->setMode("k");
        channel->setPassword(params[2]);
        server->SendMsg2Channnel(client, channel, MODE_SUCCESS2(client->getNickName(), client->getUserName(), "+k", params[2]));
        return server->SendMsg2Client(client->getFd(), MODE_SUCCESS2(client->getNickName(), client->getUserName(), "+k", params[2]));
    }
    else if (params[1] == "-k" && channel->is_mode_adaptation("k"))
    {
        channel->unsetMode("k");
        channel->setPassword("");
        server->SendMsg2Channnel(client, channel, MODE_SUCCESS2(client->getNickName(), client->getUserName(), "-k", "*"));
        return server->SendMsg2Client(client->getFd(), MODE_SUCCESS2(client->getNickName(), client->getUserName(), "-k", "*"));
    }
}

static void mode_cmd_o(Server *server, Client *client, Channel *channel, std::vector<std::string> params)
{
    if (params.size() != 3)
        return;

    Client *target = server->getClient(params[2]);
    if (!target)
        return server->SendMsg2Client(client->getFd(), ERROR_401(client->getNickName(), params[2]));
    if (!channel->is_exist(target))
        return server->SendMsg2Client(client->getFd(), ERROR_441(client->getNickName(), params[2], channel->getName()));

    if (params[1] == "o" || params[1] == "+o")
    {
        if (channel->is_operator(target))
            return;
        channel->setOperator(target);
        server->SendMsg2Channnel(client, channel, MODE_SUCCESS2(client->getNickName(), client->getUserName(), "+o", params[2]));
        return server->SendMsg2Client(client->getFd(), MODE_SUCCESS2(client->getNickName(), client->getUserName(), "+o", params[2]));
    }
    else if (params[1] == "-o")
    {
        if (!channel->is_operator(target))
            return;
        channel->unsetOperaor(target);
        server->SendMsg2Channnel(client, channel, MODE_SUCCESS2(client->getNickName(), client->getUserName(), "-o", params[2]));
        return server->SendMsg2Client(client->getFd(), MODE_SUCCESS2(client->getNickName(), client->getUserName(), "-o", params[2]));
    }
}

static void mode_cmd_l(Server *server, Client *client, Channel *channel, std::vector<std::string> params)
{

    if ((params[1] == "l" || params[1] == "+l") && !channel->is_mode_adaptation("l"))
    {
        if (params.size() != 3)
            return server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "MODE"));
        
        size_t num = s2st_for_mode_l(params[2]);
        if (num <= 0)
            return server->SendMsg2Client(client->getFd(), ERROR_696(client->getNickName(), channel->getName(), "l"));

        channel->setMode("l");
        channel->setMaxNum(num);
        server->SendMsg2Channnel(client, channel, MODE_SUCCESS2(client->getNickName(), client->getUserName(), "+l", params[2]));
        return server->SendMsg2Client(client->getFd(), MODE_SUCCESS2(client->getNickName(), client->getUserName(), "+l", params[2]));
    }
    else if (params[1] == "-l" && channel->is_mode_adaptation("l"))
    {
        if (params.size() != 2)
            return ;
        
        channel->unsetMode("l");
        server->SendMsg2Channnel(client, channel, MODE_SUCCESS(client->getNickName(), client->getUserName(), "-l"));
        return server->SendMsg2Client(client->getFd(), MODE_SUCCESS(client->getNickName(), client->getUserName(), "-l"));
    }
}

void Channel::mode(Server *server, Client *client, std::string param)
{
    if (!client->isConnected())
        return server->SendMsg2Client(client->getFd(), NOT_CONNECT(client->getNickName()));
    std::vector<std::string> params = split_string(param, ' ');

    if (params.size() != 1)
        return server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "MODE"));

    Channel *channel = server->getChannel(params[0]);
    if (channel == NULL)
        return server->SendMsg2Client(client->getFd(), ERROR_401(client->getNickName(), params[0]));
    if (!channel->is_exist(client))
        return server->SendMsg2Client(client->getFd(), ERROR_442(client->getNickName(), params[0]));
    if (!channel->is_operator(client))
        return server->SendMsg2Client(client->getFd(), ERROR_482(client->getNickName(), params[0]));

    mode_cmd_i(server, client, channel, params);
    mode_cmd_t(server, client, channel, params);
    mode_cmd_k(server, client, channel, params);
    mode_cmd_o(server, client, channel, params);
    mode_cmd_l(server, client, channel, params);
}