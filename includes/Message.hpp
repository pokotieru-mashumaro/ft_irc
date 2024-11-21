#ifndef Message_HPP
#define Message_HPP

#define RED "\e[1;31m"
#define WHI "\e[0;37m"
#define GRE "\e[1;32m"
#define YEL "\e[1;33m"


#define RPL_SYNTAXERROR(message) std::string("ERROR Invalid command syntax. " + std::string(message))

#endif