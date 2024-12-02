#include "../../includes/All.hpp"

std::string trim_space(std::string str) 
{
    int length;
    while (!str.empty() && isspace(*str.begin()))
        str.erase(str.begin());
    for (length = (str.length() - 1); length >= 0 && isspace(str[length]); length--);
    return str.substr(0, length + 1);
}

std::vector<std::string> split_string(std::string str, char c)
{
    std::vector<std::string> elems;
	std::string item;

	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] == c) {
			if (!item.empty())
				elems.push_back(item);
			item.clear();
		}
		else {
			item += str[i];
		}
	}
	if (!item.empty())
		elems.push_back(item);
	return elems;
}

size_t s2st_for_mode_l(std::string str) 
{
    if (str.empty())
        return static_cast<size_t>(-1);

    for (size_t i = 0; i < str.size(); ++i) 
	{
        if (!isdigit(str[i]))
            return static_cast<size_t>(-1);
    }

    std::stringstream ss(str);
    size_t result;
    if (!(ss >> result))
        return static_cast<size_t>(-1);

    return result;
}
