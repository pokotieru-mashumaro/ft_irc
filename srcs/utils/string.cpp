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

std::vector<std::string> split_string(std::string str, char c)
{
    std::vector<std::string> words;
    std::string::size_type start = 0;
    std::string::size_type end = str.find(c);

    while (end != std::string::npos) 
    {
        words.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(c, start);
    }

    words.push_back(str.substr(start));

    return words;
}

// int main() 
// {
//     std::string param = "1 2 3 4 5 10";
//     std::vector<std::string> params = split_string(param, ' ');

//     for (size_t i = 0; i < params.size(); i++)
//     {
//         std::cout << params[i] << ":" << std::endl;
//     }

//     return 0;
// }