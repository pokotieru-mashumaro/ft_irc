#ifndef Utils_HPP
#define Utils_HPP

#include <iostream>

std::string trim_space(std::string str);
std::vector<std::string> split_string(std::string str, char c);
size_t s2st_for_mode_l(std::string str);
void cut_colon_params(std::vector<std::string> &params);
void debug_params(std::vector<std::string> params);

#endif
