#include "../../includes/All.hpp"

#define QUIT_SUCCESS(nickname, param) std::string("ERROR :Closing connection: " + nickname + "[~@localhost] (" + param + ")")
#define QUIT_SUCCESS2(nickname, username, param) std::string(":" + nickname + "!~" + username + "@localhost QUIT :" + param)

void Client::quit(Server *server, Client *client, std::string param)
{
    std::vector<std::string> params = split_string(param, ' ');

    if (params.size() != 0 && params.size() != 1)
        return server->SendMsg2Client(client->getFd(), SYNTAX_ERROR(client->getNickName(), "QUIT"));
    std::string msg = params.size() == 0 ? "" : params[0];
    server->SendMsg2Client(client->getFd(), QUIT_SUCCESS(client->getNickName(), msg));

    std::vector<Channel *> bye_channels = server->getClientChannels(client->getNickName());
    msg = params.size() == 0 ? client->getNickName() : "\"" + params[0] + "\"";
    for (size_t i = 0; i < bye_channels.size(); i++)
    {
        server->SendMsg2Channnel(client, bye_channels[i], QUIT_SUCCESS2(client->getNickName(), client->getUserName(), msg));
        bye_channels[i]->unsetClient(client);
        if (bye_channels[i]->is_operator(client))
            bye_channels[i]->unsetOperaor(client);
        if (bye_channels[i]->getClients().size() == 0)
        {
            server->unsetChannel(bye_channels[i]);
            delete bye_channels[i];
        }
    }
    server->ClearClients(client->getFd());
}
