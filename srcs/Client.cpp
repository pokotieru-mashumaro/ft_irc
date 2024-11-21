#include "../includes/All.hpp"

Client::Client(int fd)
{
    _status = NEED_PASSWORD;
    _nickname = "";
    _username = "";
    _fd = fd;
    _nowchannel = NULL;
};