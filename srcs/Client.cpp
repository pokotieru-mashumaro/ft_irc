#include "../includes/All.hpp"

Client::Client(int fd)
{
    _is_passed = false;
    _nickname = "*";
    _username = "";
    _fd = fd;
};

bool Client::isConnected()
{
    return !(!_is_passed || _nickname == "*" || _username == "");
}