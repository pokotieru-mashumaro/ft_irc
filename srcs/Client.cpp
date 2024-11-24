#include "../includes/All.hpp"

Client::Client(int fd)
{
    _status = NEED_PASSWORD;
    _is_passed = false;
    _nickname = "*";
    _username = "";
    _fd = fd;
    // _nowchannel = NULL;
};

bool Client::isConnected()
{
    return !(!_is_passed || _nickname == "*" || _username == "");
}