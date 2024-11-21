#include "../../includes/All.hpp"

//頭と尻のスペース削除
std::string trim(std::string str) 
{
    int length;
    while (!str.empty() && isspace(*str.begin()))
        str.erase(str.begin());
    for (length = (str.length() - 1); length >= 0 && isspace(str[length]); length--);
    return str.substr(0, length + 1);
}
