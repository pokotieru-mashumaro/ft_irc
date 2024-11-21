#include "../../includes/All.hpp"

void Client::nick(Server *server, Client *client, std::string param)
{

    //validate
    std::cout << "param:" << param << std::endl;
    // client->setNickName(param);
    server->SendMsg2Client(client->getFd(), "nick done");
}