#include "../../includes/All.hpp"

void Server::cap(Server *server, Client *client, std::string param)
{
    std::size_t pos = param.find('\n');

    if (pos != std::string::npos) {
        param = param.substr(0, pos-1);
    }

    if (param == "LS 302")
    {
        std::cout << "param: " << param << std::endl;
        server->SendMsg2Client(client->getFd(), "CAP * LS :message-tags multi-prefix");
    }
    else if (param == "REQ :multi-prefix")
        server->SendMsg2Client(client->getFd(), "CAP * ACK :multi-prefix");
    else if (param == "END")
    {
        server->SendMsg2Client(client->getFd(), RPL_WELCOME(client->getNickName()));
    }
}