#include "../includes/All.hpp"

Client::Client(int fd)
{
    _status = NEED_PASSWORD;
    _is_passed = false;
    _is_operator = false;
    _nickname = "*";
    _username = "";
    _fd = fd;
    _nowchannel = NULL;
};

bool Client::isConnected()
{
    std::cout << "isConnect:" <<  !(!_is_passed || _nickname == "" || _username == "") << std::endl;
    return !(!_is_passed || _nickname == "" || _username == "");
}